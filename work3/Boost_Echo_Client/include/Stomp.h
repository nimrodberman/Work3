//
// Created by oronla@wincs.cs.bgu.ac.il on 11/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_STOMP_H
#define BOOST_ECHO_CLIENT_STOMP_H


#include <string>
#include <vector>

class Stomp {

private:
    std::string stompCommand;
    std::vector<std::string> headers;
    std::string frameBody;

public:
    Stomp(const std::string &stompCommand, const std::vector<std::string> &headers, const std::string &frameBody);


    std::string toString();

    const std::string getStompCommand() const;

    const std::vector<std::string> &getHeaders() const;

    const std::string &getFrameBody() const;

    virtual ~Stomp();

    std::vector<char> stompToByte();

};


#endif //BOOST_ECHO_CLIENT_STOMP_H
