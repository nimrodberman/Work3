//
// Created by oronla@wincs.cs.bgu.ac.il on 11/01/2020.
//

#include "../include/UserData.h"
#include "../include/Receipt.h"


UserData::UserData(): name(name), Books(Books), receipt(receipt), messages(messages), subscription(subscription),conected(false) {
    subscription = std::unordered_map<int , std::string>();
}

std::vector<Receipt> &UserData::getReceipt()  { //TODO SYNC
    return receipt;
}

std::vector<Message> &UserData::getMessages()  { //TODO SYNC
    return messages;
}

std::unordered_map<int, std::string> &UserData::getSubscription()  {
    return subscription;
}


Receipt UserData::findAndReturnReciept(int id) { //TODO SYNC
    for (auto s : receipt){
        if(s.getId() == id){
            return s;
        }
    }
}

const std::string &UserData::getName() const {
    return name;
}

std::list<Book> &UserData::getBooks()  {
    return Books;
}

void UserData::setConected(bool conected) {
    UserData::conected = conected;
}

bool UserData::isConected() const {
    return conected;
}

void UserData::addClub(int sub, std::string topic) { //TODO SYNC
    subscription.emplace(sub,topic);
}

void UserData::exitClub(int sub) { //TODO SYNC
    subscription.erase(sub);

}

void UserData::setName(const std::string &name) {
    UserData::name = name;
}

void UserData::addBook(std::string bookName, std::string holder, std::string borrower, std::string genre) {
    Book book = Book(bookName,holder);
    book.setBorrower(borrower);
    book.setGenre(genre);
    this->Books.push_back(book);

}





