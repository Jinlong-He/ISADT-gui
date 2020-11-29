#pragma once
#ifndef DeviceIdPair_h
#define DeviceIdPair_h
#include <pcap.h>
class DeviceIdPair
{
public:
	DeviceIdPair(pcap_if_t* d, int id);
	~DeviceIdPair();
	pcap_if_t* get_pcap_if();
	int get_id();
private:
	pcap_if_t* d;
	int id;
};

#endif

