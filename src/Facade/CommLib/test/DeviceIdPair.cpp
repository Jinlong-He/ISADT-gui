#include "DeviceIdPair.h"


DeviceIdPair::DeviceIdPair(pcap_if_t* d, int id){
    this->d = d;
    this->id = id;
}

DeviceIdPair::~DeviceIdPair(){

}

pcap_if_t* DeviceIdPair::get_pcap_if(){
    return this->d;
}


int DeviceIdPair::get_id(){
    return this->id;
}