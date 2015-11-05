#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node
{
	int x;
	struct Node *next;
};

typedef struct Node Node;

void add(Node *root, int value)
{
	Node *conductor = root;
	while(conductor -> next != 0)
	{
		conductor = conductor -> next;
	}
	conductor -> next = (Node*)malloc(sizeof(Node));
	conductor = conductor -> next;
	conductor -> x = value;
	conductor -> next = 0;

	return;
}

void print_list(Node *root)
{
	while(root != 0)
	{
		printf("%d - ", root -> x);
		root = root -> next;
	}
}

int length(Node *head)
{
	int count = 0;
	while (head != 0)
	{
		count++;
		head = head -> next;
	}

	return count;
}

int deleteNode(Node *head, int value)
{
	int found = 0;
	while (head -> next != 0)
	{
		if (head -> next -> x == value)
		{
			head = head -> next -> next;
			found = 1;
			break;
		}
		head = head -> next;
	}
	return found;
}

int main()
{
	Node *root, *current;
	root = (Node*)malloc(sizeof(Node));
	root -> x = 5;
	root -> next = 0;
	add(root, 7);
	add(root, 1);
	print_list(root);
	deleteNode(root, 7);
	print_list(root);
	getchar();
	return 0;
}