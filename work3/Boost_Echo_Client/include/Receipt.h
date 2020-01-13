//
// Created by oronla@wincs.cs.bgu.ac.il on 11/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_RECEIPT_H
#define BOOST_ECHO_CLIENT_RECEIPT_H

#include <string>
#include <vector>
#include "connectionHandler.h"


class Receipt {
public:
    Receipt(int id,int subscriptionId, std::string action, std::string topic, ConnectionHandler &connectionHandler);


private:

    int id;
    int subscription_id;
    std::string action;
    std::string topic;
    ConnectionHandler &connectionHandler;

public:
    static int getCounter();
    int getId() const;

    const std::string &getTopic() const;
    const std::string &getAction() const;

    int getSubscriptionId() const;

};



#endif //BOOST_ECHO_CLIENT_RECEIPT_H
