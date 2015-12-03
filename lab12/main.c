#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEMORY 100

typedef struct {
	int index;
	int size; 
}memory_block;


 
void* memory;
memory_block next_empty[MAX_MEMORY];
int pointer_list_head = 0, memory_left = MAX_MEMORY, next_empty_head = 0;

void init()
{
	memory = malloc(MAX_MEMORY);
	next_empty[next_empty_head].index = 0;
	next_empty[next_empty_head].size = MAX_MEMORY;
}

void* myMalloc(size_t size)
{

	int cur_head = 0, result = -1;

	while (cur_head <= next_empty_head)
	{

		if(size + 4 <= next_empty[cur_head].size )
		{
			memory_left -= size + 4;
			result = next_empty[cur_head].index + 4;
			memcpy((char*)memory + next_empty[cur_head].index, &size, 4);
			next_empty[cur_head].size -= (size + 4);
			next_empty[cur_head].index += size + 4;
			cur_head = next_empty_head;
		}
		cur_head++;
	}
	if(result == -1 || size == 0)
	{
		return 0;
	}
	else
	{
		return (char*)memory + result;
	}
	
}


void myFree(void* ptr)
{
	size_t size;
	memcpy(&size, (int*)ptr - 1, 4);
	next_empty_head++;
	next_empty[next_empty_head].index = (int*)ptr - 1 - (char*)memory;
	next_empty[next_empty_head].size = size + 4;

}

void* myRealloc(void* ptr, size_t size)
{
	size_t cur_size;
	memcpy(&cur_size, (int*)ptr - 1, 4);
	if(size > cur_size)
	{
		void* cur_ptr;
		cur_ptr = myMalloc(size);
		memcpy(cur_ptr, ptr, size);
		myFree(ptr);
		return cur_ptr;
	}
	else
	{
		memcpy((int*)ptr - 1, &cur_size, 4);
		return ptr;
	}
}

void main()
{
	init();
	int* test_ptr, another_test_ptr;

	test_ptr = (int*)myMalloc(sizeof(int) * 5);
	another_test_ptr = (int*)myMalloc(sizeof(int) * 1000); //must be error
	test_ptr[1] = 23;
	printf("pointer (test_ptr) - %p, val[1] - %d\n", test_ptr, test_ptr[1]);
	printf("pointer (another_test_ptr, must be error) - %p\n", another_test_ptr);

	test_ptr = (int*)myRealloc(test_ptr, sizeof(int) * 6);
	printf("pointer(test_ptr after myRealloc) - %p, val[1] - %d\n", test_ptr, test_ptr[1]);


	_getch();
	free(memory);
	return 0;
}






