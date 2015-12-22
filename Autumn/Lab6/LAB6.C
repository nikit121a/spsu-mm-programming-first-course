/*Leonid Voroshilov, 143*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>

#define N 8
int counter[N];

#define  limit log2(N)

typedef struct tagList List;

struct tagList
{
	char * String;
	int len;
	List *Next;
};


int is_prime(int x)
{
	int i = 2;

	if (x == 2)
		return 1;

	for (; i < sqrt(x) + 1; i++)
		if (x % i == 0)
			return 0;

	return 1;
}



int hash(char *str, int len)
{
	static int p = 31;
	int i = 0;
	if (len == -1)
	{
		p += 2;

		while (!is_prime(p))
			p += 2;
		return 0;
	}
	int hash = str[0];

	for (i = 1; i < len; i++)
	{
		int v = str[i];
		int j;
		for (j = i; j > 0; j--)
			v = (v * p) % N;
		hash += v;
		hash = hash % N;
	}

	return hash;
}
int delete (List **Table, char *str, int len)
{

	int h = hash(str, len);
	List * Ptr = Table[h], *Ptr1;
	if (counter[h] == 0)
		return 0;
	if (counter[h] == 1)
	{
		free(Ptr);
		counter[h]--;
		Ptr = NULL;
		return 1;
	}
	
	Ptr1 = Ptr;

	if (strcmp(Ptr->String, str) == 0)
	{
		Ptr = Ptr->Next;
		free(Ptr1);
		counter[h]--;
		return 1;
	}
	
	Ptr = Ptr->Next;

	while (Ptr != NULL)
	{
		if (strcmp(Ptr->String, str) == 0)
		{

			counter[h]--;
			Ptr1->Next = Ptr->Next;
			free(Ptr);
			return 1;
		}
		Ptr = Ptr->Next;
		Ptr1 = Ptr1->Next;
	}

	printf("There is no such string!\n");
	return 0;

}

int exisit(List **Table, char *str, int len)
{
	int h = hash(str, len);
	List * Ptr = Table[h];
	if (counter[h] == 0)
		return 0;
	while (Ptr != NULL)
	{
		if (strcmp(Ptr->String, str) == 0 )
			return 1;
		Ptr = Ptr->Next;
	}
	return 0;
}
int check(List** Table)
{
	int i;
	int j = limit;
	for (i = 0; i < N; i++)
		if (counter[i] >= limit)
			return 0;

	return 1;
}

void rebalance(List** table)
{
	while (check(table) == 0)
	{
		List* tmp[N];
		int tmp_counter[N];
		int i;
		
		for (i = 0; i < N; i++)
		{
			tmp[i] = table[i];
			table[i] = NULL;
			tmp_counter[i] = counter[i];
			counter[i] = 0;
			table[i] = (List*)malloc(sizeof(List));
			table[i]->Next = NULL;
		}

		hash(NULL, -1);
		for (i = 0; i < N; i++)
		{
			List * Ptr = tmp[i], *Ptr1;
			while (tmp_counter[i] > 0)
			{
				add(table, Ptr->String, Ptr->len);
				Ptr1 = Ptr;
				Ptr = Ptr->Next;
				free(Ptr1);
				tmp_counter[i]--;
			}
		}
	}

	printf("Rebalanced!\n");

}


int add(List ** Table, char* str, int len)
{
	if (exisit(Table, str, len) == 1)
	{
		printf("Already exist!\n");
		return 1;
	}

	int h = hash(str, len);
	List * Ptr = Table[h];
	if (counter[h] == 0)
	{
		Ptr->String = (char*)malloc(len * sizeof(char));
		strcpy(Ptr->String, str);
		Ptr->len = len;
		counter[h]++;
		return 1;
	}
	while (Ptr->Next != NULL)
		Ptr = Ptr->Next;

	Ptr->Next = (List *)malloc(sizeof(List));

	if (Ptr->Next == NULL)
	{
		printf("memory allocation error\n");
		return 0;
	}

	Ptr->Next->String = (char*)malloc(len * sizeof(char));
	Ptr->Next->len = len;
	Ptr->Next->Next = NULL;
	strcpy(Ptr->Next->String, str);
	counter[h]++;
	
	if (check(Table) == 0)
		rebalance(Table);

	return 1;
}





void init(List ** table)
{
	int i;
	for (i = 0; i < N; i++)
	{
		table[i] = (List*)malloc(sizeof(List));
		table[i]->Next = NULL;
	}
}

void main(void)
{
	int flag = 1, n;
	List * Table[N];
	init(Table);

	

	while (flag)
	{
		printf(" 0 - exit \n 1 - add\n 2 - check if exist \n 3 - delete \n >>");
		char buf[100];
		scanf("%i", &n);

		scanf("%*[^\n]");
		scanf("%*c");


		switch (n)
		{
		case(0) :
			flag = 0;
			break;

		case(1) :
			printf("\n Input a string: ");
			fgets(buf, 100, stdin);
			add(Table, buf, strlen(buf));
			break;

		case(2) :
			printf("\n Input a string: ");
			fgets(buf, 100, stdin);
			if (exisit(Table, buf, strlen(buf)))
				printf("\n EXIST!\n");
			else 
				printf("\n DON'T EXIST!\n");

			break;

		case(3) :
			printf("\n Input a string: ");
			fgets(buf, 100, stdin);;
			delete(Table, buf, strlen(buf));
			break;

		default:
			printf("Incorrect input!\n");
			break;
		}
	}

	

}