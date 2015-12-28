#include <stdio.h>
#include <stdlib.h>
#include  <string.h>
#include <stdbool.h>

#define MAX_HASH 127
#define MAX_CHAIN 3
#define KEY_LENGTH 20
#define uchar unsigned char

typedef struct
{
	uchar *key;
} data;

typedef struct
{
	data *chain;
	int chain_size;
} table_struct;

table_struct *table;
int hash_base = 31;

int hash(uchar *key)
{
	int result = 0, cur_p = 1;

	for (int i = 0; i < KEY_LENGTH; i++)
	{
		result = (result + key[i] * cur_p) % MAX_HASH;
		cur_p *= hash_base;
	}

	return result;
}

void add_ht(uchar *key, int mode)
{
	int cur_hash = hash(key);
	
	if (table[cur_hash].chain_size == MAX_CHAIN)
	{
		printf("Impossible to add\n");
		return;
	}

	for (int i = 0; i < KEY_LENGTH; i++)
	{
		table[cur_hash].chain[table[cur_hash].chain_size].key[i] = key[i];
	}

	table[cur_hash].chain_size++;
	if (table[cur_hash].chain_size == MAX_CHAIN && mode == 0)
	{ //rebalance_ht

		if (hash_base == 53)
		{
			printf("Rebalance is impossible.\n");
			return;
		}

		data* buffer = (data*)malloc(sizeof(data) * MAX_CHAIN * MAX_HASH);

		for (int i = 0; i < MAX_CHAIN * MAX_HASH; i++)
		{
			buffer[i].key = (uchar*)malloc(sizeof(uchar) * KEY_LENGTH);
		}

		int buffer_head = 0;


		for (int i = 0; i < MAX_HASH; i++)
		{
			if (table[i].chain_size > 0)
			{
				for (int j = 0; j < table[i].chain_size; j++)
				{
					for (int k = 0; k < KEY_LENGTH; k++)
					{
						buffer[buffer_head].key[k] = table[i].chain[j].key[k];
					}
					buffer_head++;
				}
			}
		}

		hash_base = 53;

		for (int i = 0; i < MAX_HASH; i++)
		{
			table[i].chain_size = 0;
		}


		for (int i = 0; i < buffer_head; i++)
		{
			add_ht(buffer[i].key, 1);
		}

		printf("Table was rebalanced, base for hash: %d\n", hash_base);

		for (int i = 0; i < MAX_CHAIN * MAX_HASH; i++)
		{
			free(buffer[i].key);
		}

		free(buffer);
	}
	return;
}	

int check(uchar *key)
{
	int cur_hash = hash(key);

	for (int i = 0; i < table[cur_hash].chain_size; i++)
	{
		bool flag = true;
		for (int j = 0; j < KEY_LENGTH; j++)
		{
			if (table[cur_hash].chain[table[cur_hash].chain_size - 1].key[j] != key[j])
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

void delete_ht(uchar *key)
{

	int position = check(key), key_hash = hash(key);

	for (int i = 0; i < KEY_LENGTH; i++)
	{
		table[key_hash].chain[position].key[i] = table[key_hash].chain[table[key_hash].chain_size].key[i];
	}

	table[key_hash].chain_size--;
	return;
}






void main()
{
	table = (table_struct*)malloc(sizeof(table_struct) * MAX_HASH);
	for (int i = 0; i < MAX_HASH; i++)
	{
		table[i].chain = (data*)malloc(sizeof(data) * MAX_CHAIN);
		for (int j = 0; j < MAX_CHAIN; j++)
		{
			table[i].chain[j].key = (uchar*)malloc(sizeof(uchar) * KEY_LENGTH);
			memset(table[i].chain[j].key, 0, KEY_LENGTH);
		}
		table[i].chain_size = 0;
	}

	int switcher = 0;
	uchar *cur_key = (uchar*)malloc(sizeof(uchar) * KEY_LENGTH);
	while (switcher != 4)
	{
		memset(cur_key, 0, KEY_LENGTH);
		printf("Enter the key: ");
		scanf("%s", cur_key);
		scanf("%*[^\n]");
		printf("1 - install, 2 - delete, 3 - find, 4 - exit ");
		scanf("%d", &switcher);
		switch (switcher)
		{
		case 1:
			add_ht(cur_key, 0);
			printf("Success.\n");
		
			break;
		case 2:
			if (check(cur_key) == -1)
			{
				printf("No such key");
				return;
			}
			else
			{
				delete_ht(cur_key);
				printf("Success.\n");

			}
			break;
		case 3:
			if (check(cur_key) == -1)
			{
				printf("No such key. \n");
			}
			else
			{
				printf("Success. \n");
			}
			break;
		case 4:
			for (int i = 0; i < MAX_HASH; i++)
			{
				for (int j = 0; j < MAX_CHAIN; j++)
				{
					free(table[i].chain[j].key);
				}
				free(table[i].chain);
			}
			free(table);
			break;
		default:
			printf("Enter valid key.\n");
			break;
		}
	}

	return;
}
