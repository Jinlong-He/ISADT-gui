#ifndef UDPReceiver_hpp
#define UDPReceiver_hpp
#include <stdlib.h>
#include <string>
#include <iostream>
#include <memory.h>
#include <unistd.h>
#include <sys/socket.h>
#include "pcap.h"

class UDPReceiver
{
private:
    u_char dstData[1000];
public:
    UDPReceiver(/* args */);
    ~UDPReceiver();

    int receivePacket(u_char* dst, std::string ipStr, u_short portNum);


};


#endif