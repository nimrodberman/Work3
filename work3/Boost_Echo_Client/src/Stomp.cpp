//
// Created by oronla@wincs.cs.bgu.ac.il on 03/01/2020.
//

#include "../include/Stomp.h"


Stomp::~Stomp() {}

Stomp::Stomp(const std::string &stompCommand, const std::vector<std::string> &headers, const std::string &frameBody)
        : stompCommand(stompCommand), headers(headers), frameBody(frameBody) {}

std::string Stomp::toString() {
    std::string output = this->stompCommand + "\n";
    for (auto &h : this->headers){
        output += h + "\n";
    }
    output += "\n";

    output += this->frameBody += "\n";

    output += "\\u0000";
    return output;
}

const std::string &Stomp::getStompCommand() const {
    return stompCommand;
}

const std::vector<std::string> &Stomp::getHeaders() const {
    return headers;
}

const std::string &Stomp::getFrameBody() const {
    return frameBody;
}

std::vector<char> Stomp::stompToByte() {
    std::string tmp = this->toString();
    return std::vector<char> (tmp.begin(), tmp.end());
}





