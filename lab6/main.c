#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_chain 50
#define key_length 25
#define val_length 150
#define table_size 37813
#define edge_chain 2


typedef struct {
	char** hash_table; 
	char** val_table;
	int* chain_size;
} data;

int base_list[11] = { 7, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71 };
int cur_base = 0, last_correct_base = 0;


int hash(char key[key_length])
{
	/*hash[s] = s[0] + s[1] * p + s[2] * p^2...*/
	long long result = 0, cur_p = 1;
	int i = 0;

	while (key[i] > 0)
	{
		result = (result + (key[i] * cur_p) % table_size) % table_size;
		cur_p *= base_list[cur_base];
		i++;
	}
	return result;
}

short is_correct(int* chain_size, int l, int r) // table validation
{
	for (int i = l; i <= r; i++)
	{
		if (chain_size[i] > edge_chain)
		{
			return 0;
		}
	}
	return 1;
}

void put_in_table(data table_data, char cur_key[key_length], int hash, char cur_val[val_length])
{

	for (int i = 0; i < key_length; i++)
	{
		table_data.hash_table[hash][table_data.chain_size[hash] * key_length + i] = cur_key[i];
	}


	for (int i = 0; i < val_length; i++)
	{
		table_data.val_table[hash][table_data.chain_size[hash] * val_length + i] = cur_val[i];
	}
	table_data.chain_size[hash] ++;

	return;
}

void table_rebalance(data table_data)
{
	char* buffer_val = (char*)malloc(sizeof(char[val_length]) * table_size * (max_chain + 1) + 1);

	char* buffer_key = (char*)malloc(sizeof(char[key_length]) * table_size * (max_chain + 1) + 1);

	int buffer_head = 0;


	if (cur_base == 9)
	{
		/* means that all hashes cause collisions*/
		cur_base = last_correct_base - 1;
		printf("Rebalance is impossible, back to the inital base\n");
		table_rebalance(table_data);
		return;
	}

	for (int i = 0; i < table_size; i++)
	{
		/*puts all data in the buffer*/
		if (table_data.chain_size[i] > 0)
		{
			for (int j = 0; j <= table_data.chain_size[i] * key_length; j++)
			{
				buffer_key[j + buffer_head * key_length] = table_data.hash_table[i][j];
			}

			for (int j = 0; j <= table_data.chain_size[i] * val_length; j++)
			{
				buffer_val[j + buffer_head * val_length] = table_data.val_table[i][j];
			}
			buffer_head += table_data.chain_size[i];
		}
	}

	cur_base++;
	memset(table_data.chain_size, 0, sizeof(int) * table_size);


	for (int i = 0; i < buffer_head; i++)
	{
		/*puts all data back in table with new hashes*/

		char cur_key[key_length];
		char cur_val[val_length];

		for (int j = i * key_length; j < (i + 1) * key_length; j++)
		{
			cur_key[j - i * key_length] = buffer_key[j];
		}

		for (int j = i * val_length; j < (i + 1) * val_length; j++)
		{
			cur_val[j - i * val_length] = buffer_val[j];
		}
		put_in_table(table_data, cur_key, hash(cur_key), cur_val);
	}

	if (!is_correct(table_data.chain_size, 0, table_size) &&
		last_correct_base != cur_base) //in case of "derebalance"
	{
		/*If rebalance did not help*/
		free(buffer_key);
		free(buffer_val);
		printf("Rebalance with base %d has failed. Trying  another base...\n", base_list[cur_base]);
		table_rebalance(table_data);
		return;
	}
	last_correct_base = cur_base;
	printf("Table was rebalanced, base for hash: %d\n", base_list[cur_base]);
	free(buffer_key);
	free(buffer_val);
}


