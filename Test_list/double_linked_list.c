#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct List_Node
{
	int value;
	struct List_Node *prev;
	struct List_Node *next;
};

typedef struct List_Node list_node;

struct List
{
	list_node *first, *last;
};

typedef struct List list;

void init(list *new_list, int value)
{
	list_node *node, *tale;
	node = (list_node*)malloc(sizeof(list_node));
	node -> next = NULL;
	node -> prev = NULL;
	node -> value = value;
	tale = (list_node*)malloc(sizeof(list_node));
	tale -> prev = NULL;
	tale -> next = NULL;
	new_list -> first = node;
	new_list -> last = tale;
	return;
}

void add_tale(list *list, int value)
{
	list_node *node;
	if (list -> last -> prev == NULL)
	{
		list -> last -> prev = list -> first;
		list -> last -> value = value; 
		list -> first -> next = list -> last;
	}
	else
	{
		node = (list_node*)malloc(sizeof(list_node));
		node -> value = list -> last -> value;
		node -> prev = list -> last -> prev;
		list -> last -> value = value;
		list -> last -> prev = node;
		node -> next = list -> last;
	}
	return;
}

void add_head(list *list, int value)
{
	list_node *node;
	if (list -> last -> prev == NULL)
	{
		list -> last -> value = list -> first -> value; 
		list -> first -> value = value;
		list -> first -> next = list -> last;
		list -> last -> prev = list -> first;
	}
	else
	{
		node = (list_node*)malloc(sizeof(list_node));
		node -> value = list -> first -> value;
		node -> next = list -> first -> next;
		list -> first -> value = value;
		list -> first -> next = node;
		node -> prev = list -> first;
	}
	return;
}

int main()
{
	list new_list;
	init(&new_list, 5);
	return 0;
}