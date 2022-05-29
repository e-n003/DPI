#include "dpi.h"

void usage(const char* arg0)
{
	printf("usage:%s <pcap_file>\n",arg0);
}


void display_result(dpi_result* res)
{
	printf("eth %u\n",res->ether_count);
	printf("ip  %u\n",res->ip_count);
	printf("tcp %u\n",res->tcp_count);
	printf("tcp_protocol:\n");
	for(int i=0;i<TCP_PROTOCOL_MAX;i++)
	{
		printf("%s:%d\n",tcp_protocol_string[i],res->tcp_protocol_count[i]);
	}

	show_connections();
}

int main(int argc,char** argv)
{
	if(argc !=2)
	{
		usage(argv[0]);
		return -1;
	}

	//初始化
	//dpi_result* res = dpi_init(argv[1]);
	dpi_result* res = dpi_init_dev(argc,argv);
	//处理
	dpi_loop(res);
	
	//display_result(res);

	//销毁
	dpi_destory(res);

	return 0;
}
