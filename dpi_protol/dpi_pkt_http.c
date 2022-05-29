#include "dpi.h"

char* http_request_method_string[HTTP_REQUEST_METHOD_MAX]={HTTP_REQUEST_METHOD_STRING};

char* http_response_status_string[HTTP_RESPONSE_STATUS_MAX]={HTTP_RESPONSE_STATUS_STRING};

int dpi_pkt_http(dpi_result* res,dpi_pkt* pkt)
{
	//printf("4");
	//长度要求
	if(pkt->payload_len<(strlen(http_request_method_string[GET]+strlen(HTTP_VERSION_1_0)+2+strlen(CRLF))))
	{
		return 0;
	}

	for(int i=0;i<HTTP_REQUEST_METHOD_MAX;i++)
	{
		//请求报文匹配
		if(memcmp(http_request_method_string[i],pkt->payload,strlen(http_request_method_string[i]))==0)
		{
			//匹配版本号
			char* p=NULL;
			for(p=pkt->payload+(strlen(http_request_method_string[i])+1);*p!=' ';p++);
			p++;
			if(memcmp(p,HTTP_VERSION_1_0,strlen(HTTP_VERSION_1_0))==0||memcmp(p,HTTP_VERSION_1_1,strlen(HTTP_VERSION_1_1))==0)
			{
				//printf("3\n");
				add_connection(pkt,HTTP);
				return 1;
			}
		}
	}
	
	//响应报文匹配
	if((memcmp(HTTP_VERSION_1_1,pkt->payload,strlen(HTTP_VERSION_1_1))==0)||(memcmp(HTTP_VERSION_1_0,pkt->payload,strlen(HTTP_VERSION_1_0))==0))
	{
		//printf("1\n");
		char* p = pkt->payload+(strlen(HTTP_VERSION_1_1)+1);
		for(int i=0;i<HTTP_RESPONSE_STATUS_MAX;i++)
		{
			if(memcmp(http_response_status_string[i],p,strlen(http_response_status_string[i]))==0)
			{
				add_connection(pkt,HTTP);
				return 1;
			}
		}
		return 1;
	}


	if(cmp_connection(pkt,HTTP)==0)
	{
		//printf("2\n");
		return 1;
	}
	


	return 0;
}
