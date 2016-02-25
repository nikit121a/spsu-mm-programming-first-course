#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>


struct stack {
	char *key;
	int data;
	struct stack* next;
};

void print_stack(struct stack *head_ptr)
{
	struct stack *i;

	for (i = head_ptr; i != NULL; i = i->next)
		printf("key=%s, data=%d\n", i->key, i->data);
}

void push(struct stack **list_head_pp, char *key, int data)
{
	struct stack *current_element;

	struct stack *new_element_ptr;
	new_element_ptr = malloc(sizeof(struct stack));
	assert(new_element_ptr != NULL);

	new_element_ptr->key = key;
	new_element_ptr->data = data;

	new_element_ptr->next = *list_head_pp;
	*list_head_pp = new_element_ptr;
}

void pop(struct stack **list_head_pp)
{
	if (*list_head_pp == NULL)
	{
		printf("Nothing to pop!");
		return;
	}

	assert(list_head_pp != NULL);

	struct stack *current_element;

	printf("pop: key=%s, data=%d\n\n", (*list_head_pp)->key, (*list_head_pp)->data);

	current_element = *list_head_pp;
	*list_head_pp = (*list_head_pp)->next;
	free(current_element);
}

int main()
{
	struct stack *head_ptr = NULL;
	int input = 42;
	char new_key[20];
	int new_data;

	push(&head_ptr, "q", 111);
	push(&head_ptr, "w", 222);
	push(&head_ptr, "e", 333);
	print_stack(head_ptr);

	while (input != "9")
	{
		scanf("%d", &input);
		if (input == 1)
		{
			scanf("%s", new_key);
			scanf("%d", &new_data);
			push(&head_ptr, new_key, new_data);
		}
		if (input == 0)
		{
			pop(&head_ptr);
		}
		print_stack(head_ptr);
	}

	_getch();
	return 0;
}
