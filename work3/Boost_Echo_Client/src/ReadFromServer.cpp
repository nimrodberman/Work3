//
// Created by Nimrod on 07/01/2020.
//

#include "../include/ReadFromServer.h"
#include "../include/Stomp.h"
#include "../include/UserData.h"

void ReadFromServer::operator()() {
    std::string input;
    while (1) {
        if (!connectionHandler.getFrameAscii((std::string &)input, '\0')) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
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
        std::cout << "Login successful";
    }

    if (stomp.getStompCommand() == "RECEIPT"){
        std::string s  = stomp.getHeaders()[0];
        std::vector<std::string> vec_s = split(s,":");
        int id = std::stoi(vec_s[1]);
        data->findAndProccesReciept(id);
    }

    if (stomp.getStompCommand() == "MESSAGE"){
        Message mes = Message();

        // read all the headers and insert them to message
        for(auto s: stomp.getHeaders()){
            std::vector<std::string> vec_s = split(s,":");
            if(vec_s[1] == "subscription"){
                int sub_number = std::stoi(vec_s[1]);
                mes.setSubscription(sub_number);
            }
            if(vec_s[1] == "Message-id"){
                int mes_id = std::stoi(vec_s[1]);
                mes.setMessageId(mes_id);
            }
            if(vec_s[1] == "destination"){
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
    res.push_back("");

    while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

Stomp ReadFromServer::toStomp(std::vector<std::string> s) {
    int lines = s.size();
    std::string command = s[0];
    std::string body;
    std::vector <std::string> headers;
    int count = 1;
    while (count < lines) {
        if (s[count] != "\0" && s[count] == "\n" && s[count+1] == "\n"){
            body = s[count+2];
            break;
        }
        else {
            headers.push_back(s[count]);
        }
        count++;
    }
    return Stomp(command, headers, body);
}

void ReadFromServer::messageProcceser(Message &mes) {

    const std::string& body = mes.getBody();
    std::vector<std::string> words = split(body," ");

    // case 1: add
    if(words[1] == "has" && words[2] == "added"){
        std::cout << body;
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
            //TODO
        }
    }

    // case 2.2: borrow
    if(words[1] == "has" && words.size() == 3){
        //TODO : is it possible that will be already a book with that name?
        bool is_exist = false;
        // check if book is already exist
        for(Book book : data->getBooks()){
            if(book.getBookName() == words[4]){
                is_exist = true;
            }
        }
        if(!is_exist){
            data.
            //TODO message that i took

        }



    }

    // case 2.3: borrow
    if(words[0] == "Taking"){
        if(data.getname == words[3]){
            d
        }


    }

    // case 2.2: borrow
    if(words[1] == "has"){


    }


    // case 3: return
    if(words[0] == "Returning"){
        std::cout << body;
    }

    // case 4: status
    if(words[0] == "book"){
        std::cout << body;
    }





};



