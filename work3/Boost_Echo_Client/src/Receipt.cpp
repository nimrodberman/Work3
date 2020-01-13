//
// Created by oronla@wincs.cs.bgu.ac.il on 11/01/2020.
//

#include <iostream>
#include <utility>
#include "../include/Receipt.h"


Receipt::Receipt(int id,int subscriptionId, std::string action, std::string topic,
                 ConnectionHandler &connectionHandler) : id(id), subscription_id(subscriptionId), action(std::move(action)), topic(std::move(topic)),
                                                         connectionHandler(connectionHandler) {}

int Receipt::getCounter() {
    return 0;
}

int Receipt::getId() const {
    return id;
}

const std::string &Receipt::getAction() const {
    return action;
}


const std::string &Receipt::getTopic() const {
    return topic;
}

int Receipt::getSubscriptionId() const {
    return subscription_id;
}
