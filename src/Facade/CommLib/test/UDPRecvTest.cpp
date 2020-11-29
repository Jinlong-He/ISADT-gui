#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <memory.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


void udp_msg_sender(int fd, struct sockaddr* dst){
    socklen_t len;
    struct sockaddr_in src;
    while(true){
        char buf[1024] = "TEST UDP MSG";
        len = sizeof(*dst);
        std::cout << "Client: send" << buf << std::endl;
        sendto(fd, buf, 1024, 0, dst, len);
        memset(buf, 0, 1024);
        recvfrom(fd, buf, 1024, 0, (struct sockaddr*)&src, &len);
        std::cout << "Server: " << buf << std::endl;
        sleep(1);
    }
}

int main(){
    int client_fd;
    struct sockaddr_in ser_addr;
    client_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(client_fd < 0){
        std::cout << "create socket failed" << std::endl;
        return 0;
    }
    memset(&ser_addr, 0, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    in_addr_t client_addr;
    inet_aton("192.168.0.104", (in_addr*)&client_addr);
    ser_addr.sin_addr.s_addr = client_addr;
    ser_addr.sin_port = htons(200);
    udp_msg_sender(client_fd, (sockaddr*)&ser_addr);
    close(client_fd);
    return 0;
}

