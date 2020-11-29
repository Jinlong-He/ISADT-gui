#include "../include/EtherSender.hpp"

int EtherSender::sendEtherBroadcast(u_char* data, int length)
{
    char errbuf[PCAP_ERRBUF_SIZE];
    char* if_name = pcap_lookupdev(errbuf);
    std::cout << "lookup" << std::endl;
    u_char dmac[6];
    for(int i = 0; i < 6; i ++)
    {
        dmac[i] = 0xff;
    }
    pcap_if_t* selectedIf = this->getDevice();
    std::cout << "getDevice" << std::endl;
    return this->sendEtherPacketWithDevice(data, length, dmac, if_name, selectedIf);
    
}


int EtherSender::sendEtherWithMac(u_char* data, int length, u_char dmac[6])
{
    char errbuf[PCAP_ERRBUF_SIZE];
    char* if_name = pcap_lookupdev(errbuf);
    std::cout << if_name << std::endl;
    pcap_if_t* selectedIf = this->getDevice();
    return this->sendEtherPacketWithDevice(data, length, dmac, if_name, selectedIf);

}

int EtherSender::sendEtherPacketWithDevice(u_char* data, int length, u_char dmac[6], char* if_name, pcap_if_t* selectedIf)
{
    std::cout << "sendEtherPacket" << std::endl;
    char errbuf[PCAP_ERRBUF_SIZE];
    std::cout << "pcap open" << std::endl;
    pcap_t* selectedAdp = pcap_open_live(if_name, 65536, 1, 1000, errbuf);
    std::cout << "pcap open over" << std::endl;
    ether_header eh;
	for (int i = 0; i < 6; i++) {
		eh.h_dest[i] = dmac[i];
		// set to broadcast
		eh.h_source[i] = this->getSmac()[i];
	}
	eh.type = htons(0x888f);
    char sndBuf[3000];
	int index = 0;
	memcpy(sndBuf, &eh, sizeof(ether_header));
	index = sizeof(ether_header);
	memcpy(&sndBuf[index], data, length);
	index += length;
    for(int i = 0; i < 14; i++){
        std::cout << std::hex << (unsigned short)((char*)&eh)[i] << std::endl;
    }
    std::cout << "Send ether packet: " << "length = " << index << ", from = " << smac << ", to = " << dmac << std::endl;
    return pcap_sendpacket(selectedAdp, (u_char*)sndBuf, index);
}

pcap_if_t* EtherSender::getDevice()
{
    char errbuf[PCAP_ERRBUF_SIZE];
    char *if_name = pcap_lookupdev(errbuf);
    pcap_if_t* selectedIf = nullptr;
    pcap_if_t* alldevs;
    pcap_if_t* d;
    pcap_findalldevs(&alldevs, errbuf);
    for(d = alldevs; d; d = d->next)
    {
        if(!strcmp(if_name, d->name))
        {
            selectedIf = d;
            break;
        }
    }
    return selectedIf;
}

u_char* EtherSender::getSmac()
{
    return this->smac;
}

EtherSender::EtherSender(u_char smac[6])
{
    memcpy(this->smac, smac, 6);
}


EtherSender::~EtherSender()
{

}
