#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MEMSIZE 1000
#define FREE -2	
#define LOCK -1	

void *memory;

void init()
{
	memory = malloc((MEMSIZE + 1)*sizeof(int));
	for (int i = 0; i < MEMSIZE - 1; i++)
	{
		((int*)memory)[i] = FREE;
	}
}

void *myMalloc(int size)
{	/*
	for (int i = 0; i < MEMSIZE - 1; i++)
	{
		printf("%d ", ((int*)memory)[i]);
	}

	printf("\n");
	*/

	int place = 0;
	int block = (size + sizeof(int) - 1) / sizeof(int);
	while (block > 0)
	{
		for (int i = 0; i < MEMSIZE; i++)
			if (((int*)memory)[i] == FREE)
			{
				block--;
				if (block == 0)
				{
					place = i;
					break;
				}
			}
			else block = (size + sizeof(int) - 1) / sizeof(int);
	}
	if (block != 0)
		return NULL;
	else
	{
		block = (size + sizeof(int) - 1) / sizeof(int);
		for (int i = place - block + 1; i <= place; i++)
			((int*)memory)[i] = LOCK;
		/*
		for (int i = 0; i < MEMSIZE - 1; i++)
		{
			printf("%d ", ((int*)memory)[i]);
		}
		
		printf("\n");
		printf("\n");
		*/
		int *p;
		p = (int*)memory;
		return (p + place - block + 1);
	}
}


void myFree(void *ptr)
{
	while ((*((int*)ptr) != FREE))
	{
		*((int*)ptr) = FREE;
		((int*)ptr)++;
	}
	/*
	for (int i = 0; i < MEMSIZE - 1; i++)
	{
		printf("%d ", ((int*)memory)[i]);
	}
	*/
	printf("\n");
}


void *myRealloc(void *ptr, int size)
{
	int *array = (int*)myMalloc(size);

	int j = 0;
	while ((*((int*)ptr) != FREE) && (*((int*)ptr) != LOCK))
	{
		j++;
		((int*)ptr)++;
	}
	((int*)ptr) -= j;
	int i = 0;
	while (j != 0 && i != size)
	{
		array[i] = *((int*)ptr);
		*((int*)ptr) = FREE;
		((int*)ptr)++;
		i++; j--;
	}
	/*
	for (int i = 0; i < MEMSIZE - 1; i++)
	{
		printf("%d ", ((int*)memory)[i]);
	}
	printf("\n");
	*/
	return ((int*)array);
}


int main()
{
	init();
	int *array = (int*)myMalloc(15 * sizeof(int));
	for (int i = 0; i < 15; i++)
		array[i] = i;

	/*
	for (int i = 0; i < 15; i++)
		printf("%d ", array[i]);

	printf("\n");
	*/

	printf("this is memory with original array. Available = -2, occupied = -1 \n ");
	for (int i = 0; i < MEMSIZE - 1; i++)
		printf("%d ", ((int*)memory)[i]);

	printf("\n");

	array = (int*)myRealloc(array, 20 * sizeof(int));

	printf("this is memory with realloc.  Copy the old array and an increase of five\n");
	for (int i = 0; i < MEMSIZE - 1; i++)
		printf("%d ", ((int*)memory)[i]);
	printf("\n");
	
	myFree(array);
	printf("this is memory with delete massive\n");
	for (int i = 0; i < MEMSIZE - 1; i++)
		printf("%d ", ((int*)memory)[i]);

	free(memory);

	return 0;
}