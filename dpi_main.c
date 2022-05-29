#include "dpi.h"

#define SNAP_LEN 65535

dpi_result* dpi_init_dev(int argc, char** argv)
{
	char errbuf[PCAP_ERRBUF_SIZE] = {0};
	char* dev = NULL;
	if(argc == 2)
	{
		dev = argv[1];
	}
	else 
	{
		printf("Usage ./TIDS devicename");
		return NULL;
	}
	pcap_t* handle = pcap_open_live(dev,SNAP_LEN,0,1000,errbuf);
	if(handle == NULL)
	{
		printf("Error in pcap_open_live:%s",errbuf);
		return NULL;
	}

	if(pcap_datalink(handle)!=DLT_EN10MB)
	{
		printf("%s is not an ethernet\n",dev);
		return NULL;
	}

	dpi_result* res = malloc(sizeof(dpi_result));
	memset(res,0,sizeof(*res));

	res->pcap_handle = handle;
	init_connection_list();

	return res;
}

dpi_result* dpi_init(const char* pcapfile)
{
	//打开pcap文件返回句柄
	char errbuf[PCAP_ERRBUF_SIZE] = {0};
	pcap_t* handle = pcap_open_offline(pcapfile, errbuf);
	if (handle == NULL)
	{
		printf("Error in pcap open offline %s\n", errbuf);
		return 0;
	}
	//返回特征结构体
	dpi_result* res = malloc(sizeof(dpi_result));
	memset(res,0,sizeof(*res));

	res->pcap_handle = handle;

	init_connection_list();

	return res;
}

void dpi_pcap_callback(u_char* user,const struct pcap_pkthdr* h,const u_char* bytes)
{
	dpi_result* res = (dpi_result*)user;
	if(h->caplen!=h->len)
	{
		return;
	}

	dpi_pkt pkt;
	memset(&pkt,0,sizeof(pkt));
	
	pkt.ether_len = h->caplen;
	pkt.ether_packet = (struct ether_header*)bytes;

	dpi_pkt_ether(res,&pkt);
	
	display_result(res);

	return;
}

void dpi_loop(dpi_result* res)
{
	pcap_loop((pcap_t*)res->pcap_handle,0,dpi_pcap_callback,(u_char*)res);
}


void dpi_destory(dpi_result* res)
{
	//释放pcap句柄
	if(res==NULL)
	{
		return;
	}
	pcap_close(res->pcap_handle);
	free(res);
	//释放结构体资源
}
