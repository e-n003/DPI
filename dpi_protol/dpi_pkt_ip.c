#include"dpi.h"

void dpi_pkt_ip(dpi_result* res,dpi_pkt* pkt)
{
	res->ip_count++;

	//ip版本号
	if(pkt->ip_packet->version != 4)
	{
		printf("IP Version not eqaul 4\n");
		return ;
	}
	//ip头长
	int ihl = pkt->ip_packet->ihl << 2;

	//ip总长度
	int ip_totlen = ntohs(pkt->ip_packet->tot_len);

	//分片
	if((pkt->ip_packet->frag_off) & htons(0x1fff)!=0)
	{
		printf("IP Frag not eq 0");
		return ;
	}

	switch(pkt->ip_packet->protocol)
	{
		case 6:
			//TCP
			pkt->tcp_len = ip_totlen - ihl;
			pkt->tcp_packet = (struct tcphdr*)((char*)pkt->ip_packet + ihl);

			dpi_pkt_tcp(res,pkt);
			break;
		case 17:
			//UDP
			break;
		case 1:
			//ICMP
			break;
		deault:
			//UNKNOW
			break;
	}
}
