#ifndef EtherReceiver_hpp
#define EtherReceiver_hpp


#include <stdlib.h>
#include <iostream>
#include <memory.h>
#include <pcap.h>
#include <string>
#include "packet.hpp"
class EtherReceiver
{
private:
    /* data */
    u_char recvData[1000];
public:
    pcap_t* listenWithHandler(pcap_t* selectedAdp, pcap_handler handler, u_char* user);
    bpf_program* setDeviceFilter(pcap_if_t* d, pcap_t* opened, char* packetFilter);
    pcap_if_t* getDevice();
    u_char* getSmac();
    EtherReceiver();
    ~EtherReceiver();
};

#endif