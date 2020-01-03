//
// Created by oronla@wincs.cs.bgu.ac.il on 03/01/2020.
//

#include "../include/StompToByte.h"

StompToByte::StompToByte(const Stomp &st) : st(st) {}

std::vector<char> StompToByte::stompToBytes(Stomp s) {
    std::string tmp = s.toString();
    return std::vector<char> (tmp.begin(), tmp.end());
}
