#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"

struct ListNode
{
	int *array[8];
	int count;
	struct ListNode	*next;
};

struct List
{
	struct ListNode	*first;
	struct ListNode	*last;
};

struct ListNode* createLN(struct ListNode* parent)
{
	struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
	node->array[8];
	node->count = 0; 
	if (parent != 0)
	{
		parent->next = node;
	}
	return node;
}

struct List createList()
{
	struct List list;
	list.first = createLN(NULL);
}

void add(struct List list, int x)
{
	if (list.last->count < 8)
	{
		list.last->array[list.last->count] = x;
		list.last->count++;
	}
	else
	{
		struct ListNode* newNode = createLN(list.last);
		newNode->array[0] = x;
		newNode->count = 1;
		list.last = newNode;
	}
	createList();
	list.last = list.first;
	return list;
}

int find(struct List list, int x)
{
	int n = x / 8; 
	struct ListNode* current = list.first;
	for (int i = 0; i < n; i++)
	{
		current = current->next;
	}
	return current->array[x % 8];
}


int main()
{
	int pos, val;
	printf("Enter the element, which you want to add: ");
	scanf("%d", &val);
	printf("Enter the position of the element, which you want to get: ");
	scanf("%d", &pos);
	struct List list = createList();
	for (int i = 0; i < 50; i++)
	{
		add(list, i);
	}
	add(list, val);
	int x = find(list, pos);
	printf("The answer is ");
	printf("%d\n", x);
	system("pause");
	return 0;
}