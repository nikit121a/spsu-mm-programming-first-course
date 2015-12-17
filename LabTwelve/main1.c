
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 51
#define FREE 0													//свободна€ €чейка пам€ти
#define CONCERNED 1												//зан€та€ €чейка
#define LOCATED -3
void *memory;
void *memorycount;
void *mallocp;


void init()
{
	void* _memorycount = malloc((MAX_SIZE)* sizeof(int));
	memory = malloc((MAX_SIZE + 1) * sizeof(int));							//выдел€ем общую пам€ть
	for (int i = 0; i < MAX_SIZE; i++)
	{
		((int*)memory)[i] = FREE;
	}
	((int*)memory)[MAX_SIZE] = NULL;										//граница нашей пам€ти
	memorycount = _memorycount;
}

void* myMalloc(size_t size)
{
	if (size % sizeof(int) != 0)
	{
		size = size / sizeof(int) + 1;
	}
	else
	{
		size = size / sizeof(int);
	}
	int count = 0;
	(int*)mallocp = (int*)memory;
	while ((count != size) && ((((int*)mallocp)) != NULL))					//ищем свободное место
	{
		if ((*((int*)mallocp) == FREE) && (((int*)mallocp + 1) != LOCATED))
		{
			count++;
		}
		else
		{
			count = 0;
		}
		((int*)mallocp)++;
	}
	if (count == 0)															//если нет свободной пам€ти
	{
		return NULL;
	}
	else
	{
		if ((((int*)mallocp)) != NULL)
		{
			*(((int*)mallocp)) = CONCERNED;
		}
		for (int i = 0; i < size; i++)
		{
			*((int*)mallocp - i - 1) = LOCATED;
		}
		return (int*)mallocp - (int*)memory - size + (int*)memorycount;
	}
}

void myFree(void* ptr)
{
	(int*)ptr = (int*)memory - (int*)memorycount + (int*)ptr;
	while ((ptr != NULL) && (*((int*)ptr) != CONCERNED) && (*((int*)ptr) != FREE))
	{
		*((int*)ptr) = FREE;
		((int*)ptr)++;
	}
	if ((int*)ptr != NULL)
	{
		*((int*)ptr) = FREE;
	}
}

void* myRealloc(void* ptr, size_t size)
{
	ptr = (int*)memory - (int*)memorycount + (int*)ptr;
	if (size % sizeof(int) != 0)
	{
		size = size / sizeof(int) + 1;
	}
	else
	{
		size = size / sizeof(int);
	}
	if (ptr == NULL)
	{
		return myMalloc(size*sizeof(int));
	}
	if (size == 0)
	{
		myFree(ptr);
		return NULL;
	}

	int prevsize = 0;
	int *prevptr = (int*)ptr;
	while ((*prevptr != CONCERNED) && (prevptr != NULL))
	{
		prevsize++;
		prevptr++;
	}

	if (prevsize < size)									//провер€ем, есть ли дальше в пам€ти свободные €чейки
	{
		int memorysize = prevsize;
		while ((prevptr != NULL) && ((*prevptr == FREE) || (*(prevptr + 1) == FREE)) && (memorysize != size + 1))
		{
			memorysize++;
			prevptr++;
		}

		prevptr = (int*)ptr;
		if (memorysize - 1 < size)
		{
			ptr = myMalloc(size*sizeof(int));
			ptr = (int*)memory - (int*)memorycount + (int*)ptr;
		}

		for (int i = prevsize; (i < memorysize - 1) && (memorysize - 1 == size); i++)
		{
			*((int*)ptr + i) = LOCATED;
		}

		memcpy(ptr, prevptr, prevsize * sizeof(int));
		if (memorysize < size)
		{
			myFree((int*)prevptr - (int*)memory + (int*)memorycount);
		}
		while (prevsize < size)
		{
			((int*)ptr)[prevsize] = LOCATED;
			prevsize++;
		}
		if (((int*)ptr)[size] != NULL)
		{
			((int*)ptr)[size] = CONCERNED;
		}
		return (int*)ptr - (int*)memory + (int*)memorycount;
	}
	else
	{
		int i = 0;
		prevptr = (int*)ptr;
		for (i; i < size; i++)
		{
			prevptr++;
		}
		*prevptr = CONCERNED;
		prevptr++;
		myFree((int*)prevptr - (int*)memory + (int*)memorycount);
		return (int*)ptr - (int*)memory + (int*)memorycount;
	}
}

int main()
{
	init();
	printf("\n");

	int *test = (int*)myMalloc(sizeof(int) * 3);
	test[1] = 31;


	int *test1 = (int*)myMalloc(sizeof(int) * 3);
	int *test2 = (int*)myMalloc(sizeof(int) * 3);
	int i;

	for (i = 0; i < 15; i++)
	{
		if (test[i] != NULL)
		{
			printf("variable address: %p , variable value: %i\n", (int*)(test + i), test[i]);
		}
	}

	test = (int *)myRealloc(test, sizeof(int) * 5);

	for (i = 0; i < 15; i++)
	{
		if (test1[i] != NULL)
		{
			printf("variable address: %p , variable value: %i\n", (test1 + i), test1[i]);
		}
	}
	printf("\n");
	for (i = 0; i < 5; i++)
	{
		printf("After realloc - variable address: %p , variable value: %i\n", (test + i), test[i]);
	}

	_getch();
	free(memory);
	free(memorycount);
	return 0;
}
