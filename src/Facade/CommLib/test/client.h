#include <pcap/pcap.h>
#include <iostream>
#include <linux/types.h>
#include <arpa/inet.h>
#include <memory.h>
#include <list>
#include <thread>
#include "packet.h"
#include "DeviceIdPair.h"
using namespace std;
int gatewayFound = 0;
pcap_if_t* selectedIf;
pcap_t* selectedAdp;
bpf_program* fcode;

int main();
list<DeviceIdPair*> listAdaptor();

void ifprint(pcap_if_t* d, int selectId);
pcap_if_t* selectAdaptor(int id, list<DeviceIdPair*> list);


bpf_program* setDeviceFilter(pcap_if_t* d, pcap_t* opened, char* packetFilter) ;


void handle_ether_thread(u_char* param, const struct pcap_pkthdr* header, const u_char* packetData);

void handle_connection_thread(pcap_t* selectedAdp);

void find_gateway_thread(pcap_t* selectedAdp);