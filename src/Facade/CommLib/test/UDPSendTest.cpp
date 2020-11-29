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




void handle_udp_msg(int fd){
    char buf[1024];
    socklen_t len;
    int count;
    struct sockaddr_in client_addr;
    // use for remember the otherside
    while(true){
        memset(buf, 0, 1024);
        len = sizeof(client_addr);
        count = recvfrom(fd, buf, 1024, 0, (struct sockaddr*)&client_addr, &len);
        // recv data from socket to buf
        if(count == -1){
            std::cout << "recv data failed" << std::endl;
            return;
        }
        std::cout << "client data: " << buf << std::endl;
        memset(buf, 0, 1024);
        sprintf(buf, "Server recv %d data", count);
        sendto(fd, buf, 1024, 0, (struct sockaddr*)&client_addr, len);
    }
}
int main(){
    int server_fd, ret;
    struct sockaddr_in ser_addr;
    server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    // construct socket
    if(server_fd < 0){
        std::cout << "create socket failed";
        return 0;
    }
    memset(&ser_addr, 0, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    in_addr_t addrServ;
    inet_aton("192.168.0.104", (in_addr*)&addrServ);
    ser_addr.sin_addr.s_addr = (uint32_t)addrServ;
    ser_addr.sin_port = htons(200);

    ret = bind(server_fd, (struct sockaddr*)&ser_addr, sizeof(ser_addr));
    if(ret < 0){
        std::cout << "bind failure" << std::endl;
        return -1;
    }
    handle_udp_msg(server_fd);
    close(server_fd);
    return 0;
}

