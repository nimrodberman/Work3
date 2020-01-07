//
// Created by Nimrod on 07/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_READFROMKEYBOARD_H
#define BOOST_ECHO_CLIENT_READFROMKEYBOARD_H

#include "connectionHandler.h"
#include "UserData.h"

class ReadFromKeyboard{

public:
    ReadFromKeyboard(UserData *userData, ConnectionHandler &connectionHandler);
    void operating();
    std::vector<std::string> split (std::string s , std::string delimiter);
    bool clientCommand();

private:
    ConnectionHandler &connectionHandler;
    std::string input;
    std::vector<std::string> headers;
    int countSubscription;
    UserData* userData;

};

#endif //BOOST_ECHO_CLIENT_READFROMKEYBOARD_H
