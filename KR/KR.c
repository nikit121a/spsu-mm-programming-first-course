#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int value;
	void *next;
}init_struct;

init_struct h;
int head = 0;

void push(int value)
{
	init_struct* cur = &h;
	for (int i = 0; i < head; i++)
	{
		cur = cur->next;
	}
	cur->value = value;
	cur->next = (init_struct*)malloc(sizeof(init_struct));
	head++;
}

int pop()
{
	init_struct* cur = &h;
	for (int i = 0; i < head - 1; i++)
	{
		cur = cur->next;
	}
	head--;
	return cur->value;
}

void main()
{
	push(1);
	push(2);
	push(3);

	int a = pop();
	int b = pop();
	int c = pop();

	printf("%d, %d, %d", a, b, c);
	_getch();
	return;
}