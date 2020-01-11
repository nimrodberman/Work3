//
// Created by oronla@wincs.cs.bgu.ac.il on 11/01/2020.
//

#include "../include/ReadFromServer.h"
#include "../include/Stomp.h"
#include "../include/UserData.h"
#include "../include/Message.h"


ReadFromServer::ReadFromServer(UserData *data, ConnectionHandler &connectionHandler)
        : connectionHandler(connectionHandler), data(data) {};



void ReadFromServer::run() {

    while (1) {
        std::string input;
        if (data->isConected() && !connectionHandler.getFrameAscii((std::string &)input, '\0')) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            data->setConected(false); // TODO:: think if it is killinig something?
            break;
        }

        decode(input);
        if (connectionHandler.isTerminate()) {
            std::cout << "Exiting...\n" << std::endl;
            break;
        }
    }



}

void ReadFromServer::decode(std::string in) {
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
            data->getSubscription().erase(tmp.getSubscriptionId());
            std::cout << "Exited club " << tmp.getTopic() << "\n";
        }

        if(tmp.getAction() == "DISCONNECT"){
            std::cout << "Disconnecting...";
            this->connectionHandler.terminate();
            connectionHandler.close();
            // TODO: Close the socket
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
        //search for the book in the inventory
        bool is_exist = false;
        for(Book book : data->getBooks()){
            if(book.getBookName() == words[4]){
                is_exist = true;
            }
        }

        // send the server that the book is exist
        if(is_exist){
            std::string body = data->getName() + " has " + words[4] ;
            std::vector<std::string> header ;
            header[0] = mes.getDes();
            Stomp stomp = Stomp ("SEND" , header , body);
            connectionHandler.sendBytes(&stomp.stompToByte()[0], stomp.toString().size());
            //TODO: user the socket to send and syncroniez;
        }
    }

    // case 2.2: borrow
    if(words[1] == "has" && words.size() == 3){
        //TODO : is it possible that will be already a book with that name?
        bool is_exist = false;
        // check if book is already exist
        for(Book book : data->getBooks()){
            if(book.getBookName() == words[2]){
                is_exist = true;
            }
        }
        Book toAdd = Book(words[2],words[0]);
        toAdd.setBorrower(data->getName());
        if(!is_exist){
            data->getBooks().push_back(toAdd);
            std::string body = "Taking " + words[2] + " from " + words[0] ;
            std::vector<std::string> header ;
            header[0] = mes.getDes();
            Stomp stomp = Stomp ("SEND" , header , body);
            connectionHandler.sendBytes(&stomp.stompToByte()[0], stomp.toString().size());
        }
    }

    // case 2.3: borrow
    if(words[0] == "Taking"){
        if(data->getName() == words[3]){
            for(auto s: data->getBooks()){
                if(s.getBookName() == words[1]){
                    //data.getBooks().remove(s); // TODO:deletion
                }
            }
        }
    }

    // case 3: return
    if(words[0] == "Returning"){
        if (this->data->getName() == words[3]){
            this->data->getBooks().emplace_back(words[1],this->data->getName());
        }
    }

    // case 4: status
    if(words[0] == "book"){
        std::vector<std::string> header ;
        header[0] = mes.getDes();
        std::string body = data->getName() + ":";

        for(auto b : data->getBooks()){
            body+=b.getBookName() + ",";
        }
        body.substr(0,body.size()-2);

        Stomp stomp = Stomp ("SEND" , header , body);
        connectionHandler.sendBytes(&stomp.stompToByte()[0], stomp.toString().size());
    }

}


