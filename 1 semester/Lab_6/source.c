#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

int HASH_SIZE = 5;
int MAX_SIZE_OF_BASCET = 2;

struct my_list {
	char *key;
	int data;
	struct my_list* next;
};

int next_prime_after(int a)
{
	while (1)
	{
		a++;
		for (int i = 2; i <= sqrt(a); i++)
		{
			if (a%i == 0)
				break;
			return a;
		}
	}
}

int hash_function(char *key)
{
	int sum = 0;
	while (*key != '\0') sum += (int)*key++;
	return (sum % HASH_SIZE);
}

void clean_list(struct my_list **head_pp)
{
	struct my_list *current_element;
	struct my_list *temp;

	assert(head_pp != NULL);

	current_element = *head_pp;
	while (current_element != NULL)
	{
		printf("Free element: \"%s\" with data = %d\n", current_element->key, current_element->data);
		temp = current_element->next;
		free(current_element->key);
		free(current_element);
		current_element = temp;
	}
}

void print_list(struct my_list *head_ptr)
{
	struct my_list *i;

	for (i = head_ptr; i != NULL; i = i->next)
		printf("\tkey=%s, data=%d\n", i->key, i->data);
}

/*return number of elements in hash[i]*/
int add_element_to_list_end(struct my_list **head_pp, char *key, int data)
{
	struct my_list *current_element;

	assert(head_pp != NULL);
	 
	int number_of_element = 1;
	 
	for (current_element = *head_pp;
		current_element != NULL;
		current_element = current_element->next)
	{
		number_of_element++;
		if (current_element->next == NULL)
			break;
	}

	struct my_list *new_element_ptr;
	new_element_ptr = malloc(sizeof(struct my_list));
	assert(new_element_ptr != NULL);

	new_element_ptr->key = malloc(strlen(key) + 1);
	assert(new_element_ptr->key != NULL);
	memcpy(new_element_ptr->key, key, strlen(key) + 1);
	new_element_ptr->data = data;
	new_element_ptr->next = NULL;

	if (current_element == NULL)
		*head_pp = new_element_ptr;
	else
		current_element->next = new_element_ptr;

	printf("Key \"%s\" with data = %d added. (hash=%d)\n", key, data, hash_function(key));
	return number_of_element;
}

void del_element_from_list_for_key(struct my_list **head_pp, char *key)
{
	struct my_list *current_element;
	struct my_list *temp;
	struct my_list *previous_element = NULL;

	assert(head_pp != NULL);

	for (current_element = *head_pp;
		current_element != NULL;
		previous_element = current_element, current_element = current_element->next)
	{
		if (strcmp(current_element->key, key) == 0) 
			break;
	}
	if (current_element == NULL)
	{
		printf("Key \"%s\" is not found.\n", key);
		return;
	}

	if (previous_element == NULL)
	{
		*head_pp = (current_element)->next;
		free(current_element->key);
		free(current_element);
	}
	else if (current_element->next == NULL)
	{
		temp = current_element;
		previous_element->next = NULL;
		free(temp->key);
		free(temp);
	}
	else
	{
		previous_element->next = current_element->next;
		free(current_element->key);
		free(current_element);
	}
	printf("Key \"%s\" with data = %d deleted.\n", key, current_element->data);
	return;
}

/*return 1 if key exist*/
int print_element_data_for_key(struct my_list **head_pp, char *key)
{
	struct my_list *current_element;

	for (current_element = *head_pp;
		current_element != NULL;
		current_element = current_element->next)
	{
		if (strcmp(current_element->key, key) == 0) break;
	}
	if (current_element == NULL)
	{
		return 0;
	}
	printf("\"%s\"=%d\n", key, current_element->data);
	return 1;
}

/*return rebalansing hash*/
struct my_list** rebalancing(struct my_list **old_hash)
{
	assert(old_hash != NULL);

	int old_hash_size = HASH_SIZE;
	HASH_SIZE = next_prime_after(HASH_SIZE);
	printf("Hash increased by %d (hash size = %d now)\n\n", HASH_SIZE - old_hash_size, HASH_SIZE);
	printf("Rebalansing:\n\n");

	struct my_list **new_hash;
	new_hash = malloc(HASH_SIZE * sizeof(struct my_list));

	for (int i = 0; i < HASH_SIZE; i++)
		new_hash[i] = NULL;

	struct my_list *current_element;
	for (int i = 0; i < old_hash_size; i++)
	{
		current_element = old_hash[i];
		while (current_element != NULL)
		{
			add_element_to_list_end(&new_hash[hash_function(current_element->key)], current_element->key, current_element->data);
			current_element = current_element->next;
		}
		clean_list(&old_hash[i]);
	}
	return new_hash;
}

int main()
{
	struct my_list **hash;
	hash = malloc(HASH_SIZE * sizeof(struct my_list));

	for (int i = 0; i < HASH_SIZE; i++)
		hash[i] = NULL;

	add_element_to_list_end(&hash[hash_function("0")], "0", 100);
	add_element_to_list_end(&hash[hash_function("1")], "1", 111);
	add_element_to_list_end(&hash[hash_function("2")], "2", 222);
	add_element_to_list_end(&hash[hash_function("3")], "3", 333);
	add_element_to_list_end(&hash[hash_function("4")], "4", 444);
	add_element_to_list_end(&hash[hash_function("5")], "5", 555);
	add_element_to_list_end(&hash[hash_function("6")], "6", 666);

	char new_key[50];
	int new_data;
	int input = 999;

	while (input != 0)
	{
		printf("\nEnter 1 to add key with data\n");
		printf("      (key in string format, data in integer format)\n");
		printf("      2 to delete key with data\n");
		printf("      3 to search data for key\n");
		printf("      4 to print\n");
		printf("      0 to exit\n");
		scanf("%d", &input);
		switch (input)
		{
		case 0:
			for (int i = 0; i < HASH_SIZE; i++)
				clean_list(&hash[i]);
			break;
		case 1:
			printf("New key = ");
			scanf("%s", new_key);
			if (print_element_data_for_key(&hash[hash_function(new_key)], new_key))
			{
				printf("Key \"%s\" already exist!", new_key);
				break;
			}
			printf("New data = ");
			scanf("%d", &new_data);
			if (add_element_to_list_end(&hash[hash_function(new_key)], new_key, new_data) > MAX_SIZE_OF_BASCET)
			{
				printf("Hash[%d] is overcrowded\n\n", hash_function(new_key));
				hash = rebalancing(hash);
				printf("\nRebalansing complete.\n");
			}
			break;
		case 2:
			printf("Delete key = ");
			scanf("%s", new_key);
			del_element_from_list_for_key(&hash[hash_function(new_key)], new_key);
			break;
		case 3:
			printf("Search key = ");
			scanf("%s", new_key);
			if(print_element_data_for_key(&hash[hash_function(new_key)], new_key) == 0)
				printf("Key \"%s\" does not exist\n", new_key);
			break;
		case 4:
			for (int i = 0; i < HASH_SIZE; i++)
			{
				printf("\n[%d]==>", i);
				print_list(hash[i]);
				printf("\n");
			}
			break;
		default:
			printf("To add, delete, search or print input only 1-4!\n");
			break;
		}
	}
	printf("Press any key to exit");
	_getch();
	return 0;
}