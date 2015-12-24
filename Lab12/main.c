#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000

void *memory;

void init() 
{
	int available_memory = SIZE - sizeof(int);
	memory = (char*)malloc(SIZE + 1);
	*((char*)memory + SIZE) = 0;
	memcpy((char*)memory, &available_memory, sizeof(int));
	return;
}

void *myMalloc(size_t size)
{
	int cursor = 0, pointer;
	size_t current;
	if(size > SIZE)
	{
		return NULL;
	}
	while(cursor < SIZE && *(int*)((char*)memory + cursor) < size)
	{
		cursor += (-(*(int*)((char*)memory + cursor)) + sizeof(int));
	}
	if(cursor >= SIZE)
	{
		return NULL;
	}
	memcpy(&current, (char*)memory + cursor, sizeof(int));
	pointer = cursor + sizeof(int);
	if(current - size > sizeof(int))
	{
		*(int*)((char*)memory + cursor) = -1 * size;
		cursor += *(int*)((char*)memory + cursor) * (-1) + sizeof(int);
		*(int*)((char*)memory + cursor) = current - size - sizeof(int);
	}
	return (char*)memory + pointer;
}

void myFree(void *ptr)
{
	int current, size = -(*(int*)((char*)ptr - sizeof(int)));
	while(*((char*)ptr + current - sizeof(int)) > 0)
	{
		current += *(int*)((char*)ptr + current - sizeof(int)) + sizeof(int);
	}
	memcpy((int*)ptr - 1, &current, sizeof(int));
	return;
}

void *myRealloc(void *ptr, size_t size)
{
	int current;
	void *new_ptr;
	if(ptr == NULL)
	{
		return myMalloc(size);
	}
	if(size == 0)
	{
		myFree(ptr);
		return NULL;
	}
	memcpy(&current, (char*)ptr - sizeof(int), sizeof(int));
	current *= -1;
	if(current < size)
	{
		if(*(int*)((char*)ptr + current) > size - current)
		{
			*(int*)((char*)ptr - sizeof(int)) = -1 * size;
			*(int*)((char*)ptr + size) = current + *(int*)((char*)ptr + current) - size;
			return ptr;
		}
		else
		{
			new_ptr = myMalloc(size);
			memcpy(new_ptr, ptr, current);
			myFree(ptr);
			return new_ptr;
		}
	}
	if(current > size)
	{
		*(int*)((char*)ptr - sizeof(int)) = -1 * size;
		*(int*)((char*)ptr + size) = current + *(int*)((char*)ptr + current) - size;
		myFree((char*)ptr + size + sizeof(int));
		return(ptr);
	}
	return ptr;
}

int main()
{
	init();
	int *test, *test1;
	test = (int*)myMalloc(sizeof(int) * 20);
	test1 = (int*)myMalloc(sizeof(int) * 10000);
	test[0] = 1;
	printf("First test, adress - %p, value at test[0] - %d\n", test, test[0]);
	printf("Second test, asked blocksize is too big, adress - %p\n", test1);
	myFree(test);
	printf("Third test, after myFree - %p\n", test);
	test = (int*)myRealloc(test, sizeof(int) * 5);
	test[3] = 11;
	printf("Fourth test, after myRealloc, adress - %p, value at test[3] - %d\n", test, test[3]);
	getchar();
	free(memory);
	return 0;
}