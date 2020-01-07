//
// Created by Nimrod on 07/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_USERDATA_H
#define BOOST_ECHO_CLIENT_USERDATA_H


class UserData {
private:
    std::vector<Book> Books;
    std::vector<Receipt> receipt;
    std::vector<Messages> messages;

    std::BlockingQueue<Stomp> stompQueue;
    std::BlockingQueue<Object> MissionQueue;


};


#endif //BOOST_ECHO_CLIENT_USERDATA_H
