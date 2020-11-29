#pragma once
#include <stdio.h>
#include <arpa/inet.h>

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
	u_short length;// length
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

typedef struct {
	// type = 0x1
	auth_header auth_hdr;
	identifier gateway_id;
	info_t gateway_info;
} auth_hello_packet;

typedef struct {
	// type = 0x2
	auth_header auth_hdr;
	identifier client_id;
	info_t client_info;
	identifier gateway_id;
} auth_start_packet;

typedef struct {
	// type = 0x3
	auth_header auth_hdr;
	identifier client_id;
	u_int32_t random_num_encrypted;
	identifier server_id;
} auth_ask_packet;

typedef struct {
	// type= 0x4
	auth_header auth_hdr;
	identifier client_id;
	u_int32_t random_num_decrypted;
} auth_answer_packet;

typedef struct {
	// type = 0x5
	auth_header auth_hdr;
	identifier client_id;
	bool auth_result;
	u_int32_t authority;
	ip_address client_ip;
	ip_address client_mask;
	ip_address gateway_ip;
	u_int32_t client_ip_private_key;
	identifier server_id;
}auth_response_packet;

typedef struct udp_header {
	u_short sport;          
	u_short dport;          
	u_short len;               
	u_short crc;            
} udp_header;

typedef struct ip_header {
	u_char  ver_ihl;		  
	u_char  tos;			   
	u_short tlen;            
	u_short identification;    
	u_short flags_fo;       
	u_char  ttl;            
	u_char  proto;          
	// 1: ICMP, 6: TCP, 17: UDP
	u_short crc;            
	ip_address  saddr;      
	ip_address  daddr;      
	u_int   op_pad;         
} ip_header;