#include<dpi.h>
#include"dpi_list.h"

dpi_list_t* globalConnections[TCP_PROTOCOL_MAX];

void init_connection_list()
{
	for(int i=0;i<TCP_PROTOCOL_MAX;i++)
	{
		globalConnections[i]=dpi_list_init();
	}
}

void destory_connection_list(dpi_list_t* globalConnections[])
{
	for(int i=0;i<TCP_PROTOCOL_MAX;i++)
	{
		dpi_list_destory(globalConnections[i]);
	}
}

void add_connection(dpi_pkt* pkt,dpi_tcp_protocol protocol)
{
	dpi_connection* connect = malloc(sizeof(dpi_connection));
	if(!connect)
	{
		printf("创建链接信息失败");
		exit(0);
	}
	memset(connect,0,sizeof(dpi_connection));
	
	connect->ipv4.src_ip = pkt->ip_packet->saddr;
	connect->ipv4.dst_ip = pkt->ip_packet->daddr;

	connect->ipv4.src_port = pkt->tcp_packet->source;
	connect->ipv4.dst_port = pkt->tcp_packet->dest;

	dpi_list_append(globalConnections[protocol],connect);

}

int cmp_connection(dpi_pkt* pkt,dpi_tcp_protocol protocol)
{
	int ret=1;
	
	uint32_t src_ip;
	uint32_t dst_ip;
	uint16_t src_port;
	uint16_t dst_port;


	dpi_list_node_t* node = globalConnections[protocol]->head.next;
	for(;node!=&globalConnections[protocol]->head;node=node->next)
	{
		dpi_connection* connect = node->data;
		src_ip = connect->ipv4.src_ip;
		dst_ip = connect->ipv4.dst_ip;
		src_port = connect->ipv4.src_port;
		dst_port = connect->ipv4.dst_port;

		if(src_ip == pkt->ip_packet->saddr)
		{
			if(dst_ip == pkt->ip_packet->daddr)
			{
				if((src_port == pkt->tcp_packet->source) && (dst_port == pkt->tcp_packet->dest))
				{
					ret = 0;
					goto END;
				}
			}
		}
	}
	
END:
	return ret;
}

void show_connections()
{
	for(int i=0;i<TCP_PROTOCOL_MAX;i++)
	{
		printf("==========TCP Connections==========\n");
		printf("tcp protocol:%s\n",tcp_protocol_string[i]);
		
		dpi_list_node_t* node = globalConnections[i]->head.next;
		while(node!=&globalConnections[i]->head)
		{
			dpi_connection* connect=node->data;
			struct in_addr in;
			in.s_addr=connect->ipv4.src_ip;
			printf("src:%s:%d\t",inet_ntoa(in),ntohs(connect->ipv4.src_port));
			in.s_addr = connect->ipv4.dst_ip;
			printf("dst:%s:%d\n",inet_ntoa(in),ntohs(connect->ipv4.dst_port));
			node=node->next;
		}
	}
}
