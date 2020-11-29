#include "../include/UDPSender.hpp"


UDPSender::UDPSender(/* args */)
{
}

int UDPSender::sendPacket(u_char* data, int length, std::string ipStr, u_short portNum)
{
    int this_fd, ret;
    struct sockaddr_in target_addr;
    this_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(this_fd < 0)
    {
        std::cout << "create socket failed" << std::endl;       
        return 0;
    }
    memset(&target_addr, 0, sizeof(target_addr));
    target_addr.sin_family = AF_INET;
    in_addr_t addr_dst;
    inet_aton(ipStr.c_str(), (in_addr*)&addr_dst);
    target_addr.sin_addr.s_addr = addr_dst;
    target_addr.sin_port = htons(portNum);
    char sndBuf[length];
    memset(sndBuf, 0, length);
    int len = sizeof(target_addr);
    memcpy(sndBuf, data, length);
    std::cout << "udp sndBuf: " << sndBuf << std::endl;
    sendto(this_fd, sndBuf, length, 0, (struct sockaddr*)&target_addr, len);
    close(this_fd);
}

UDPSender::~UDPSender()
{

}