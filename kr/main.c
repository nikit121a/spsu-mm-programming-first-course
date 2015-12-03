#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAIN 3

typedef struct {
	int* next;
	int value;
}data;

int head = 0;
data init;

void add(int value)
{
	data* cur = &init;
	for (int i = 0; i < head; i++)
	{
		cur = cur->next;
	}
	cur->value = value;
	head = (head + 1) % MAX_CHAIN;
}

int get(int v)
{
	data* cur = &init;
	for (int i = 0; i < v; i++)
	{
		cur = cur->next;
	}
	return cur->value;
}

void main()
{
	data* cur = &init;

	for (int i = 0; i < MAX_CHAIN; i++)
	{
		cur->next = (data*)malloc(sizeof(data));
		cur = cur->next;
	}

	cur->next = &init;

	add(1);
	add(2);
	add(3);
	printf("%d", get(5));
	_getch();
	return 0;
}