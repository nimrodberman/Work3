cmake_minimum_required(VERSION 3.15)
project(work1_v2)

set(CMAKE_CXX_STANDARD 11)

add_executable(src connectionHandler.cpp echoClient.cpp Client.cpp ../include/Client.h Stomp.cpp ../include/Stomp.h StompToByte.cpp ../include/StompToByte.h UserData.cpp ../include/UserData.h Book.cpp ../include/Book.h Receipt.cpp ../include/Receipt.h Message.cpp ../include/Message.h ../include/BlockingQueue.cpp ../include/BlockingQueue.h ReadFromKeyboard.cpp ../include/ReadFromKeyboard.h ReadFromServer.cpp ../include/ReadFromServer.h)