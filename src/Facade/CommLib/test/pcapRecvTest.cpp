#include <pcap/pcap.h>
#include <iostream>
#include <linux/types.h>
#include <arpa/inet.h>
#include <memory.h>
#include <list>
#include <thread>
#include "packet.h"

using namespace std;

void getPacket(u_char * arg, const struct pcap_pkthdr * pkthdr, const u_char * packet){
    ether_header* eh = (ether_header*)packet;
    if(ntohs(eh->type) == 0x888f){

        cout << "get ether packet" << endl;
    }
}

int main(){
    char errbuf[100], *devStr;
    devStr = pcap_lookupdev(errbuf);
    if(!devStr){
        cout << "lookup failed" << endl;
        exit(-1);
    }
    pcap_t *device = pcap_open_live(devStr, 65535, 1, 0, errbuf);
    if(!device){
        cout << "open failed" << endl;
        exit(-1);
    }
    struct bpf_program filter;
    pcap_compile(device, &filter, "ether", 1, 0);
    pcap_setfilter(device, &filter);
    int id = 0;
    pcap_loop(device, -1, getPacket, (u_char*)&id);

    pcap_close(device);
    return 0;
}

