#include<dpi_list.h>

int main(int argc,char** argv)
{
	dpi_list_t* list=dpi_list_init();
	if(!list)
	{
		printf("初始化失败");
		exit(0);
	}
	int* num10 = (int*)malloc(sizeof(int));
	int* num20 = (int*)malloc(sizeof(int));
	int* num30 = (int*)malloc(sizeof(int));
	int* num40 = (int*)malloc(sizeof(int));
	int* num50 = (int*)malloc(sizeof(int));
	int* num60 = (int*)malloc(sizeof(int));

	*num10=10;
	*num20=20;
	*num30=30;
	*num40=40;
	*num50=50;
	*num60=60;

	dpi_list_append(list,num10);
	dpi_list_append(list,num20);
	dpi_list_append(list,num30);
	dpi_list_append(list,num40);
	dpi_list_append(list,num50);
	dpi_list_append(list,num60);
	
	dpi_list_node_t* begin = list->head.next;
	while(begin!=&list->head)
	{
		int *p=begin->data;
		printf("%d\n",*p);

		begin=begin->next;
	}
	
	dpi_list_destory(list);
	return 0;
}
