#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_chain 50
#define key_length 25
#define val_length 150
#define table_size 37813
#define edge_chain 2

int base_list[11] = {7, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71};
int cur_base = 0, last_correct_base = 0;


typedef struct {
	char[key_length] key;
	char[val_length] val;
} data;

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
		if(chain_size[i] > edge_chain) 
		{
			return 0;
		}
	}
	return 1;
}

void put_in_table(data** data_table, int* chain_size, char cur_key[key_length], int hash, char cur_val[val_length])
{
	
	for (int i = 0; i < key_length; i++)
	{
		data_table[hash][chain_size[hash]].key[i] = cur_key[i];
	}


	for (int i = 0; i < val_length; i++)
	{
		data_table[hash][chain_size[hash]].val[i] = cur_val[i];
	}
	chain_size[hash] ++;

	return;
}

void table_rebalance(data** data_table, data** data_table, int* chain_size) 
{
	data* buffer_data = (data*)malloc(sizeof(data) * (table_size + 1));


	int buffer_head = 0;


	if(cur_base == 9) 
	{
		/* means that all hashes cause collisions*/
		cur_base = last_correct_base - 1;
		printf("Rebalance is impossible, back to the inital base\n");
		table_rebalance(data_table, chain_size);
		return;
	}

	for (int i = 0; i < table_size; i++)
	{
		/*puts all data in the buffer*/
		if(chain_size[i] > 0)
		{
			for (int j = 0; j < chain_size[i]; j++)
			{
				buffer_data[buffer_head].key = data_table[i][j].key;
				buffer_data[buffer_head].val = data_table[i][j].val;
			}
			buffer_head += chain_size[i];
		}
	}

	cur_base++;
	memset(chain_size, 0, sizeof(int) * table_size);


	for (int i = 0; i < buffer_head; i++)
	{
		/*puts all data back in table with new hashes*/

		data cur_data;

		cur_data.key = buffer_data[i].key;
		cur_data.val = buffer_data[i].val
		put_in_table(data_table, chain_size, cur_data, hash(cur_data.val));
	}

	if(!is_correct(chain_size, 0, table_size) &&
		last_correct_base != cur_base) //in case of "derebalance"
	{
		/*If rebalance did not help*/
		printf("Rebalance with base %d has failed. Trying  another base...\n", base_list[cur_base]);
		table_rebalance(data_table, chain_size);
		return;
	}
	last_correct_base = cur_base;
	printf("Table was rebalanced, base for hash: %d\n", base_list[cur_base]);
	free(buffer_data);
}


void remove_from_table(data** data_table, int* chain_size, int s_pos, int hash)
{
	/*function "find_string" returns position of the string, so it's easy to remove the string*/
	for (int i = (s_pos - 1) * key_length; i < (chain_size[hash]) * key_length; i++)
	{
		data_table[hash][i] = data_table[hash][i + key_length];
	}
	chain_size[hash]--;
	return;
}

int find_key(data** data_table, int* chain_size, char cur_key[key_length], int hash)
{
	/*Tries to find string in table*/
	int result = 0;
	for (int i = 0; i < chain_size[hash]; i++)
	{
		int cur_res = 1;
		for (int j = 0; j < key_length; j++)
		{
			if(data_table[hash][i * key_length + j] != cur_key[j])
			{
				cur_res = 0;
			}
		}
		if(cur_res == 1)
		{
			result = i + 1;
		}
	}
	return result;
}

void print_val(data** data_table,int hash,int num)
{
	int i = val_length * (num - 1); 
	printf("Value: ");
	while (data_table[hash][i] != 0)
	{
		printf("%c", data_table[hash][i]);
		i++;
	}
	printf("\n");
}


int main()
{
	data** data_table = (data**)malloc(sizeof(data*) * (table_size + 1));

	for (int i = 0; i < table_size; i++)
	{
		data_table[i] = (data*)malloc(sizeof(data) * (max_chain + 1));
		memset(data_table[i], 0, sizeof(data) * (max_chain + 1));
	}

	int* chain_size = (int*)malloc(sizeof(int) * (table_size + 1));

	memset(chain_size, 0, sizeof(int) * (table_size + 1));

	int action_num = 0;
	while (action_num != 4) 
	{
		
		printf("\nChoose the operation(1 - add, 2 - remove, 3 - check, 4 - exit): ");
		action_num = -1;
		scanf("%d", &action_num);
		scanf("%*[^\n]");

		char cur_val[val_length * 2];
		memset(cur_val, 0, val_length * 2);

		char cur_key[key_length * 2];
		memset(cur_key, 0, key_length * 2);

		if(action_num == 1 || action_num == 2 || action_num == 3)
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
			put_in_table(data_table, chain_size, cur_data, hash(cur_data.val));
			if(!is_correct(chain_size, hash(cur_key), hash(cur_key))) 
			{
				printf("Table has to be rebalanced. Please, wait...\n");
				table_rebalance(data_table, chain_size);
			}
			printf("The string was successfully added.\n");
			break;
		case 2:
			if(find_key(data_table, chain_size, cur_data, hash(cur_data.val)))
			{
				remove_from_table(data_table, chain_size, find_key(data_table, chain_size, cur_data, hash(cur_data.val)), hash(cur_data.val));
				printf("String was successfully removed.\n");
			}
			else
			{
				printf("There is such hash in the table.\n");
			}
			break;
		case 3:
			if(find_key(data_table, chain_size, cur_data, hash(cur_data.val)))
			{
				print_val(data_table, hash(cur_key), find_key(data_table, chain_size, cur_data, hash(cur_data.val)));
			}
			else
			{
				printf("There is no such string in the table.\n");
			}
			break;
		case 4:
			break;
		default:
			printf("Please, choose correctly.\n");
			break;
		}
		
	}
	
	
	for (int i = 0; i < table_size; i++)
	{
		free(data_table[i]);
	}
	free(data_table);
	free(chain_size);
	return 0;

}