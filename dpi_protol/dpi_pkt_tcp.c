#include"dpi.h"

char* tcp_protocol_string[TCP_PROTOCOL_MAX]={TCP_PROTOCOL_STRING};

void dpi_pkt_tcp(dpi_result* res,dpi_pkt* pkt)
{
	res->tcp_count++;
	
	//tcp头长度
	int tcphl = pkt->tcp_packet->doff<<2;

	//应用层长度
	pkt->payload_len = pkt->tcp_len - tcphl;

	//应用层首地址
	pkt->payload = (char*)pkt->tcp_packet + tcphl;
	
	/*for(int i=0;i<TCP_PROTOCOL_MAX;i++)
	{
		printf("%d",i);
	}
	printf("\n");
	*/

	dpi_protocl_analyze_func_t dpi_tcp_analyze_funcs[TCP_PROTOCOL_MAX]={TCP_ANALYZE_FUNCS_NAME};

	for(int i=0;i<TCP_PROTOCOL_MAX;i++)
	{
		if(dpi_tcp_analyze_funcs[i](res,pkt) == 1)
		{
			res->tcp_protocol_count[i]++;
		}
	}
	
	

}
