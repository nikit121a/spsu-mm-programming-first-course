#include <stdio.h>
#include <stdlib.h>
#include  <string.h>
#include <stdbool.h>

#define MAX_HASH 16127
#define MAX_CHAIN 5

typedef struct 
{
	unsigned char key[10];
	unsigned char value[20];
} data;

typedef struct
{
	data *chain;
	int chain_size;
} table_struct;

table_struct *table;
int p = 31;

int hash(char key[10])
{
	int result = 0, cur_p = 1;

	for (int i = 0; i < 10; i++)
	{
		result = (result +  key[i] * cur_p) % MAX_HASH;
		cur_p *= p;
	}
	
	return result;
}

void add_ht(data pair)
{
	if (table[hash(pair.key)].chain_size == MAX_CHAIN)
	{
		printf("Impossible to add\n");
		return;
	}

	for (int i = 0; i < 10; i++)
	{
		table[hash(pair.key)].chain[hash(pair.key)].key[i] = pair.key[i];
	}

	for (int i = 0; i < 20; i++)
	{
		table[hash(pair.key)].chain[hash(pair.key)].value[i] = pair.value[i];
	}
	
	table[hash(pair.key)].chain_size++;
	printf("Success. \n");
	return;
}

int check(char key[20])
{
	for (int i = 0; i < table[hash(key)].chain_size; i++)
	{
		bool flag = true;
		for (int j = 0; j < 10; j++)
		{
			if (table[hash(key)].chain[hash(key)].key[j] != key[j])
			{
				flag = false;
			}
		}
		if (flag == true)
		{
			return i;
		}
	}

	return -1;
	
}

void delete_ht(char key[20])
{
	if (check(key) == -1)
	{
		printf("No such key");
		return;
	}

	int position = check(key), key_hash = hash(key);
	
	for (int i = 0; i < 10; i++)
	{
		table[key_hash].chain[position].key[i] = table[key_hash].chain[table[key_hash].chain_size].key[i];
	}

	for (int i = 0; i < 20; i++)
	{
		table[key_hash].chain[position].value[i] = table[key_hash].chain[table[key_hash].chain_size].value[i];
	}

	table[key_hash].chain_size--;
	printf("Success. \n");
	return;
}




void main()
{
	table = (table_struct*)malloc(sizeof(table_struct*) * MAX_HASH);
	for (int i = 0; i < MAX_HASH; i++)
	{
		table[i].chain = (data*)malloc(sizeof(data) * MAX_CHAIN);
		table[i].chain_size = 0;
	}

	int switcher = 0;

	while (switcher != 4)
	{
		data cur_data;
		memset(&cur_data.key, 0, 10);
		printf("Enter the key: ");
		scanf("%s", cur_data.key);
		scanf("%*[^\n]");
		printf("1 - install, 2 - delete, 3 - find, 4 - exit ");
		scanf("%d", &switcher);
		switch (switcher)
		{
		case 1:
			printf("Enter the value: ");
			scanf("%s", cur_data.value);
			add_ht(cur_data);
			break;
		case 2:
			delete_ht(cur_data.key);
			break;
		case 3:
			if (check(cur_data.key) == -1)
			{
				printf("No such key. \n");
			}
			else
			{
				printf("Success. \n");
			}
			break;
		default:
			printf("Enter valid key.\n");
			break;
		}
	}
	
	return;
}





