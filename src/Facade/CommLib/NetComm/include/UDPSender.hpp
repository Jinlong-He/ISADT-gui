#ifndef UDPSender_hpp
#define UDPSender_hpp
#include <stdlib.h>
#include <string>
#include <iostream>
#include <memory.h>
#include <unistd.h>
#include <pcap/pcap.h>
#include <sys/socket.h>
#include <netinet/in.h>

class UDPSender
{
private:
    /* data */
public:
    
    UDPSender(/* args */);
    ~UDPSender();

    int sendPacket(u_char* data, int length, std::string ipStr, u_short portNum);

};





#endif // !UDPSender_hpp 