void remove_from_table(data table_data, int s_pos, int hash)
{
	/*function "find_string" returns position of the string, so it's easy to remove the string*/
	for (int i = (s_pos - 1) * key_length; i < (table_data.chain_size[hash]) * key_length; i++)
	{
		table_data.hash_table[hash][i] = table_data.hash_table[hash][i + key_length];
	}
	table_data.chain_size[hash]--;
	return;
}

int find_key(data table_data, char cur_key[key_length], int hash)
{
	/*Tries to find string in table*/
	int result = 0;
	for (int i = 0; i < table_data.chain_size[hash]; i++)
	{
		int cur_res = 1;
		for (int j = 0; j < key_length; j++)
		{
			if (table_data.hash_table[hash][i * key_length + j] != cur_key[j])
			{
				cur_res = 0;
			}
		}
		if (cur_res == 1)
		{
			result = i + 1;
		}
	}
	return result;
}

void print_val(char** val_table, int hash, int num)
{
	int i = val_length * (num - 1);
	printf("Value: ");
	while (val_table[hash][i] != 0)
	{
		printf("%c", val_table[hash][i]);
		i++;
	}
	printf("\n");
}


int main()
{
	data table_data;
	table_data.hash_table = (char**)malloc(sizeof(char*) * (table_size + 1));
	table_data.val_table = (char**)malloc(sizeof(char*) * (table_size + 1));

	for (int i = 0; i < table_size; i++)
	{
		table_data.hash_table[i] = (char*)malloc(sizeof(char[key_length]) * (max_chain + 1));
		table_data.val_table[i] = (char*)malloc(sizeof(char[val_length]) * (max_chain + 1));

		memset(table_data.val_table[i], 0, sizeof(char[val_length]) * (max_chain + 1));
		memset(table_data.hash_table[i], 0, sizeof(char[key_length]) * (max_chain + 1));
	}

	table_data.chain_size = (int*)malloc(sizeof(int) * (table_size + 1));

	memset(table_data.chain_size, 0, sizeof(int) * (table_size + 1));

	int action_num = 0;
	while (action_num != 4)
	{

		printf("\nInput the key(1 - add, 2 - remove, 3 - check, 4 - exit): ");
		action_num = -1;
		scanf("%d", &action_num);
		scanf("%*[^\n]");

		char cur_val[val_length * 2];
		memset(cur_val, 0, val_length * 2);

		char cur_key[key_length * 2];
		memset(cur_key, 0, key_length * 2);

		if (action_num == 1 || action_num == 2 || action_num == 3)
		{
			printf("Input the key: ");
			scanf("%s", &cur_key);
		}

		if (action_num == 1)
		{
			scanf("%*[^\n]");
			printf("Input the string: ");
			scanf("%s", &cur_val);
		}

		switch (action_num)
		{
		case 1:
			put_in_table(table_data, cur_key, hash(cur_key), cur_val);
			if (!is_correct(table_data.chain_size, hash(cur_key), hash(cur_key)))
			{
				printf("Table has to be rebalanced. Please, wait...\n");
				table_rebalance(table_data);
			}
			printf("The string was successfully added.\n");
			break;
		case 2:
			if (find_key(table_data, cur_key, hash(cur_key)))
			{
				remove_from_table(table_data, find_key(table_data, cur_key, hash(cur_key)), hash(cur_key));
				printf("String was successfully removed.\n");
			}
			else
			{
				printf("There is such hash in the table.\n");
			}
			break;
		case 3:
			if (find_key(table_data, cur_key, hash(cur_key)))
			{
				print_val(table_data.val_table, hash(cur_key), find_key(table_data, cur_key, hash(cur_key)));
			}
			else
			{
				printf("There is no such string in the table.\n");
			}
			break;
		case 4:
			break;
		default:
			printf("Please, input the valid key.\n");
			break;
		}

	}


	for (int i = 0; i < table_size; i++)
	{
		free(table_data.hash_table[i]);
		free(table_data.val_table[i]);
	}
	free(table_data.hash_table);
	free(table_data.val_table);
	free(table_data.chain_size);
	return 0;

}