

#include <cstdlib>
#include <iostream>
#include <thread>
#include "../include/connectionHandler.h"
#include "../include/UserData.h"
#include "../include/ReadFromKeyboard.h"
#include "../include/ReadFromServer.h"


/**
* This code assumes that the server replies the exact text the client sent it (as opposed to the practical session example)
*/
//help function
std::vector<std::string> split(const std::string& s, const std::string& delimiter) {
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

int main () {


    std::string command;
    std::string client_first_input;
    std::mutex mutex_connectionhandler;
    std::mutex mutex_userData;
    std::mutex mutex_logout;
    std::mutex mutex_login;



    do {
        getline(std::cin,client_first_input);
        int spaceApp = client_first_input.find_first_of(' ', 0);
        command = client_first_input.substr(0,spaceApp);
        if (command == "login"){
            auto* data = new UserData(mutex_userData);
            std::vector<std::string> line = split(client_first_input, " ");
            std::vector<std::string> HP = split(line[1], ":");
            short port = std::stoi(HP[1]);
            ConnectionHandler connectionHandler(HP[0], port, mutex_connectionhandler);
            ReadFromKeyboard readFromKeyboard= ReadFromKeyboard(data , connectionHandler , client_first_input, mutex_logout,mutex_login);
            ReadFromServer readFromServer = ReadFromServer (data , connectionHandler, mutex_logout,mutex_login);

            std::thread th1(&ReadFromKeyboard::run, &readFromKeyboard);
            std::thread th2(&ReadFromServer::run, &readFromServer);
            th2.join();
            th1.join();

            delete(data);
        }
    }
    while( command != "exit" );

}


