cmake_minimum_required(VERSION 3.15)
project(work1_v2)

set(CMAKE_CXX_STANDARD 11)

add_executable(src connectionHandler.cpp echoClient.cpp Client.cpp ../include/Client.h Stomp.cpp ../include/Stomp.h StompToByte.cpp ../include/StompToByte.h)