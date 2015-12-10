#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node *next;
} Node;

void push(Node** stack, int data) //Adding a new element to the stack
{
	Node *tmp = malloc(sizeof(struct Node)); //Select by his memory.
	tmp->data = data; //Set the value to
	tmp->next = *stack; //Make it so that he was referring to the previous item
	*stack = tmp; //Now the top of the stack points to the new node.
}

void pop(Node** stack) // Remove from the stack
{
	Node *p = (*stack)->next; //the first element (the pointed top), throws a pointer to the next element 
	free(*stack);
	*stack = p; //and returns the first.
}

int main()
{
	Node *stack = NULL;

	// for(int i = 1; i <= 7; ++i) push(&stackp, i);

	push(&stack, 4);
	push(&stack, 3);
	push(&stack, 7);
	push(&stack, 0);
	push(&stack, 1);

	while (stack)
	{
		printf("%d\n", stack->data);
		pop(&stack);
	}

	return 0;
}