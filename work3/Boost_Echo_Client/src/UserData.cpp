//
// Created by oronla@wincs.cs.bgu.ac.il on 11/01/2020.
//

#include "../include/UserData.h"
#include "../include/Receipt.h"


UserData::UserData(std::mutex &mutex):bookCounter(0), name(name), Books(Books), receipt(receipt), messages(messages), subscription(subscription),conected(false), mutex(mutex){
    subscription = std::unordered_map<int , std::string>();
    Books = std::unordered_map<std::string, Book>();
    borrowList = std::unordered_map<std::string , std::string>();
}

std::vector<Receipt> &UserData::getReceipt()  { // only read - no need for syn TODO true?
    return receipt;
}

std::vector<Message> &UserData::getMessages()  { // only read - no need for syn TODO true?
    return messages;
}




Receipt UserData::findAndReturnReciept(int id) {
    std::lock_guard<std::mutex> lock(mutex);
    for (auto s : receipt){
        if(s.getId() == id){
            return s;
        }
    }
}

const std::string &UserData::getName() const {
    std::lock_guard<std::mutex> lock(mutex);
    return name;
}

std::unordered_map<std::string,Book> &UserData::getBooks()  {
    std::lock_guard<std::mutex> lock(mutex);
    return Books;
}

void UserData::setConected(bool conected) {
    std::lock_guard<std::mutex> lock(mutex);
    UserData::conected = conected;
}

bool UserData::isConected() const {
    std::lock_guard<std::mutex> lock(mutex);
    return conected;
}

void UserData::addClub(int sub, std::string topic) {
    subscription.insert({sub,topic});
}

void UserData::exitClub(int sub) {
    subscription.erase(sub);

}

void UserData::setName(const std::string &name) {
    std::lock_guard<std::mutex> lock(mutex);
    UserData::name = name;
}

void UserData::addBook(std::string bookName, std::string holder, std::string borrower, std::string genre) {
    std::lock_guard<std::mutex> lock(mutex);
    Book book = Book(bookName,holder);
    book.setBorrower(borrower);
    book.setGenre(genre);
    bookCounter++;
    this->Books.insert({bookName,book});

}
`
void UserData::addToWishList(std::string bookName) {
    std::lock_guard<std::mutex> lock(mutex);
    wishList.push_back(bookName);

}

bool UserData::findAndRemoveFromWishList(std::string bookName) {
    std::lock_guard<std::mutex> lock(mutex);
    for(auto book : wishList){
        if(book == bookName){
            wishList.remove(book);
            return true;
        }
    }
    return false;
}

void UserData::removeBook(std::string bookName) {
    std::lock_guard<std::mutex> lock(mutex);
    bookCounter--;
    this->Books.erase(bookName);
}

bool UserData::isBookExist(std::string bookName) {
    std::lock_guard<std::mutex> lock(mutex);
    for(auto book : Books){
        if(book.second.getBookName() == bookName){
            return true;
        }
    }
    return false;
}

Book UserData::getBook(std::string bookName) {
    std::lock_guard<std::mutex> lock(mutex);
    return Books.find(bookName)._M_cur->_M_v().second;
}

int UserData::getBookCounter() const {
    std::lock_guard<std::mutex> lock(mutex);
    return bookCounter;
}

std::string UserData::getBooksInGenere(std::string genre) {
    std::lock_guard<std::mutex> lock(mutex);
    std::string body = name + ": ";
    int i = 0;
    for(auto &b : Books){
        i++;
        if(b.second.getGenre() == genre)
            body = body + b.first;
        if(i<bookCounter)
            body = body + ",";
    }
    return  body;
}

int UserData::isUserInClub(std::string des) {
    std::lock_guard<std::mutex> lock(mutex);
    int subscription_id =-1;

    for (auto s : subscription){
        if(s.second == des){
            subscription_id=s.first;
            subscription_id;
        }
    }
    return subscription_id;

}

void UserData::addToBorrowList(std::string book, std::string borrower) {
    std::lock_guard<std::mutex> lock(mutex);
    borrowList.insert({book,borrower});

}

std::string UserData::getHolder(std::string bookname) {
    std::lock_guard<std::mutex> lock(mutex);
    std::string ans ="";
    for(auto& s: borrowList){
        if(bookname == s.second){
            return  s.second;
        }
    }
    return ans;
}

void UserData::removeToBorrowList(std::string book) {
    std::lock_guard<std::mutex> lock(mutex);
    borrowList.erase(book);
}










