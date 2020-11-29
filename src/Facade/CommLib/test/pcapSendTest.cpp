#include <pcap.h>
#include <iostream>
#include <linux/types.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <memory.h>
#include <list>
#include <thread>
#include "packet.h"

using namespace std;

void getPacket(u_char * arg, const struct pcap_pkthdr * pkthdr, const u_char * packet){
    cout << "get ether packet" << endl;
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
    u_char* snd_buf = (u_char*)malloc(1024*sizeof(u_char));
    memset(snd_buf, 0, 1024);
    ether_header eh;
    memset(&eh, 0, sizeof(eh));
    for(int i = 0; i < 6; i ++){
        eh.h_dest[i] = 0xff;
        eh.h_source[i] = 0x11;
    }
    eh.type = htons(0x888f);
    int i = 0;
    cout << "ether size: " << sizeof(eh) << endl;
    memcpy(snd_buf + i, &eh, 14);
    i += sizeof(eh);
    struct auth_header ah;
    memset(&ah, 0, sizeof(ah));
    ah.type = 0;
    ah.version = 0;
    memcpy(snd_buf + i, &ah, sizeof(ah));
    i += sizeof(ah);
    cout << i << endl;
    if(i < 42){
        i = 42;
    }
    cout << "size: " << i << endl;
    while(true){
        cout << "send" << endl;
        sleep(1);
        pcap_sendpacket(device, snd_buf, i);   
    }
    free(snd_buf);
    return 0;
}

