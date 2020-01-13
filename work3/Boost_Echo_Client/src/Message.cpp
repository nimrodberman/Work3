//
// Created by oronla@wincs.cs.bgu.ac.il on 11/01/2020.
//

#include "../include/Message.h"


Message::Message() {

}

void Message::setSubscription(int subscription1) {
    Message::subscription = subscription1;
}

void Message::setMessageId(int messageId) {
    message_id = messageId;
}

void Message::setDes(const std::string &des1) {
    Message::des = des1;
}

void Message::setBody(const std::string &body1) {
    Message::body = body1;
}

void Message::setIsDone(bool isDone1) {
    Message::isDone = isDone1;
}

int Message::getSubscription() const {
    return subscription;
}

int Message::getMessageId() const {
    return message_id;
}

const std::string &Message::getDes() const {
    return des;
}

const std::string &Message::getBody() const {
    return body;
}