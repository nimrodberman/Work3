//
// Created by Nimrod on 07/01/2020.
//

#include "../include/ReadFromKeyboard.h"
#include "../include/Receipt.h"
#include "../include/Stomp.h"
#include "../include/UserData.h"

ReadFromKeyboard::ReadFromKeyboard(UserData *userData, ConnectionHandler &connectionHandler)
        : userData(userData), connectionHandler(connectionHandler) {
}

void ReadFromKeyboard::operating() {
    while (!connectionHandler.isTerminate()) {
        getline(std::cin,input);//TODO: getline
        {
            //encoding line and send them to server
            if (!clientCommand()) {
                std::cout << "Disconnected. Exiting...\n" << std::endl;
                break;
            }
            if (input == "LOGOUT" && connectionHandler.isLogedIn()) {
                break;
            }
        }
    }
    connectionHandler.setTerminate(true);
}

bool ReadFromKeyboard::clientCommand() {
    int spaceApp = input.find_first_of(' ', 0);
    std::string command = input.substr(0,spaceApp);
    this->input.substr(spaceApp,input.length());


    if(command == "login"){//TODO: version and host
        this->headers = split(input," ");
        this->input = "CONNECT";
        this->headers[3] = "passcode:" + this->headers[2];
        this->headers[2] = "login:" + this->headers[1];
        this->headers[1] = "host:";
        this->headers[0] = "version:";

        Stomp stomp = Stomp(this->input,headers,"");
        return connectionHandler.sendBytes(&stomp.stompToByte()[0] , stomp.toString().size());

    }
    if(command == "join"){
        this->headers = split(input," ");
        this->input = "SUBSCRIBE";

        Receipt receipt = Receipt(this->input , this->headers[0]);
        this->userData->getSubscription().insert({this->countSubscription , this->headers[0]});
        this->userData->getReceipt().push_back(receipt);
        this->countSubscription++;

        this->headers[0]= "destination:" + this->headers[0];
        this->headers[1]="id:" + std::to_string(this->countSubscription);
        this->headers[2]="receipt:" + std::to_string(receipt.getId());

        Stomp stomp = Stomp(this->input,headers,"");
        return connectionHandler.sendBytes(&stomp.stompToByte()[0] , stomp.toString().size());

    }
    if(command == "add"){
        this->headers = split(input," ");
        this->input = "SEND";

        this->headers[0]= "destination:" + this->headers[0];
        std::string body =this->userData->getName() + "has added the book" +this->headers[1];

        Stomp stomp = Stomp(command,headers,body);
        return connectionHandler.sendBytes(&stomp.stompToByte()[0], stomp.toString().size());

    }
    if(command == "borrow"){
        this->headers = split(input," ");
        this->input = "SEND";

        this->headers[0]= "destination:" + this->headers[0];
        std::string body =this->userData->getName() + "wish to borrow" +this->headers[1];

        Stomp stomp = Stomp(command,headers,body);
        return connectionHandler.sendBytes(&stomp.stompToByte()[0], stomp.toString().size());
    }

    if(command == "return"){
        this->headers = split(input," ");
        this->input = "SEND";

        this->headers[0]= "destination:" + this->headers[0];
        std::string body = "Returning" + this->headers[1] + "to" + this->userData->getName();

        Stomp stomp = Stomp(command,headers,body);
        return connectionHandler.sendBytes(&stomp.stompToByte()[0], stomp.toString().size());
    }

    if(command == "status"){
        this->headers = split(input," ");
        this->input = "SEND";

        this->headers[0]= "destination:" + this->headers[0];
        std::string body = "book status";

        Stomp stomp = Stomp(command,headers,body);
        return connectionHandler.sendBytes(&stomp.stompToByte()[0], stomp.toString().size());

    }
    if(command == "logout") {
        this->input = "DISCONNECT";

        Receipt receipt = Receipt(this->input , this->headers[0]);
        this->userData->getSubscription().insert({this->countSubscription , this->headers[0]});
        this->userData->getReceipt().push_back(receipt);
        this->countSubscription++;

        this->headers[1] = "receipt:" + std::to_string(receipt.getId()) ;

        Stomp stomp = Stomp(command,headers,"");
        return connectionHandler.sendBytes(&stomp.stompToByte()[0], stomp.toString().size());
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


