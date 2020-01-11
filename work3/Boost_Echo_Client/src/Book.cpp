//
// Created by oronla@wincs.cs.bgu.ac.il on 11/01/2020.
//

#include "../include/Book.h"


void Book::setBookName(const std::string &bookName) {
    Book::bookName = bookName;
}

void Book::setHolder(const std::string &holder) {
    Book::holder = holder;
}

void Book::setBorrower(const std::string &borrower) {
    Book::borrower = borrower;
}

const std::string &Book::getBookName() const {
    return bookName;
}

const std::string &Book::getHolder() const {
    return holder;
}

const std::string &Book::getBorrower() const {
    return borrower;
}

const std::string &Book::getGenre() const {
    return genre;
}

void Book::setGenre(const std::string &genre) {
    Book::genre = genre;
}

Book::Book(std::string name, std::string holder): bookName(name),holder(holder) {

}
