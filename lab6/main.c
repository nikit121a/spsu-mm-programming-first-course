#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define osn 31
#define max_chain 5
#define s_length 256
#define table_size 17390
#define edge_chain 2

int base_list[11] = {7, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71};
int cur_base = 0, last_correct_base = 0;


long long hash(char s[s_length])
{
	/*hash[s] = s[0] + s[1] * p + s[2] * p^2...*/
	long long result = 0, cur_p = 1;
	int i = 0;

	while (s[i] > 0)
	{
		result = (result + (s[i] * cur_p) % table_size) % table_size;
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

void put_in_table(char** hash_table, int* chain_size, char cur_s[s_length], int hash)
{
	
	for (int i = 0; i < s_length; i++)
	{
		hash_table[hash][chain_size[hash] * s_length + i] = cur_s[i];
	}
	chain_size[hash] ++;

	return;
}

void table_rebalance(char** hash_table, int* chain_size) 
{
	char* buffer = (char*)malloc(sizeof(char[s_length]) * table_size * (max_chain + 1) + 1);
	int buffer_head = 0;


	if(cur_base == 9) 
	{
		/* means that all hashes cause collisions*/
		cur_base = last_correct_base - 1;
		printf("Rebalance is impossible, back to the inital base\n");
		table_rebalance(hash_table, chain_size);
		return;
	}

	for (int i = 0; i < table_size; i++)
	{
		/*puts all data in the buffer*/
		if(chain_size[i] > 0)
		{
			for (int j = 0; j <= chain_size[i] * s_length; j++)
			{
				buffer[j + buffer_head * s_length] = hash_table[i][j];
			}
			buffer_head += chain_size[i];
		}
	}

	cur_base++;
	memset(chain_size, 0, sizeof(int) * table_size);


	for (int i = 0; i < buffer_head; i++)
	{
		/*puts all data back in table with new hashes*/
		char cur_s[s_length];
		for (int j = i * s_length; j < (i + 1) * s_length; j++)
		{
			cur_s[j - i * s_length] = buffer[j];
		}
		put_in_table(hash_table, chain_size, cur_s, hash(&cur_s));
	}

	if(!is_correct(chain_size, 0, table_size) &&
		last_correct_base != cur_base) //in case of "derebalance"
	{
		/*If rebalance did not help*/
		printf("Rebalance with base %d has failed. Trying  another base...\n", base_list[cur_base]);
		table_rebalance(hash_table, chain_size);
		return;
	}
	last_correct_base = cur_base;
	printf("Table was rebalanced, base for hash: %d\n", base_list[cur_base]);
	free(buffer);
}


void remove_from_table(char** hash_table, int* chain_size, int s_pos, int hash)
{
	/*function "find_string" returns position of the string, so it's easy to remove the string*/
	for (int i = (s_pos - 1) * s_length; i < (chain_size[hash]) * s_length; i++)
	{
		hash_table[hash][i] = hash_table[hash][i + s_length];
	}
	chain_size[hash]--;
	return;
}

int find_string(char** hash_table, int* chain_size, char cur_s[s_length], int hash)
{
	/*Tries to find string in table*/
	int result = 0;
	for (int i = 0; i < chain_size[hash]; i++)
	{
		int cur_res = 1;
		for (int j = 0; j < 256; j++)
		{
			if(hash_table[hash][i * s_length + j] != cur_s[j])
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


int main()
{
	char** hash_table = (char**)malloc(sizeof(char*) * (table_size + 1));
	for (int i = 0; i < table_size; i++)
	{
		hash_table[i] = (char*)malloc(sizeof(char[s_length]) * (max_chain + 1));
		memset(hash_table[i], 0, sizeof(char[s_length]) * (max_chain + 1));
	}

	int* chain_size = (int*)malloc(sizeof(int) * (table_size + 1));

	memset(chain_size, 0, sizeof(int) * (table_size + 1));

	int action_num = 0;
	while (action_num != 4) 
	{
		
		printf("\nInput the key(1 - add, 2 - remove, 3 - check, 4 - exit): ");
		action_num = -1;
		scanf("%d", &action_num);
		scanf("%*[^\n]");

		char cur_s[s_length * 2];
		memset(cur_s, 0, s_length * 2);

		if(action_num == 1 || action_num == 2 || action_num == 3)
		{
			printf("Input the string: ");
			scanf("%s", &cur_s);
		}

		switch (action_num)
		{
		case 1: 
			put_in_table(hash_table, chain_size, cur_s, hash(cur_s));
			if(!is_correct(chain_size, hash(cur_s), hash(cur_s))) 
			{
				printf("Table has to be rebalanced. Please, wait...\n");
				table_rebalance(hash_table, chain_size);
			}
			printf("The string was successfully added.\n");
			break;
		case 2:
			if(find_string(hash_table, chain_size, cur_s, hash(cur_s)))
			{
				remove_from_table(hash_table, chain_size, find_string(hash_table, chain_size, cur_s, hash(cur_s)), hash(cur_s));
				printf("String was successfully removed.\n");
			}
			else
			{
				printf("There is no such string in the table.\n");
			}
			break;
		case 3:
			if(find_string(hash_table, chain_size, cur_s, hash(cur_s)))
			{
				printf("The table contains this string.\n");
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
		free(hash_table[i]);
	}
	free(hash_table);
	free(chain_size);
	return 0;

}