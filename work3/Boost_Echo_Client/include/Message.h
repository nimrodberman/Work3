//
// Created by Nimrod on 07/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_MESSAGE_H
#define BOOST_ECHO_CLIENT_MESSAGE_H


#include <string>

class Message {
public:

    Message();

    void setSubscription(int subscription);

    void setMessageId(int messageId);

    void setDes(const std::string &des);

    void setBody(const std::string &body);

    void setIsDone(bool isDone);

    int getSubscription() const;

    int getMessageId() const;

    const std::string &getDes() const;

    const std::string &getBody() const;


private:
    int Id;
    int static counter;
    int subscription;
    int message_id;
    std::string des;
    std::string body;
    bool isDone;
};


#endif //BOOST_ECHO_CLIENT_MESSAGE_H
