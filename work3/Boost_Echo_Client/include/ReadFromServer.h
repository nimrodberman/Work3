//
// Created by Nimrod on 07/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_READFROMSERVER_H
#define BOOST_ECHO_CLIENT_READFROMSERVER_H


#include "connectionHandler.h"
#include "Stomp.h"
#include "UserData.h"

class ReadFromServer {
public:
    ReadFromServer(UserData* u, ConnectionHandler con);
    void ReadFromServer::operator();

private:
    ConnectionHandler &connectionHandler;
    UserData* data;

    void decode(std::string in);
    std::vector<std::string> split(std::string s, std::string delimiter);
    Stomp toStomp(std::vector<std::string> s);

    void messageProcceser(Message& mes);

};


#endif //BOOST_ECHO_CLIENT_READFROMSERVER_H
