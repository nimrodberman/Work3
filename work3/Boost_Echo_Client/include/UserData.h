//
// Created by oronla@wincs.cs.bgu.ac.il on 11/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_USERDATA_H
#define BOOST_ECHO_CLIENT_USERDATA_H


#include <vector>
#include <unordered_map>
#include "Book.h"
#include "Message.h"
#include "Receipt.h"
#include <list>
#include <boost/asio/ip/tcp.hpp>

using boost::asio::ip::tcp;


class UserData {
private:
    int bookCounter;
    std::string name;
    std::unordered_map<std::string,Book> Books;
    std::list<std::string> wishList;
    std::vector<Receipt> receipt;
    std::vector<Message> messages;
    std::unordered_map<int , std::string>  subscription;
    bool conected;
    std::unordered_map<std::string , std::string>  borrowList;
    std::mutex & mutex;

public:
    UserData(std::mutex &mutex);
    std::unordered_map<std::string,Book> &getBooks();
    const std::string &getName() const;
    std::vector<Receipt> &getReceipt() ;
    std::vector<Message> &getMessages() ;

    Receipt findAndReturnReciept(int id);

    void addClub(int sub, std::string topic);
    void exitClub(int sub);
    int isUserInClub(std::string des);

    void addToWishList(std::string bookName);
    bool isBookExist(std::string bookName);
    bool findAndRemoveFromWishList(std::string bookName);

    void setName(const std::string &name);

    bool isConected() const;
    void setConected(bool conected);

    void addBook (std::string bookName , std::string holder , std::string borrower, std::string genre);
    void removeBook(std::string bookName);
    Book getBook(std::string bookName);
    std::string getBooksInGenere(std::string genre);

    void addToBorrowList(std::string book, std::string borrower);
    std::string getHolder(std::string name);
    void removeToBorrowList(std::string book);

    int getBookCounter() const;


};



#endif //BOOST_ECHO_CLIENT_USERDATA_H
