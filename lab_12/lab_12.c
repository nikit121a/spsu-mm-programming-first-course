#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY 0
#define FULL 1
#define MEMORY_SIZE 100

#pragma pack(push, 1)


typedef struct block_header
{
	size_t size;
	unsigned char type;
	void *next;
}block_header;

#pragma pack(pop)

void* memory;

void init()
{
	memory = malloc(MEMORY_SIZE + sizeof(block_header));
	(*(block_header*)memory).type = EMPTY;
	(*(block_header*)memory).size = MEMORY_SIZE - sizeof(block_header) - 1;
	(*(block_header*)memory).next = (char*)memory + MEMORY_SIZE - 1;
	block_header *pointer = (*(block_header*)memory).next;
	(*pointer).type = FULL;
	(*pointer).next = NULL;
}


void* myMalloc(size_t size)
{
	if (size == 0 || size >= MEMORY_SIZE)
	{
		return NULL;
	}


	block_header *ptr = (block_header*)memory;
 	void *result = NULL;

	//at first, find empty block
	while (ptr != NULL)
	{
		if((*ptr).type == EMPTY && (*ptr).size >= size)
		{
			result = ptr;
			(*ptr).type = FULL;
			if((*ptr).size > size + sizeof(block_header) + 1)
			{
				block_header *next = (block_header*)((char*)(ptr + 1) + size);
				(*next).type = EMPTY;
				(*next).size = (*ptr).size - size - sizeof(block_header);
				(*next).next = (*ptr).next;
				(*ptr).size = size;
				(*ptr).next = next;
			}
			break;

		}

		ptr = (*ptr).next;

	}


	return (char*)result + sizeof(block_header);

}



void myFree(void* ptr)
{
	(char*)ptr -= sizeof(block_header);

	(*(block_header*)ptr).type = EMPTY;
	
	block_header *cur_ptr = (block_header*)ptr;

	while ((*cur_ptr).type != FULL)
	{
		cur_ptr = (*cur_ptr).next;
	}

	(*(block_header*)ptr).next = cur_ptr;
	(*(block_header*)ptr).size = (int)((char*)(*(block_header*)ptr).next - (char*)ptr);

	return;
}

void* myRealloc(void* ptr, size_t size)
{
	(char*)ptr -= sizeof(block_header);

	if (ptr == NULL)
	{
		return myMalloc(size);
	}

	if (size == 0)
	{
		myFree(ptr);
		return NULL;
	}

	size_t cur_size = (*(block_header*)ptr).size;

	if (cur_size > size)
	{
		(*(block_header*)ptr).size = size;
		block_header *next = (block_header*)((char*)((block_header*)ptr + 1) + size);
		(*next).type = EMPTY;
		(*next).next = (*(block_header*)ptr).next;
		(*(block_header*)ptr).next = next;
		(*next).size = (*(block_header*)ptr).size - size - sizeof(block_header);
		return (char*)ptr + sizeof(block_header);
	}

	if (cur_size < size)
	{
		block_header *next = (*(block_header*)ptr).next;
		if ((*next).size > size - sizeof(block_header) && (*next).type == EMPTY)
		{
			(*(block_header*)ptr).size = size;
			block_header *next = (block_header*)((char*)((block_header*)ptr + 1) + size);
			(*next).type = EMPTY;
			(*next).size = (*(block_header*)ptr).size - size - sizeof(block_header);
			(*next).next = (*(block_header*)ptr).next;
			(*(block_header*)ptr).next = next;
			return (char*)ptr + sizeof(block_header);
		}
		else
		{
			void* result;
			result = myMalloc(size);
			(char*)ptr += sizeof(block_header);
			memcpy(result, ptr, cur_size);
			myFree(ptr);
			return result;
		}
	}
}

int main() 
{
	init();
	int *test_ptr, *another_test_ptr;

	test_ptr = (int*)myMalloc(sizeof(int) * 5);
	another_test_ptr = (int*)myMalloc(sizeof(int) * 2); //must be error
	test_ptr[1] = 23;
	printf("pointer (test_ptr) - %p, val[1] - %d\n", test_ptr, test_ptr[1]);
	printf("pointer (another_test_ptr, must be error) - %p\n", another_test_ptr);

	test_ptr = (int*)myRealloc(test_ptr, sizeof(int) * 6);
	printf("pointer (test_ptr after myRealloc) - %p, val[1] - %d\n", test_ptr, test_ptr[1]);


	_getch();
	free(memory);
	return 0;
}