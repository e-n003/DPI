#pragma once
#include <dpi.h>
typedef struct _dpi_list_node
{
	void* data;
	struct _dpi_list_node* prev;
	struct _dpi_list_node* next;
}dpi_list_node_t;

typedef struct _dpi_list
{
	uint32_t size;
	dpi_list_node_t head;
}dpi_list_t;

dpi_list_t* dpi_list_init();

void dpi_list_append(dpi_list_t* list,void* data);

void dpi_list_destory(dpi_list_t* list);


