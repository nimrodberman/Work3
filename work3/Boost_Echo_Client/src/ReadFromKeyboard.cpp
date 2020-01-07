//
// Created by Nimrod on 07/01/2020.
//

#include "../include/ReadFromKeyboard.h"

void ReadFromKeybord::operator()() {
    //getting line from keyboard

    while (!connectionHandler.isTerminate()) {
        getline(std::cin,input);
        {
            //encoding line and send them to server
            if (!clientCommand(input)) {
                std::cout << "Disconnected. Exiting...\n" << std::endl;
                break;
            }
            if (line == "LOGOUT" && connectionHandler.isLogedIn()) {
                break;
            }
        }
    }
    connectionHandler.setTerminate(true);
}

bool ReadFromKeyboard::clientCommand(std::string command) {
    input = command;
    int spaceApp = input.find_first_of(' ', 0);
    std::string command = input.substr(0,spaceApp);
    this->input.substr(spaceApp,input.length());


    if(command == "login"){//TODO: login frame

    }
    if(command == "join"){
        this->headers = split(input," ");
        this->headers[0] = "SUBSCRIBE";

        subscription.insert({(int) 1, 3}); //TODO: maintain the user data structer and add functionalleties as needed to any command
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
        StompToByte to_send = StompToByte(stomp);
        return connectionHandler.sendBytes(to_send.stompToBytes, stomp.size());

    }
    if(command == "add"){
        this->headers = split(input," ");

        this->headers[0] = "SEND";

        this->headers[1]= "destination:" + this->headers[1];

        std::string body =this->name + "has added the book" +this->headers[2];

        this->headers[2]="content-type:add";

        Stomp stomp = Stomp(command,headers,body);
        StompToByte to_send = StompToByte(stomp);
        return connectionHandler.sendBytes(to_send.stompToBytes, stomp.size());

    }
    if(command == "borrow"){ //TODO: borrow 2,3
        this->headers = split(input," ");

        this->headers[0] = "SEND";

        this->headers[1]= "destination:" + this->headers[1];

        std::string body =this->name + "wish to borrow" +this->headers[2];

        this->headers[2]="content-type:borrow";

        Stomp stomp = Stomp(command,headers,body);
        StompToByte to_send = StompToByte(stomp);
        return connectionHandler.sendBytes(to_send.stompToBytes, stomp.size());
    }

    if(command == "return"){
        this->headers = split(input," ");

        this->headers[0] = "SEND";

        this->headers[1]= "destination:" + this->headers[1];

        std::string body = "Returning" + this->headers[2] + "to" + this->name;

        this->headers[2]="content-type:return";

        Stomp stomp = Stomp(command,headers,body);
        StompToByte to_send = StompToByte(stomp);
        return connectionHandler.sendBytes(to_send.stompToBytes, stomp.size());
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
        StompToByte to_send = StompToByte(stomp);
        return connectionHandler.sendBytes(to_send.stompToBytes, stomp.size());
    }
}
