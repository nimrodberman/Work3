//
// Created by oronla@wincs.cs.bgu.ac.il on 03/01/2020.
//

#include "../include/Client.h"
#include "../include/Stomp.h"

Client::Client() : countSubscription(0){}







// help function
std::vector<std::string> Client::split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;
    res.push_back("");

    while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

Client::~Client() = default;


