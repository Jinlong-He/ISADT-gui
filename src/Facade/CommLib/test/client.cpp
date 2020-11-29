// Client.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "client.h"
int main()
{
	list<DeviceIdPair*> list = listAdaptor();
	int id;
	cout << "select adaptor: ";
	cin >> id;
	int start = 0;
	while (start != 1) {
		cout << "start?: ";
		cin >> start;
	}
	cout << "select adaptor" << endl;
	selectedIf = selectAdaptor(id, list);
	cout << "selectedIfNull:" << (selectedIf == nullptr) << endl;
	char errbuf[100];

	cout << "listen live" << endl;
	cout << "selectedIfName:" << selectedIf->name << endl;
	selectedAdp = pcap_open_live(selectedIf->name, 65536, 1, 1, errbuf);

	cout << "selectedadpNull:" << (selectedAdp == nullptr) << endl;
	cout << "errbuf: " << errbuf << endl;
	char* filter = (char*)"ether";

	cout << "set filter" << endl;
	fcode = setDeviceFilter(selectedIf, selectedAdp, filter);
	pcap_setfilter(selectedAdp, fcode);
	cout << "thread" << endl;
	thread findThd(&find_gateway_thread, selectedAdp);
	findThd.join();
}

list<DeviceIdPair*> listAdaptor()
{
	list<DeviceIdPair*> list;
	pcap_if_t* alldevs;
	pcap_if_t* d;
	int adapNum = 0;
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_findalldevs(&alldevs, errbuf);

	int selectId = 0;
	for (d = alldevs; d; d = d->next) {
		if(d->description){
			DeviceIdPair* pair = new DeviceIdPair(d, selectId);
			list.push_back(pair);
			cout << "selectId: " << selectId << " " << d->description << endl;
			selectId ++;
		} else {
			cout << "des not allowed" << endl;
		}
		
	}

	//pcap_freealldevs(alldevs);
	return list;
}

void ifprint(pcap_if_t* d, int selectId) {

	cout << "here" << endl;
	u_int32_t net_ip = ((struct sockaddr_in*)d->addresses->addr)->sin_addr.s_addr;

	cout << "here" << endl;
	//u_int32_t net_mask = ((struct sockaddr_in*)d->addresses->netmask)->sin_addr.s_addr;
	struct in_addr net_ip_address;
	struct in_addr net_mask_address;
	char errbuf[PCAP_ERRBUF_SIZE];
	char ip6str[128];
	cout << "\tSelect: " << selectId << endl;
	cout << "\t" << d->name << endl;
	if (d->description) {
		cout << "\tDescription: " << d->description << endl;
	}
	cout << "\tLoopback: " << ((d->flags & PCAP_IF_LOOPBACK) ? "yes" : "no") << endl;

	net_ip_address.s_addr = net_ip;
	char* net_ip_str = inet_ntoa(net_ip_address);
	cout << "\tNet IP Address: " << net_ip_str << endl;
	//net_mask_address.s_addr = net_mask;
	char* net_mask_str = inet_ntoa(net_ip_address);
	cout << "\tNet Mask: \t" << net_mask_str << endl;
}

pcap_if_t* selectAdaptor(int id, list<DeviceIdPair*> list) {

	for (DeviceIdPair* p : list) {
		if (p->get_id() == id) {
			return p->get_pcap_if();
		}
	}
	cout << "Device id not found." << endl;
	return NULL;
}


bpf_program* setDeviceFilter(pcap_if_t* d, pcap_t* opened, char* packetFilter) {
	struct bpf_program fcode;
	bpf_u_int32 netmask;
	bpf_program* fcodeptr = NULL;
	if (d->addresses != NULL) {
		netmask = ((struct sockaddr_in*)(d->addresses->netmask))->sin_addr.s_addr;
	}
	else {
		netmask = 0xffffff;
	}
	cout << netmask << endl;
	cout << "pcap_compile" << endl;
	if(opened == nullptr){
		cout << "openedNull" << endl;
	}
	if (pcap_compile(opened, &fcode, packetFilter, 1, netmask) < 0) {
		cout << "unable to compile" << endl;
	}
	else {

		fcodeptr = &fcode;
		return fcodeptr;
	}
	cout << "pcap_compile end" << endl;
	return fcodeptr;
}



void handle_ether_thread(u_char* param, const struct pcap_pkthdr* header, const u_char* packetData) {
	ether_header* eh;
	eh = (ether_header*)packetData;
	if (ntohs(eh->type) == 0x888f) {
		cout << "Broadcast received" << endl;
		gateway_hello_packet* ghp = (gateway_hello_packet*)((u_char*)packetData + 14);
		cout << packetData << endl;
		cout << ghp->gateway_info.mac[0] << endl;
		if (ghp->gateway_id == 0x8) {
			cout << "id correct" << endl;
			gatewayFound = 1;
			thread th(&handle_connection_thread, selectedAdp);
			th.join();
		}
	}
}

void handle_connection_thread(pcap_t* selectedAdp) {
	ether_header eh;
	auth_start_packet authStart;
	eh.type = htons(0x888f);
	for (int i = 0; i < 6; i++) {
		eh.h_dest[i] = 0xff;
		eh.h_dest[i] = 0x22;
	}
	authStart.auth_hdr.type = 2;
	authStart.client_id = 0x1;
	for (int i = 0; i < 6; i++) {
		authStart.client_info.mac[i] = 0x22;
	}
	authStart.gateway_id = 0x8;
	char sndBuf[200];
	int index = 0;
	memcpy(sndBuf, &eh, sizeof(eh));
	index += sizeof(eh);
	memcpy(sndBuf, &authStart, sizeof(authStart));
	index += sizeof(authStart);
	cout << "auth start id: " << (int)authStart.client_id << " size: " << index << endl;
	if (pcap_sendpacket(selectedAdp, (u_char*)sndBuf, index) != 0) {
		cout << "send buf error" << endl;
	}
	cout << "send authStart successful" << endl;
	cout << sndBuf << endl;

}

void find_gateway_thread(pcap_t* selectedAdp) {
	while (!gatewayFound) {
		pcap_loop(selectedAdp, 1, handle_ether_thread, NULL);
	}
}

