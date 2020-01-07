//
// Created by Nimrod on 07/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_BOOK_H
#define BOOST_ECHO_CLIENT_BOOK_H


class Book {
private:
    Book(std::string name, std::string holder)
    std::string bookName;
    std::string holder;
    std::string borrower;
public:
    std::string getBookName();
    void changeHolder();
    void changeBorrower();



};


#endif //BOOST_ECHO_CLIENT_BOOK_H
