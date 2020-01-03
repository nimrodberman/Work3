//
// Created by oronla@wincs.cs.bgu.ac.il on 03/01/2020.
//

#ifndef WORK1_V2_STOMPTOBYTE_H
#define WORK1_V2_STOMPTOBYTE_H

#include "Stomp.h"


class StompToByte {
public:
    StompToByte(const Stomp &st);

private:
    Stomp st;
public:
    std::vector<char>stompToBytes (Stomp s) ;
};


#endif //WORK1_V2_STOMPTOBYTE_H
