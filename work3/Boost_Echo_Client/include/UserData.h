//
// Created by Nimrod on 07/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_USERDATA_H
#define BOOST_ECHO_CLIENT_USERDATA_H


#include <vector>
#include <unordered_map>
#include "Book.h"
#include "Receipt.h"
#include "Message.h"

class UserData {
private:
    std::string name;
    std::vector<Book> Books;
    std::vector<Receipt> receipt;
    std::vector<Message> messages;
    std::unordered_map<int,std::string>  subscription;

public:
    const std::string &getName() const;

    std::vector<Book> &getBooks() ;
    std::vector<Receipt> &getReceipt() ;
    std::vector<Message> &getMessages() ;
    std::unordered_map<int, std::string> &getSubscription() ;

    void findAndProccesReciept(int id);
};


#endif //BOOST_ECHO_CLIENT_USERDATA_H
