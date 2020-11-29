#pragma once
#include <pcap.h>
#include <stdio.h>

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

// �������汨��
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
	u_short sport;          // Դ�˿�(Source port)    
	u_short dport;          // Ŀ�Ķ˿�(Destination port)    
	u_short len;            // UDP���ݰ�����(Datagram length)    
	u_short crc;            // У���(Checksum)
} udp_header;

typedef struct ip_header {
	u_char  ver_ihl;		// �汾 (4 bits) + �ײ����� (4 bits)    
	u_char  tos;			// ��������(Type of service)     
	u_short tlen;           // �ܳ�(Total length)     
	u_short identification; // ��ʶ(Identification)   
	u_short flags_fo;       // ��־λ(Flags) (3 bits) + ��ƫ����(Fragment offset) (13 bits)    
	u_char  ttl;            // ���ʱ��(Time to live)    
	u_char  proto;          // Э��(Protocol) 
	// 1: ICMP, 6: TCP, 17: UDP
	u_short crc;            // �ײ�У���(Header checksum)    
	ip_address  saddr;      // Դ��ַ(Source address)    
	ip_address  daddr;      // Ŀ�ĵ�ַ(Destination address)    
	u_int   op_pad;         // ѡ�������(Option + Padding)
} ip_header;