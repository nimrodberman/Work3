//
// Created by oronla@wincs.cs.bgu.ac.il on 03/01/2020.
//

#include "../include/Client.h"
#include "../include/Stomp.h"

Client::Client() : countSubscription(0){}

void Client::clientCommand() {
    getline(std::cin,input);
    int spaceApp = input.find_first_of(' ', 0);
    std::string command = input.substr(0,spaceApp);
    this->input.substr(spaceApp,input.length());


    if(command == "login"){

    }
    if(command == "join"){
        this->headers = split(input," ");

        this->headers[0] = "SUBSCRIBE";

        subscription.insert({(int) 1, 3}); //TODO: insert
        this->headers[1]= "destination:" + this->headers[1];

        std::string s = std::to_string(this->countSubscription);
        s="id:"+s;
        this->headers[2]=s;
        this->countSubscription++;

        s = std::to_string(this->countReceipt);
        s="receipt:"+s;
        this->headers[3]=s;
        this->countReceipt++;

        Stomp stomp = Stomp(command,headers,"");
        stompQueue.push(stomp);

    }
    if(command == "add"){
        this->headers = split(input," ");

        this->headers[0] = "SEND";

        this->headers[1]= "destination:" + this->headers[1];

        std::string body =this->name + "has added the book" +this->headers[2];

        this->headers[2]="content-type:add";

        Stomp stomp = Stomp(command,headers,body);
        stompQueue.push(stomp);

    }
    if(command == "borrow"){ //TODO: borrow 2,3
        this->headers = split(input," ");

        this->headers[0] = "SEND";

        this->headers[1]= "destination:" + this->headers[1];

        std::string body =this->name + "wish to borrow" +this->headers[2];

        this->headers[2]="content-type:borrow";

        Stomp stomp = Stomp(command,headers,body);
        stompQueue.push(stomp);

    }

    if(command == "return"){
        this->headers = split(input," ");

        this->headers[0] = "SEND";

        this->headers[1]= "destination:" + this->headers[1];

        std::string body = "Returning" + this->headers[2] + "to" + this->name;

        this->headers[2]="content-type:return";

        Stomp stomp = Stomp(command,headers,body);
        stompQueue.push(stomp);
    }
    if(command == "status")
    {

    }
    if(command == "logout") {
        this->headers[0] = "DISCONNECT";
        std::string s = std::to_string(this->countReceipt);
        s="receipt:"+s;
        this->headers[1] = s ;

        Stomp stomp = Stomp(command,headers,"");
        stompQueue.push(stomp);
    }
}

std::vector<std::string> Client::split(std::string s, std::string delimiter) {
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

Client::~Client() = default;


