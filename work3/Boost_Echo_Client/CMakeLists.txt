cmake_minimum_required(VERSION 3.15)
project(Boost_Echo_Client)

set(CMAKE_CXX_STANDARD 11)

add_executable(Boost_Echo_Client  ../src/Client.cpp  ../src/connectionHandler.cpp ../include/connectionHandler.h  ../src/Book.cpp ../include/Book.h
        ../src/Message.cpp  ../include/Message.h  ../src/ReadFromKeyboard.cpp  ../include/ReadFromKeyboard.h   ../src/Receipt.cpp  ../include/Receipt.h
        ../src/Stomp.cpp  ../include/Stomp.h   ../src/UserData.cpp  ../include/UserData.h   ../src/ReadFromServer.cpp  ../include/ReadFromServer.h)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")


find_package(Boost 1.65.1 REQUIRED COMPONENTS
        date_time filesystem iostreams system)

find_package(Threads)

target_link_libraries(Boost_Echo_Client Boost::date_time Boost::filesystem
        Boost::iostreams Boost::system)