#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEMORY 100
#define EMPTY 0
#define FULL 1 

 
void* memory;

void init()
{
	memory = (char*)malloc(MAX_MEMORY + 1);
	*((char*)memory + MAX_MEMORY) = FULL;
	*(char*)memory = EMPTY;
	int size = MAX_MEMORY - 1 - sizeof(int);
	memcpy((char*)memory + 1, &size, sizeof(int));
}

void* myMalloc(size_t size)
{
	/*first byte shows type of block (0 - empty, 1 - full)
	next 4 bytes shows size of block*/

	int cur_head = 0, is_empty = *(char*)memory;
	int result = -1;

	while (cur_head < MAX_MEMORY)
	{
		size_t cur_block_size;
		while (is_empty != EMPTY) //gets to the empty block
		{
			cur_head++;
			cur_head += *(int*)((char*)memory + cur_head) + sizeof(int);
			is_empty = *((char*)memory + cur_head);
		}

		memcpy(&cur_block_size, (char*)memory + cur_head + 1, sizeof(int));

		if(cur_block_size >= size) //checks if the current block is suitable
		{
			*((char*)memory + cur_head) = FULL;
			cur_head++;
			result = cur_head + sizeof(int);
			if(cur_block_size - size > sizeof(int) + 1)
			{
				*(int*)((char*)memory + cur_head) = size;
				cur_head += *(int*)((char*)memory + cur_head) + sizeof(int);
				*((char*)memory + cur_head) = EMPTY;
				cur_head++;
				*(int*)((char*)memory + cur_head) = cur_block_size - size - 1 - sizeof(int);
			}
			cur_head = MAX_MEMORY;
		}
		else
		{
			cur_head++;
			cur_head += *(int*)((char*)memory + cur_head) + sizeof(int);
			is_empty = *((char*)memory + cur_head);
		}
	}

	if(result == -1 || size == 0)
	{
		return NULL;
	}
	else
	{
		return (char*)memory + result;
	}
	
}


void myFree(void* ptr)
{
	*((char*)ptr - 1 - sizeof(int)) = EMPTY;
	size_t cur_head = 0;

	/*next part regroups empty blocks*/

	while (*((char*)ptr + cur_head - 1 - sizeof(int)) != FULL)
	{
		cur_head++;
		cur_head += *(int*)((char*)ptr + cur_head - 1 - sizeof(int)) + sizeof(int);
	}
	memcpy((int*)ptr - 1, &cur_head, sizeof(int));
	return;
}

void* myRealloc(void* ptr, size_t size)
{
	if (ptr == NULL)
	{
		return myMalloc(size);
	}

	if(size == 0)
	{
		free(ptr);
		return NULL;
	}

	size_t cur_size;
	memcpy(&cur_size, (int*)ptr - 1, 4);
		
	if(cur_size > size) 
	{
		*((int*)ptr - 1) = size;
		*((char*)ptr + size) = EMPTY;
		*(int*)((char*)ptr + size + 1) = *(int*)((char*)ptr + cur_size + 1) - size + cur_size;
		myFree((char*)ptr + size + 1 + sizeof(int));
		return ptr;
	}

	if (cur_size < size)
	{
		/*Checks next block. Uses it if it's empty and size is suitable
		Othewise, finds new block.*/
		if (*(char*)((char*)ptr + cur_size) == EMPTY &&
			*(int*)((char*)ptr + cur_size + 1) > size)
		{
			*((int*)ptr - 1) = size;
			*((char*)ptr + size) = EMPTY;
			*(int*)((char*)ptr + size + 1) = *(int*)((char*)ptr + cur_size + 1) - size + cur_size;
			return ptr;
		}
		else
		{
			void* result;
			result = myMalloc(size);
			memcpy(result, ptr, cur_size);
			myFree(ptr);
			return result;
		}
	}
}

void main()
{
	init();
	int *test_ptr, *another_test_ptr;

	test_ptr = (int*)myMalloc(sizeof(int) * 5);
	another_test_ptr = (int*)myMalloc(sizeof(int) * 1000); //must be error
	test_ptr[1] = 23;
	printf("pointer (test_ptr) - %p, val[1] - %d\n", test_ptr, test_ptr[1]);
	printf("pointer (another_test_ptr, must be error) - %p\n", another_test_ptr);

	test_ptr = (int*)myRealloc(test_ptr, sizeof(int) * 6);
	printf("pointer(test_ptr after myRealloc) - %p, val[1] - %d\n", test_ptr, test_ptr[1]);


	_getch();
	free(memory);
	return;
}






