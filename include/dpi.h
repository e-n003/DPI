#pragma once
#include<pcap/pcap.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<net/ethernet.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<netinet/tcp.h>
#include<sys/socket.h>

#define TCP_ANALYZE_FUNCS_NAME	\
	dpi_pkt_ssh,		\
	dpi_pkt_http

#define TCP_PROTOCOL_STRING	\
	"SSH",			\
	"HTTP"

typedef enum _dpi_tcp_protocol
{
	SSH=0,
	HTTP,
	TCP_PROTOCOL_MAX
}dpi_tcp_protocol;

#define HTTP_VERSION_1_1 "HTTP/1.1"
#define HTTP_VERSION_1_0 "HTTP.1.0"
#define CRLF "/r/n"

#define HTTP_REQUEST_METHOD_STRING	\
	"GET",				\
	"POST",				\
	"HEAD",				\
	"OPTIONS",			\
	"DELETE",			\
	"TRACE",			\
	"CONNECT"

typedef enum _HTTP_REQUEST_METHOD
{
	GET=0,
	POST,
	HEAD,
	OPTIONS,
	DELETE,
	TRACE,
	CONNECT,
	HTTP_REQUEST_METHOD_MAX
}HTTP_REQUEST_METHOD;

#define HTTP_RESPONSE_STATUS_STRING		\
	"200 Ok",			\
	"400 Bad Request",		\
	"401 Unauthorized",		\
	"403 Forbidden",		\
	"404 Not Found",		\
	"500 Internal Server Error",	\
	"503 Server Unavailable"	\

typedef enum _HTTP_RESPONSE_STATUS
{
		
	OK=0,
	Bad_Request,
	Unauthorized,
	Forbidden,
	Not_Found,
	Internal_Server_Error,
	Server_Unavailable,
	HTTP_RESPONSE_STATUS_MAX
}HTTP_RESPONSE_STATUS;

extern char* tcp_protocol_string[TCP_PROTOCOL_MAX];

extern char* http_request_method_string[HTTP_REQUEST_METHOD_MAX];

extern char* http_response_status_string[HTTP_RESPONSE_STATUS_MAX];

typedef struct _dpi_result
{
	void* pcap_handle;

	//以太网报文数量
	unsigned int ether_count;
	//tcp报文数量
	unsigned int tcp_count;
	//udp报文数量
	unsigned int udp_count;
	//ip报文数量
	unsigned int ip_count;
	//应用层报文数量
	unsigned int tcp_protocol_count[TCP_PROTOCOL_MAX];
}dpi_result;

typedef struct _dpi_pkt
{
	uint32_t ether_len;

	struct ether_header* ether_packet;

	uint32_t ip_len;

	struct iphdr* ip_packet;

	uint32_t tcp_len;

	struct tcphdr* tcp_packet;

	uint32_t udp_len;

	char* udp_packet;



	uint32_t payload_len;
	char* payload;
}dpi_pkt;

struct ipv4_port_pair
{
	uint32_t src_ip;
	uint32_t dst_ip;
	uint16_t src_port;
	uint16_t dst_port;
};

typedef struct dpi_connection
{
	struct ipv4_port_pair ipv4;
}dpi_connection;

void init_connection_list();
void add_connection(dpi_pkt* pkt,dpi_tcp_protocol protocol);
void show_connections();
int cmp_connection(dpi_pkt* pkt,dpi_tcp_protocol protocol);

dpi_result* dpi_init_dev(int argc,char** argv);
dpi_result* dpi_init(const char* pcapfile);

//处理
void dpi_loop(dpi_result* res);

//销毁
void dpi_destory(dpi_result* res);

void dpi_pkt_ether(dpi_result* res,dpi_pkt* pkt);

void dpi_pkt_ip(dpi_result* res,dpi_pkt* pkt);

void dpi_pkt_tcp(dpi_result* res,dpi_pkt* pkt);

int dpi_pkt_ssh(dpi_result* res,dpi_pkt* pkt);
int dpi_pkt_http(dpi_result* res,dpi_pkt* pkt);

typedef int (*dpi_protocl_analyze_func_t)(dpi_result* res,dpi_pkt* pkt);

//extern dpi_protocl_analyze_func_t dpi_tcp_analyze_funcs[TCP_PROTOCOL_MAX];
