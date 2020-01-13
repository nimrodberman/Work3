//
// Created by oronla@wincs.cs.bgu.ac.il on 11/01/2020.
//

#include "../include/ReadFromKeyboard.h"

#include <utility>
#include "../include/Receipt.h"
#include "../include/Stomp.h"
#include "../include/UserData.h"

ReadFromKeyboard::ReadFromKeyboard(UserData *userData, ConnectionHandler &connectionHandler, std::string s, std::mutex &mutex,std::mutex &mutex_login)
        :  connectionHandler(connectionHandler), input(std::move(s)),countReceipt(1),countSubscription(1),  userData(userData), mutex(mutex),mutex_login(mutex_login){
}

void ReadFromKeyboard::run() {
    while (!connectionHandler.isTerminate()) {
        std::string word_to_check = input.substr(0,5);
        if (word_to_check != "login") {
            getline(std::cin, input);
            //encoding line and send them to server
            if (!clientCommand()) {
                std::cout << "Disconnected. Exiting...\n" << std::endl;
                break;
            }
        }
        else{
            if(!clientCommand()){
                std::cout << "Disconnected. Exiting...\n" << std::endl;
                break;
            }
        }
    }
}

bool ReadFromKeyboard::clientCommand() {
    int spaceApp = input.find_first_of(' ', 0);
    std::string command = input.substr(0,spaceApp);


    if(command == "login"){
        std::vector<std::string> tmp  = split(input," ");

        this->headers.emplace_back("accept-version:1.2") ;
        std::vector<std::string> HP = split(tmp[1], ":");
        this->headers.push_back("host:" + HP[0]) ;// TODO : what is the host ?
        this->headers.push_back("login:" + tmp[2]) ;
        this->headers.push_back("passcode:" + tmp[3]) ;



        Stomp stomp = Stomp("CONNECT",headers,"");
        userData->setName(tmp[2]);


        //update the input for not returning again to login
        this->input = "";
        headers.clear();
        if(!userData->isConected()){
            if(!connectionHandler.connect()){
                std::cout<< "Could not connect to server" << std::endl;
                connectionHandler.terminate();
                return false;
            }
        }
        connectionHandler.sendFrameAscii(stomp.toString(),'\0');
        userData->setConected(true); // TODO logging in only after reciving recipet
        return true;


    }
    if(command == "join"){
        std::vector<std::string> tmp = split(input," ");
        this->input = "SUBSCRIBE";

        Receipt receipt = Receipt(countReceipt,this->countSubscription, "SUBSCRIBE", tmp[1], this->connectionHandler);
        this->userData->getReceipt().push_back(receipt);
        this->headers.push_back("destination:" + tmp[1]);
        this->headers.push_back("id:" + std::to_string(this->countSubscription));
        this->headers.push_back("receipt:" + std::to_string(receipt.getId()));
        this->countSubscription++;
        this->countReceipt++;

        Stomp stomp = Stomp(this->input,headers,"");
        headers.clear();
        return connectionHandler.sendFrameAscii(stomp.toString(),'\0');

    }

    if(command == "exit"){
        std::vector<std::string> tmp = split(input," ");
        this->input = "UNSUBSCRIBE";
        int subscription_id = userData->isUserInClub(tmp[1]);

        if(subscription_id!= -1){
            this->headers.push_back( "id:" + std::to_string(subscription_id));
            Receipt receipt = Receipt(countReceipt,subscription_id,this->input,tmp[1],this->connectionHandler);
            countReceipt++;
            this->userData->getReceipt().push_back(receipt);
            headers.push_back("receipt:" + std::to_string(receipt.getId()));

            Stomp stomp = Stomp(this->input,headers,"");
            headers.clear();
            return connectionHandler.sendFrameAscii(stomp.toString(),'\0');

        }
        else{
            std::cout << "You are not a member in that kind of club!" <<  std::endl;
            return true;
        }
    }


    if(command == "add"){

        std::vector<std::string> tmp  = split(input," ");
        this->input = "SEND";
        headers.push_back("destination:" + tmp[1]) ;

        // merge book name into one string
        std::string bookName;
        for(int i = 2; (unsigned)i<tmp.size(); i++){
            bookName +=  tmp[i] ;
            if(i < tmp.size()-1){
                bookName += " ";
            }
        }

        if(userData->isUserInClub(tmp[1]) == -1){
            headers.clear();
            std::cout << "You are not a member in this club!" <<  std::endl;
            return true;

        }

        std::string body =this->userData->getName() + " has added the book " +bookName;

        this->userData->addBook(bookName,this->userData->getName(),"",tmp[1]);

        Stomp stomp = Stomp(input,headers,body);
        headers.clear();
        return connectionHandler.sendFrameAscii(stomp.toString(),'\0');

    }
    if(command == "borrow"){
        std::vector<std::string> tmp = split(input," ");
        this->input = "SEND";

        headers.push_back("destination:" + tmp[1]) ;

        // merge book name into one string
        std::string bookName;
        for(int i = 2; (unsigned)i<tmp.size(); i++){
            bookName += tmp[i] ;
            if(i < tmp.size()-1){
                bookName += " ";
            }
        }

        userData->addToWishList(bookName);// add the book to the wish list
        std::string body =this->userData->getName() + " wish to borrow " + bookName;

        Stomp stomp = Stomp("SEND",headers,body);
        headers.clear();
        return connectionHandler.sendFrameAscii(stomp.toString(),'\0');
    }

    if(command == "return"){

        std::vector<std::string> tmp = split(input," ");
        // merge book name into one string
        std::string bookName;
        for(int i = 2; (unsigned)i<tmp.size(); i++){
            bookName += tmp[i] ;
            if(i < tmp.size()-1){
                bookName += " ";
            }
        }
        this->input = "SEND";
        this->headers.push_back("destination:" + tmp[1]);



        // check if the book exist in the user inventory
        if(!userData->isBookExist(bookName)){
            headers.clear();
            std::cout << "You don't have this book!" <<  std::endl;
            return true;
        }

        else{ // if user have the book remove it and send the message
            Book tmp1 = userData->getBook(bookName);
            // if the user return the book to itself
            if(tmp1.getHolder() == userData->getName()){
                headers.clear();
                std::cout << "You are the owner of the book!" <<  std::endl;
                return true;
            }
            else{// if the user is not the owner of the book
                userData->removeBook(bookName);
                std::string body = "Returning " + bookName + " to " + tmp1.getHolder();
                //std::cout << body + "\n" <<  std::endl; TODO
                Stomp stomp = Stomp("SEND",headers,body);
                headers.clear();
                return connectionHandler.sendFrameAscii(stomp.toString(),'\0');
            }
        }



    }

    if(command == "status"){
        std::vector<std::string> tmp = split(input," ");

        // check if the user in the club
        if(userData->isUserInClub(tmp[1]) == -1){
            std::cout << "You are not a member in this club!" <<  std::endl;
            return true;
        }

        this->input = "SEND";

        headers.push_back( "destination:" + tmp[1]);
        std::string body = "book status";

        Stomp stomp = Stomp("SEND",headers,body);
        headers.clear();
        return connectionHandler.sendFrameAscii(stomp.toString(),'\0');

    }
    if(command == "logout") {
        this->input = "DISCONNECT";

        Receipt receipt = Receipt(countReceipt,this->countSubscription,this->input,this->headers[0],connectionHandler);
        countReceipt++;
        this->userData->getReceipt().push_back(receipt);

        headers.push_back("receipt:" + std::to_string(receipt.getId()));

        Stomp stomp = Stomp("DISCONNECT",headers,"");
        headers.clear();

        connectionHandler.sendFrameAscii(stomp.toString(),'\0');

        std::lock_guard<std::mutex> lock(mutex); // wait until receipt is arriving and then log out
        return false;
    }

    else{
        std::cout << "Command is no legal!" <<  std::endl;
        return true;
    }
}



std::vector<std::string> ReadFromKeyboard::split(const std::string& s, const std::string& delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}