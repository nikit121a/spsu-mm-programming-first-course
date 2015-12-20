#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 255 //size of hash table
#define MAX_LENGTH 5 //max length of the chains in table
#define STRING_LENGTH 32 //max length of the keys and values
#define COUNT 5 //max count of rebalancing

struct List
{
	char key[STRING_LENGTH];
	char value[STRING_LENGTH];
	struct List *next;
};

typedef struct List list;

struct HashTable
{
	list **table;
	int *length;
	int size;
	int width;
	int count;
};

typedef struct HashTable HashTable;

void init(HashTable *h, int size)
{
	int i;
	h->size = size;
	h->width = 0;
	h->count = 0;
	h->table = (list**)malloc(sizeof(list*) * h->size);
	h->length = (int*)malloc(sizeof(int) * h->size);
	memset(h->length, 0, sizeof(int) * h->size);
	for (i = 0; i < h->size; i++)
	{
		h->table[i] = (list*)malloc(sizeof(list));
		h->table[i] = NULL;
	}
}

unsigned int hash(char *str, int count)
{
	//using Ly hash function
	unsigned int value = 0;
	for (; *str; str++)
	{
		value += (unsigned char)(*str) + value * 1664525 + 1013904223;
	}

	return ((value >> count) % SIZE);
}

void add(HashTable *h, char *str, char *value);

void new_hash(HashTable *h)
{
	HashTable new_h;
	int i;
	list *conductor;
	init(&new_h, SIZE);
	new_h.count = h->count;
	for (i = 0; i < h->size; i++)
	{
		conductor = h->table[i];
		while (conductor != NULL)
		{
			add(&new_h, conductor->key, conductor->value);
			conductor = conductor->next;
		}
	}
	new_h.count++;
	if(new_h.count >= COUNT)
	{
		printf("Sorry, can not rebalanse the table.\n");
		new_h.count = 0;
		for (i = 0; i < h->size; i++)
		{
			conductor = h->table[i];
			while (conductor != NULL)
			{
				add(&new_h, conductor->key, conductor->value);
				conductor = conductor->next;
			}
		}
	}
	h = &new_h;
	return;
}

void add(HashTable *h, char *str_origin, char *value)
{
	int i = hash(str_origin, h->count), k;
	list *conductor = (list*)malloc(sizeof(list));
	h->length[i]++;
	h->width = max(h->width, h->length[i]);
	if (h->table[i] == NULL)
	{
		h->table[i] = (list*)malloc(sizeof(list));
		for (k = 0; str_origin[k] != '\0'; k++)
		{
			h->table[i]->key[k] = str_origin[k];
		}
		h->table[i]->key[k] = '\0';
		for (k = 0; value[k] != '\0'; k++)
		{
			h->table[i]->value[k] = value[k];
		}
		h->table[i]->value[k] = '\0';
		h->table[i]->next = NULL;
	}
	else
	{
		conductor->next = h->table[i]->next;
		memcpy(conductor->key, h->table[i]->key, sizeof(h->table[i]->key));
		memcpy(conductor->value, h->table[i]->value, sizeof(h->table[i]->value));
		for (k = 0; str_origin[k] != '\0'; k++)
		{
			h->table[i]->key[k] = str_origin[k];
		}
		h->table[i]->key[k] = '\0';
		for (k = 0; value[k] != '\0'; k++)
		{
			h->table[i]->value[k] = value[k];
		}
		h->table[i]->value[k] = '\0';
		h->table[i]->next = conductor;
	}
	return;
}

int strcomp(char *str, char *str_new)
{
	int i;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] != str_new[i])
		{
			return 0;
		}
	}
	if (str[i] == '\0' && str_new[i] != '\0')
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void delete_key(HashTable *h, char *str)
{
	int i = hash(str, h->count);
	list *conductor;
	conductor = h->table[i];
	while (conductor && !strcomp(conductor->key, str))
	{
		conductor = conductor->next;
	}

	if (conductor && strcomp(conductor->key, str))
	{
		if (h->table[i]->next == NULL)
		{
			h->table[i] = NULL;
		}
		else
		{
			memcpy(conductor->key, h->table[i]->key, sizeof(h->table[i]->key));
			memcpy(conductor->value, h->table[i]->value, sizeof(h->table[i]->value));
			memcpy(h->table[i]->key, h->table[i]->next->key, sizeof(h->table[i]->next->key));
			memcpy(h->table[i]->value, h->table[i]->next->value, sizeof(h->table[i]->next->value));
			h->table[i]->next = NULL;
		}
		h->length[i]--;
	}
	return;
}

char *search(HashTable *h, char *str)
{
	int i = hash(str, h->count);
	list *conductor;
	conductor = h->table[i];
	while (conductor && !strcomp(conductor->key, str))
	{
		conductor = conductor->next;
	}
	if (strcomp(conductor->key, str))
	{
		printf("%s\n", conductor->value);
	}
	else
	{
		printf("Not found!\n");
	}
}

void print(HashTable *h)
{
	int i;
	list *conductor;
	for (i = 0; i < h->size; i++)
	{
		printf("%d) ", i + 1);
		conductor = h->table[i];
		while (conductor)
		{
			printf("\'%s\' : \'%s\'; ", conductor->key, conductor->value);
			conductor = conductor->next;
		}
		printf("\n");
	}
	return;
}

int main()
{
	HashTable Hash;
	int choice, i;
	list *conductor;
	char *str = (char*)malloc(sizeof(char) * STRING_LENGTH), *value = (char*)malloc(sizeof(char) * STRING_LENGTH), *temp;
	init(&Hash, SIZE);
	do
	{
		printf("Please choose the option:\n 0 - to exit\n 1 - add key to the table\n 2 - delete key from the table\n 3 - search key in the table\n 4 - print the table\n");
		scanf_s("%d", &choice);
		scanf_s("%*[^\n]");
		switch (choice)
		{
		case 0:
			break;
		case 1:
			getchar();
			gets(str);
			gets(value);
			add(&Hash, str, value);
			if(Hash.width > MAX_LENGTH)
			{
				Hash.count++;
				new_hash(&Hash);
			}
			break;
		case 2:
			getchar();
			gets(str);
			delete_key(&Hash, str);
			break;
		case 3:
			getchar();
			gets(str);
			search(&Hash, str);
			break;
		case 4:
			print(&Hash);
			break;
		default:
			printf("\nIncorrect input, please try again\n\n");
			break;
		}
	} while (choice != 0);
	getchar();
	return 0;
}