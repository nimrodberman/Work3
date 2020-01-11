//
// Created by oronla@wincs.cs.bgu.ac.il on 11/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_BOOK_H
#define BOOST_ECHO_CLIENT_BOOK_H

#include <string>

class Book {
private:
    std::string bookName;
    std::string holder;
    std::string borrower;
    std::string genre;
public:
    Book(std::string name, std::string holder);

    void setBookName(const std::string &bookName);

    void setHolder(const std::string &holder);

    void setBorrower(const std::string &borrower);

    const std::string &getBookName() const;

    const std::string &getHolder() const;

    const std::string &getBorrower() const;

    const std::string &getGenre() const;

    void setGenre(const std::string &genre);

};

#endif //BOOST_ECHO_CLIENT_BOOK_H
