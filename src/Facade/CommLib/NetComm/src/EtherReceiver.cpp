#include "../include/EtherReceiver.hpp"

pcap_t* EtherReceiver::listenWithHandler( pcap_t* selectedAdp,  pcap_handler handler, u_char* user)
{
    char errbuf[100];
	char* filter = (char*)"ether";
	pcap_loop(selectedAdp, 0, handler, user);
    return selectedAdp; 
}

bpf_program* EtherReceiver::setDeviceFilter(pcap_if_t* d, pcap_t* opened, char* packetFilter)
{
    struct bpf_program fcode;
	u_int netmask;
	bpf_program* fcodeptr = NULL;
	netmask = 0xffffff;
	if (pcap_compile(opened, &fcode, packetFilter, 1, netmask) < 0) {
		// unable to compile
		std::cout << "unable to compile" << std::endl;
	}
	else {

		fcodeptr = &fcode;
		return fcodeptr;
	}
	return fcodeptr;
}

pcap_if_t* EtherReceiver::getDevice()
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

EtherReceiver::EtherReceiver()
{

}

EtherReceiver::~EtherReceiver()
{

}