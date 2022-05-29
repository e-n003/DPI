#include "dpi_list.h"


dpi_list_t* dpi_list_init()
{
	dpi_list_t *list = malloc(sizeof(dpi_list_t));
	if (list != NULL)
	{
		memset(list, 0, sizeof(dpi_list_t));
	}


	list->head.next = &list->head;
	list->head.prev = &list->head;
	list->size = 0;

	return list;
}


void dpi_list_append(dpi_list_t *list, void *data)
{
       	dpi_list_node_t *new_node = malloc(sizeof(dpi_list_node_t));
	if (new_node == NULL)
	{
		printf("加入失败");
		exit(0);
	}
	memset(new_node, 0 , sizeof(dpi_list_node_t));
	new_node->data = data;

	dpi_list_node_t *last_node = list->head.prev;

	last_node->next = new_node;

	new_node->prev = last_node;

	list->head.prev = new_node;

	new_node->next = &list->head;

	list->size ++;

}


void dpi_list_destory(dpi_list_t* list)
{
	dpi_list_node_t *begin = list->head.next;
    	int num = 0;
	
	while (begin != &list->head)
	{
		dpi_list_node_t *temp = begin;
		begin = begin->next;
		printf("free:%d\n",*(int *)temp->data);
		free(temp);
	}


	free(list);
}

