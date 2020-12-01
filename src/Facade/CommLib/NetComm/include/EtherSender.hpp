#ifndef EtherSender_hpp
#define EtherSender_hpp


#include <stdlib.h>
#include <iostream>
#include <memory.h>
#include <pcap.h>
#include <string>
#include "packet.hpp"
class EtherSender
{
private:
    /* data */
    u_char smac[6];
public:
    int sendEtherBroadcast(u_char* data, int length);
    int sendEtherWithMac(u_char* data, int length, u_char dmac[6]);
    int sendEtherPacketWithDevice(u_char* data, int length, u_char dmac[6], char* if_name, pcap_if_t* selectedIf);
    pcap_if_t* getDevice();
    u_char* getSmac();
    EtherSender(u_char smac[6]);
    ~EtherSender();
};

#endif