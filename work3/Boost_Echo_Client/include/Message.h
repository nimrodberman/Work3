//
// Created by Nimrod on 07/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_MESSAGE_H
#define BOOST_ECHO_CLIENT_MESSAGE_H


class Message {
public:
    Message(int ID);

private:
    int id;
    bool isDone;
};


#endif //BOOST_ECHO_CLIENT_MESSAGE_H
