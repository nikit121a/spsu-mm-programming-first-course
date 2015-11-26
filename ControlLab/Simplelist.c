#include <stdlib.h>
#include <conio.h>
#include <stdio.h>

struct Node
{
	int Value;
	struct Node *next;
	int kol;
};

typedef struct Node *PNode;

PNode CreateNode(int NewValue)
{
	PNode NewNode = malloc(sizeof(struct Node));
	NewNode->next = NULL;
	NewNode->Value = NewValue;
	NewNode->kol = 1;
	return NewNode;
}

void AddAfter(PNode p, PNode NewNode)
{
	NewNode->next = p->next;
	p->next = NewNode;
}

void AddLast(PNode head, PNode NewNode)
{
	PNode temp = head;
	while (temp->next)
		temp = temp->next;
	AddAfter(temp, NewNode);
}

void Add(PNode* head, int value, int count)
{
	PNode NewNode;
	PNode temp = *head;
	if (count == 1)
	{
		*head = CreateNode(value);

		return;
	}
	if (count % 32 == 0)
	{
		NewNode = CreateNode(value);
		AddLast(*head, NewNode);
		return;
	}
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->Value = temp->Value * 2 + value;
		temp->kol += 1;
	}
}

PNode GetByNumber(PNode head, int *count)
{
	PNode temp = head;
	while (*count > 32)
	{
		temp = temp->next;
		*count -= 32;
	}
	return temp;

}

int main()
{
	PNode head = NULL;
	int count = 1;
	int value;
	printf_s("Enter your numbers\n");
	printf_s("In the end write -1\n");
	scanf_s("%d", &value);
	if (value != -1)
	{
		Add(&head, value, count);
		count++;
	}
	else
	{
		printf_s("The End.");
		return 0;
	}
	scanf_s("%d", &value);
	while (value != -1)
	{
		Add(&head, value, count);
		count++;
		scanf_s("%d", &value);
	}

	printf_s("Enter your number: \n");
	int numberOfarray;
	scanf_s("%d", &numberOfarray);
	PNode list = GetByNumber(head, &numberOfarray);
	for (int i = list->kol - numberOfarray; i > 0; i--)
		list->Value /= 2;
	printf_s("%d", list->Value % 2);
	_getch();
	return 0;
}