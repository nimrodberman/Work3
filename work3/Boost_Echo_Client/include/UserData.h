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
    std::string name;
    std::list<Book> Books;
    //std::list<std::string> wishList;
    std::vector<Receipt> receipt;
    std::vector<Message> messages;
    std::unordered_map<int , std::string>  subscription;
    bool conected;

public:
    UserData();
    std::list<Book> &getBooks();
    const std::string &getName() const;
    std::vector<Receipt> &getReceipt() ;
    std::vector<Message> &getMessages() ;
    std::unordered_map<int, std::string> &getSubscription() ;
    Receipt findAndReturnReciept(int id);


    void addClub(int sub, std::string topic);
    void exitClub(int sub);

    //void addToWishList();
    //bool findAndRemoveFromWishList();

    void setName(const std::string &name);

    bool isConected() const;

    void setConected(bool conected);

    void addBook (std::string bookName , std::string holder , std::string borrower, std::string genre);

};



#endif //BOOST_ECHO_CLIENT_USERDATA_H
