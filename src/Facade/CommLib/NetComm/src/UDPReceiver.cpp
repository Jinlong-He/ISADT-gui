#include "../include/UDPReceiver.hpp"


UDPReceiver::UDPReceiver(/* args */)
{
}

int UDPReceiver::receivePacket(u_char* dst, std::string ipStr, u_short portNum)
{
    int this_fd, ret;
    struct sockaddr_in target_addr;
    this_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(this_fd < 0)
    {
        std::cout << "create socket failed";
		return 0;
    }
    memset(&target_addr, 0, sizeof(target_addr));
    target_addr.sin_family = AF_INET;
    in_addr_t addr_dst;
    inet_aton(ipStr.c_str(), (in_addr*)&addr_dst);
    target_addr.sin_addr.s_addr = (uint32_t)addr_dst;
    target_addr.sin_port = htons(portNum);
    ret = bind(this_fd, (struct sockaddr*)&target_addr, sizeof(target_addr));
    if(ret < 0)
    {
        std::cout << "bind failure" << std::endl;
		return -1;
    }
    char recvBuf[1000];
    socklen_t len;
    struct sockaddr_in recv_target_addr;
    memset(recvBuf, 0, 1000);
    int count;
    count = recvfrom(this_fd, recvBuf, 1000, 0, (struct sockaddr*) &recv_target_addr, &len);
    
    if (count == -1) {
		std::cout << "recv data failed" << std::endl;
		return -1;
	}
    std::cout << "RECV BUF:" << recvBuf << std::endl;
    memcpy(dst, recvBuf, 1000);
    close(this_fd);
}

UDPReceiver::~UDPReceiver()
{
}
