//
// Created by Nimrod on 07/01/2020.
//

#include <iostream>
#include "../include/Receipt.h"

Receipt::Receipt(const std::string &action, const std::string &topic) : action(action), topic(topic) {}

int Receipt::getCounter() {
    return counter;
}

int Receipt::getId() const {
    return id;
}

const std::string &Receipt::getAction() const {
    return action;
}

void Receipt::Procces() {
    if (action == "SUBSCRIBE"){
        std::cout << "Joined club " << topic << "\n";
    }

    if(action == "DISCONNECT"){
        std::cout << "Disconnecting...";
        // TODO: Close the socket
    }
}


