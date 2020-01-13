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

    void addClub(int sub, const std::string& topic);
    void exitClub(int sub);
    int isUserInClub(const std::string& des);

    void addToWishList(const std::string& bookName);
    bool isBookExist(const std::string& bookName);
    bool findAndRemoveFromWishList(const std::string& bookName);

    void setName(const std::string &name);

    bool isConected() const;
    void setConected(bool conected);

    void addBook (const std::string& bookName , std::string holder , const std::string& borrower, const std::string& genre);
    void removeBook(const std::string& bookName);
    Book getBook(const std::string& bookName);
    std::string getBooksInGenere(const std::string& genre);

    void addToBorrowList(const std::string& book, const std::string& borrower);
    std::string getHolder(const std::string& name);
    void removeToBorrowList(const std::string& book);

    int getBookCounter() const;


};



#endif //BOOST_ECHO_CLIENT_USERDATA_H
