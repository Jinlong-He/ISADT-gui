#pragma once
#include <stdio.h>
#include <sys/socket.h>

#define ETH_P_888F 0x888f

typedef struct ether_header {
	u_char h_dest[6];// destination mac address
	u_char h_source[6];// source mac address
	u_short type;// ethernet type
} ether_header;

typedef struct auth_header {
	u_char version;// version number
	u_char type;// type 
	u_int serial_num;// serial number
	u_int timestamp;// time stamp
	u_short length;// lengtt
} auth_header;

typedef u_char identifier;
typedef struct ip_address {
	u_char byte1;
	u_char byte2;
	u_char byte3;
	u_char byte4;
} ip_address;

// information of gateway, client and server
typedef struct {
	u_char mac[6];
	ip_address ip;
} info_t;

// 网关宣告报文
typedef struct {
	auth_header auth_hdr;
	identifier gateway_id;
	info_t gateway_info;
} gateway_hello_packet;


typedef struct {
	auth_header auth_hdr;
	identifier client_id;
	info_t client_info;
	identifier gateway_id;
} auth_start_packet;



typedef struct udp_header {
	u_short sport;          // 源端口(Source port)    
	u_short dport;          // 目的端口(Destination port)    
	u_short len;            // UDP数据包长度(Datagram length)    
	u_short crc;            // 校验和(Checksum)
} udp_header;

typedef struct ip_header {
	u_char  ver_ihl;		// 版本 (4 bits) + 首部长度 (4 bits)    
	u_char  tos;			// 服务类型(Type of service)     
	u_short tlen;           // 总长(Total length)     
	u_short identification; // 标识(Identification)   
	u_short flags_fo;       // 标志位(Flags) (3 bits) + 段偏移量(Fragment offset) (13 bits)    
	u_char  ttl;            // 存活时间(Time to live)    
	u_char  proto;          // 协议(Protocol) 
	// 1: ICMP, 6: TCP, 17: UDP
	u_short crc;            // 首部校验和(Header checksum)    
	ip_address  saddr;      // 源地址(Source address)    
	ip_address  daddr;      // 目的地址(Destination address)    
	u_int   op_pad;         // 选项与填充(Option + Padding)
} ip_header;