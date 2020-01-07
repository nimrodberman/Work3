//
// Created by Nimrod on 07/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_RECIEPT_H
#define BOOST_ECHO_CLIENT_RECIEPT_H


#include <string>

class Receipt {
public:
    Receipt(const std::string &action, const std::string &topic);

private:
    int static counter;
    int id;
    std::string action;
    std::string topic;

public:
    static int getCounter();
    int getId() const;
    const std::string &getAction() const;
    void Procces();

};


#endif //BOOST_ECHO_CLIENT_RECIEPT_H
