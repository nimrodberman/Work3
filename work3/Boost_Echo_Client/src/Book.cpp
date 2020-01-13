//
// Created by oronla@wincs.cs.bgu.ac.il on 11/01/2020.
//

#include "../include/Book.h"

#include <utility>


void Book::setBookName(const std::string &bookName1) {
    Book::bookName = bookName1;
}

void Book::setHolder(const std::string &holder1) {
    Book::holder = holder1;
}

void Book::setBorrower(const std::string &borrower1) {
    Book::borrower = borrower1;
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

void Book::setGenre(const std::string &genre1) {
    Book::genre = genre1;
}

Book::Book(std::string name1, std::string holder1): bookName(std::move(name1)),holder(std::move(holder1)) {}
