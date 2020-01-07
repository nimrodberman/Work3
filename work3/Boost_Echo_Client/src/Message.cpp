//
// Created by Nimrod on 07/01/2020.
//

#include "../include/Message.h"

Message::Message() {
    this->Id = counter;
    counter++;
}

void Message::setSubscription(int subscription) {
    Message::subscription = subscription;
}

void Message::setMessageId(int messageId) {
    message_id = messageId;
}

void Message::setDes(const std::string &des) {
    Message::des = des;
}

void Message::setBody(const std::string &body) {
    Message::body = body;
}

void Message::setIsDone(bool isDone) {
    Message::isDone = isDone;
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


