//
// Created by oronla@wincs.cs.bgu.ac.il on 11/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_READFROMKEYBOARD_H
#define BOOST_ECHO_CLIENT_READFROMKEYBOARD_H


#include "connectionHandler.h"
#include "UserData.h"
#include "Receipt.h"

class ReadFromKeyboard{

public:
    ReadFromKeyboard(UserData *userData, ConnectionHandler &connectionHandler, std::string, std::mutex &mutex);
    void run();
    std::vector<std::string> split (std::string s , std::string delimiter);
    bool clientCommand();


private:
    ConnectionHandler &connectionHandler;
    std::string input;
    std::vector<std::string> headers;
    int countSubscription;
    int countReceipt;
    UserData* userData;
    std::mutex & mutex;

};

#endif //BOOST_ECHO_CLIENT_READFROMKEYBOARD_H
