//
// Created by oronla@wincs.cs.bgu.ac.il on 11/01/2020.
//

#include "../include/ReadFromKeyboard.h"
#include "../include/Receipt.h"
#include "../include/Stomp.h"
#include "../include/UserData.h"

ReadFromKeyboard::ReadFromKeyboard(UserData *userData, ConnectionHandler &connectionHandler, std::string s)
        :  connectionHandler(connectionHandler), input(s),countReceipt(1),countSubscription(1),  userData(userData){
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
            };
        }
    }
}

bool ReadFromKeyboard::clientCommand() {
    int spaceApp = input.find_first_of(' ', 0);
    std::string command = input.substr(0,spaceApp);


    if(command == "login"){
        std::vector<std::string> tmp  = split(input," ");

        this->headers.push_back("accept-version:1.2") ;
        std::vector<std::string> HP = split(tmp[1], ":");
        this->headers.push_back("host:" + HP[0]) ;// TODO : what is the host ?
        this->headers.push_back("login:" + tmp[2]) ;
        this->headers.push_back("passcode:" + tmp[3]) ;



        Stomp stomp = Stomp("CONNECT",headers,"");
        connectionHandler.connect();
        userData->setConected(true);
        userData->setName(tmp[2]);


        //update the input for not returning again to login
        this->input = "";
        headers.clear();
        return connectionHandler.sendFrameAscii(stomp.toString(),'\0');


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
        int subscription_id =-1;

        for (auto s : userData->getSubscription()){
            if(s.second == tmp[1]){
                subscription_id=s.first;
               this->headers.push_back( "id:" + std::to_string(subscription_id));
            }
        }
        // TODO: Worng club givin by the user
        if(subscription_id!= -1){
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
        // TODO: a book with few names

        std::vector<std::string> tmp  = split(input," ");
        this->input = "SEND";
        headers.push_back("destination:" + tmp[1]) ;
        // merge book name into one string TODO : test it

        std::string bookName ="";
        for(int i = 2; i<tmp.size(); i++){
            bookName = bookName + tmp[i] + " ";

        }


        std::string body =this->userData->getName() + " has added the book " +bookName;

        this->userData->addBook(bookName,this->userData->getName(),"",tmp[1]);

        Stomp stomp = Stomp(input,headers,body);
        std::cout << stomp.getFrameBody()  << std::endl;
        headers.clear();
        return connectionHandler.sendFrameAscii(stomp.toString(),'\0');

    }
    if(command == "borrow"){
        //TODO long book name
        std::vector<std::string> tmp = split(input," ");
        this->input = "SEND";

        headers.push_back("destination:" + tmp[1]) ;
        std::string body =this->userData->getName() + " wish to borrow " + tmp[2];

        Stomp stomp = Stomp("SEND",headers,body);
        headers.clear();
        return connectionHandler.sendFrameAscii(stomp.toString(),'\0');
    }

    if(command == "return"){
        this->headers = split(input," ");
        this->input = "SEND";

        this->headers[0]= "destination:" + this->headers[0];
        std::string body = "Returning" + this->headers[1] + "to" + this->userData->getName();

        //remove the book from the client
        for(auto& s: this->userData->getBooks()){
            if(s.getBookName() == this->headers[1]){
                //this->userData.getBooks().remove(s); // TODO: deletion
            }
        }
        Stomp stomp = Stomp(command,headers,body);
        headers.clear();
        return connectionHandler.sendFrameAscii(stomp.toString(),'\0');
    }

    if(command == "status"){
        this->headers = split(input," ");
        this->input = "SEND";

        this->headers[0]= "destination:" + this->headers[0];
        std::string body = "book status";

        Stomp stomp = Stomp(command,headers,body);
        headers.clear();
        return connectionHandler.sendFrameAscii(stomp.toString(),'\0');

    }
    if(command == "logout") {
        this->input = "DISCONNECT";

        Receipt receipt = Receipt(countReceipt,this->countSubscription,this->input,this->headers[0],connectionHandler);
        countReceipt++;
        this->userData->getSubscription().insert({this->countSubscription , this->headers[0]});
        this->userData->getReceipt().push_back(receipt);
        this->countSubscription++;

        this->headers[1] = "receipt:" + std::to_string(receipt.getId()) ;

        Stomp stomp = Stomp(command,headers,"");
        headers.clear();
        return connectionHandler.sendFrameAscii(stomp.toString(),'\0');
    }
}



std::vector<std::string> ReadFromKeyboard::split(std::string s, std::string delimiter) {
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