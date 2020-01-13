//
// Created by oronla@wincs.cs.bgu.ac.il on 11/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_READFROMSERVER_H
#define BOOST_ECHO_CLIENT_READFROMSERVER_H


#include "connectionHandler.h"
#include "Stomp.h"
#include "Message.h"
#include "UserData.h"

class ReadFromServer {
public:
    ReadFromServer(UserData *data, ConnectionHandler &connectionHandler, std::mutex &mutex,std::mutex &mutex_login);
    void run();

private:
    ConnectionHandler &connectionHandler;
    UserData* data;

    void decode(const std::string& in);
    static std::vector<std::string> split(const std::string& s, const std::string& delimiter);
    static Stomp toStomp(std::vector<std::string> s);
    void messageProcceser(Message& mes);
    std::mutex & mutex;
    std::mutex & mutex_login;



};



#endif //BOOST_ECHO_CLIENT_READFROMSERVER_H
