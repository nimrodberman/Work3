//
// Created by Nimrod on 07/01/2020.
//

#include "../include/UserData.h"

std::vector<Book> &UserData::getBooks()  {
    return Books;
}

std::vector<Receipt> &UserData::getReceipt()  {
    return receipt;
}

std::vector<Message> &UserData::getMessages()  {
    return messages;
}

std::unordered_map<int, std::string> &UserData::getSubscription()  {
    return subscription;
}


void UserData::findAndProccesReciept(int id) {
    for (auto s : receipt){
        if(s.getId() == id){
            s.Procces();
        }
    }
}

const std::string &UserData::getName() const {
    return name;
}


