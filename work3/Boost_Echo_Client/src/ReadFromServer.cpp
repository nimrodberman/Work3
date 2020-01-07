//
// Created by Nimrod on 07/01/2020.
//

#include "../include/ReadFromServer.h"

void ReadFromServer::operator()() {
    char type[2];
    while (1) {

        if (!connectionHandler.getBytes(type, 2)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
        }

        decode(type);
        if (connectionHandler.isTerminate()) {
            std::cout << "Exiting...\n" << std::endl;
            break;
        }
    }



}
