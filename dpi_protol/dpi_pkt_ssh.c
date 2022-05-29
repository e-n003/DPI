#include "dpi.h"

//检测SSH
int dpi_pkt_ssh(dpi_result* res, dpi_pkt* pkt)
{
	//识别
	if(pkt->payload_len<=4)
	{
		return 0;
	}

	if(memcmp("SSH-",pkt->payload,4)==0)
	{
		add_connection(pkt,SSH); 
		return 1;
	}
	if(cmp_connection(pkt,SSH)==0)
	{
		return 1;
	}
	return 0;
}
