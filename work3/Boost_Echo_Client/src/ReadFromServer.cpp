//
// Created by oronla@wincs.cs.bgu.ac.il on 11/01/2020.
//

#include "../include/ReadFromServer.h"
#include "../include/Stomp.h"
#include "../include/UserData.h"
#include "../include/Message.h"


ReadFromServer::ReadFromServer(UserData *data, ConnectionHandler &connectionHandler,std::mutex &mutex)
        : connectionHandler(connectionHandler), data(data), mutex(mutex){};



void ReadFromServer::run() {
    mutex.lock(); // a mutex for logging out
    while (1) {
        std::string input = "";
        if (data->isConected() && !connectionHandler.getFrameAscii((std::string &)input, '\0')) {
            std::cout << "1Disconnected. Exiting...\n" << std::endl;
            data->setConected(false); // TODO:: think if it is killinig something?
            break;
        }

        if(!input.empty()){
            decode(input);
        }
        if (connectionHandler.isTerminate()) {
            std::cout << "12Exiting...\n" << std::endl;
            break;
        }
    }



}

void ReadFromServer::decode(std::string in) {
    std::cout << in + "\n" << std::endl;
    std::vector<std::string> before_stomp = split(in, "\n");
    Stomp stomp = this->toStomp(before_stomp);


    if (stomp.getStompCommand() == "CONNECTED"){
        // TODO: SYNC printing
        std::cout << "Login successful" <<  std::endl;
    }

    if (stomp.getStompCommand() == "RECEIPT"){

        std::string s  = stomp.getHeaders()[0];
        std::vector<std::string> vec_s = split(s,":");
        int id = std::stoi(vec_s[1]);
        Receipt tmp = data->findAndReturnReciept(id);

        if (tmp.getAction() == "SUBSCRIBE"){
            data->addClub(tmp.getSubscriptionId(),tmp.getTopic());
            std::cout << "Joined club " << tmp.getTopic() << "\n";
        }

        if (tmp.getAction() == "UNSUBSCRIBE"){
            data->exitClub(tmp.getSubscriptionId());
            std::cout << "Exited club " << tmp.getTopic() << "\n";
        }

        if(tmp.getAction() == "DISCONNECT"){
            this->connectionHandler.terminate();
            data->setConected(false);
            connectionHandler.close();
            this->mutex.unlock();

        }


    }

    if (stomp.getStompCommand() == "MESSAGE"){
        Message mes = Message();

        // read all the headers and insert them to message
        for(auto s: stomp.getHeaders()){
            std::vector<std::string> vec_s = split(s,":");
            if(vec_s[0] == "id"){
                int sub_number = std::stoi(vec_s[1]);
                mes.setSubscription(sub_number);
            }
            if(vec_s[0] == "Message-id"){
                int mes_id = std::stoi(vec_s[1]);
                mes.setMessageId(mes_id);
            }
            if(vec_s[0] == "destination"){
                mes.setDes(vec_s[1]);
            }
        }
        // set the body of the message
        mes.setBody(stomp.getFrameBody());
        //insert message to client data
        data->getMessages().push_back(mes);

        messageProcceser(mes);
    }
}

// help function
std::vector<std::string> ReadFromServer::split(std::string s, std::string delimiter) {
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

Stomp ReadFromServer::toStomp(std::vector<std::string> s) {

    std::string command = s[0];
    std::vector <std::string> headers;
    int count = 1;
    while (s[count] != "") {
        headers.push_back(s[count]);
        count++;
    }
    std::string body=s[s.size()-2];



    return Stomp(command, headers, body);
}

void ReadFromServer::messageProcceser(Message &mes) {

    const std::string& body = mes.getBody();
    std::vector<std::string> words = split(body," ");

    // case 1: add
    if(words[1] == "has" && words[2] == "added"){
        std::cout << body <<  std::endl;//TODO: what to do?
    }


    // case 2.1: borrow
    if(words[1] == "wish"){
        if(words[0] != data->getName()){ // do only if it is not me that asking
            // merge book name into one string
            std::string bookName ="";
            for(int i = 4; i<words.size(); i++){
                bookName = bookName + words[i] ;
                if(i < words.size()-1){
                    bookName = bookName + + " ";
                }
            }

            //search for the book in the inventory
            bool is_exist = data->isBookExist(bookName);

            // send the server that the book is exist
            if(is_exist){
                std::string body = data->getName() + " has " + bookName;
                std::vector<std::string> header ;
                header.push_back("destination:" + mes.getDes());
                Stomp stomp = Stomp ("SEND" , header , body);
                connectionHandler.sendFrameAscii(stomp.toString(),'\0');
                //TODO: user the socket to send and syncroniez;
            }
        }
    }

    // case 2.2: borrow
    if(words[1] == "has" && words[2] != "added") {

        std::string bookName = "";
        for (int i = 2; i < words.size(); i++) {
            bookName = bookName + words[i];
            if (i < words.size() - 1) {
                bookName = bookName +" ";
            }
        }

        // add the book to the holder library if it is not the user itself
        if (data->getName() != words[0]) {
            if (data->findAndRemoveFromWishList(bookName)) {
                data->addBook(bookName, words[0], data->getName(), mes.getDes());
                // remember who gave me that book
                data->addToBorrowList(bookName,words[0]);

                std::string body = "Taking " + bookName + " from " + words[0];
                std::vector<std::string> header;
                header.push_back("destination:" + mes.getDes());
                Stomp stomp = Stomp("SEND", header, body);
                connectionHandler.sendFrameAscii(stomp.toString(), '\0');
            }
        }
    }

    // case 2.3: borrow

    if (words[0] == "Taking") {
        // TODO : CHECK WITH MORE CLIENTS
        std::string bookName = "";
        for (int i = 1; i < words.size() - 2; i++) {
            bookName = bookName + words[i];
            if (i < words.size() - 3) {
                bookName = bookName + +" ";
            }
        }
        if (data->getName() == words[words.size() - 1]) {
            data->removeBook(bookName);
        }
    }

    // case 3: return
    if (words[0] == "Returning") {

        // get the book name
        std::string bookName = "";
        for (int i = 1; i < words.size() -2; i++) {
            bookName = bookName + words[i];
            if (i < words.size() - 3) {
                bookName = bookName + +" ";
            }
        }
        if (this->data->getName() == words[words.size()-1]){
            std::string holder = data->getHolder(bookName);
            if (holder != ""){
                data->addBook(bookName,holder,data->getName(),mes.getDes());
                data->removeToBorrowList(bookName);
            } else{
                data->addBook(bookName,data->getName(),"",mes.getDes());
            }

        }
    }

    // case 4: status
    if (words[1] == "status") {
        std::vector<std::string> header ;
        header.push_back("destination:" + mes.getDes());
        std::string tmpBody = data->getBooksInGenere(mes.getDes());
        Stomp stomp = Stomp ("SEND" , header , tmpBody);
        connectionHandler.sendFrameAscii(stomp.toString(),'\0');
        // TODO print it?

    }
}


