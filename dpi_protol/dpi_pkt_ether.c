#include<dpi.h>

void dpi_pkt_ether(dpi_result* res,dpi_pkt* pkt)
{
	res->ether_count++;
	/*
	printf("eth dmac:");
	for(int i=0;i<6;i++)
	{
		printf("%x",pkt.ether_packet->ether_dhost[i]);
	}
	printf("\n");
	printf("eth smac");
	for(int i=0;i<6;i++)
	{
		printf("%x",pkt.ether_packet->ether_dhost[i]);
	}
	printf("\n");
	printf("ether type = %x\n",pkt.ether_packet->ether_type);
	*/

	if(pkt->ether_packet->ether_type == htons(0x0800))
	{
		
		//获得长度和首地址
		pkt->ip_len = pkt->ether_len - sizeof(*pkt->ether_packet);

		pkt->ip_packet = (struct iphdr*)((char*)pkt->ether_packet + sizeof(*pkt->ether_packet));

		//解析ip报文
		dpi_pkt_ip(res,pkt);


	}
	else if(pkt->ether_packet->ether_type == htons(0x0806))
	{
		//res->arp_count++;
	}
	else if(pkt->ether_packet->ether_type == htons(0x8035))
	{

	}

}
