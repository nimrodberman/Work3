//
// Created by oronla@wincs.cs.bgu.ac.il on 03/01/2020.
//

#ifndef WORK1_V2_CLIENT_H
#define WORK1_V2_CLIENT_H


#include <queue>
#include <bits/unordered_map.h>
#include "connectionHandler.h"
#include "Stomp.h"

class Client {

private:
    std::vector <std::string> headers;
    std::string input;
    std::unordered_map<int,std::string>  subscription;
    std::string name;
    int countSubscription;
    int countReceipt;


public:
    Client();    //constructor
    virtual ~Client();    //destructor



    void clientCommand();
    static std::vector<std::string> split(std::string s , std::string delimiter);
};


#endif //WORK1_V2_CLIENT_H
