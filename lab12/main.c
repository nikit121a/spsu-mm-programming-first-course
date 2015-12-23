#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MEMORY_SIZE 4040


void *memory;


void init()
{
	memory = malloc(MEMORY_SIZE);
	memset(memory, 0, MEMORY_SIZE);
}

void *myMalloc(int size)
{
	if (*((int*)memory) == 0)
	{
		*((int*)memory) = size;
		return (void*)((char*)memory + 4);
	}
	else
	{
		char* current = memory;
		while (1)
		{
			int blockSize = *((int*)current);
			if (blockSize == 0)
			{
				if (current - (char*)memory + size >= MEMORY_SIZE)
					return NULL;

				int isGoodBlock = 1;

				for (int i = 4; i < size + 4; i += 4)
				{
					if (*(int*)(current + i) != 0)
					{
						isGoodBlock = 0;
						break;
					}
				}
				if (isGoodBlock)
				{
					*((int *)current) = size;
					return (void*)(current + 4);
				}
			}
			current += blockSize + 4;
		}
	}
	return NULL;
}


void myFree(void *data)
{
	int size = *(int*)((char*)data - 4);
	*(int*)((char*)data - 4) = 0;
	for (int i = 0; i < size; i++)
	{
		*((char*)data + i) = 0;
	}
	*(int*)((char*)data - 4) = 0;
}


void *myRealloc(void *data, int size)
{
	int dataSize = *((int*)((char*)data - 4));

	int flag = 1;

	for (int i = 0; i < dataSize - size; i += 4)
	{
		if (*(int*)((char*)data + size + i) != 0)
		{
			flag = 0;
			break;
		}
	}
	if (flag)
	{
		*((int*)((char*)data - 4)) = size;
		return data;
	}

	void* newData = myMalloc(size);
	memcpy(newData, data, dataSize);
	myFree(data);
	return newData;
}


int main()
{
	init();
	int *array = (int *)myMalloc(50 * sizeof(int));
	for (int i = 0; i < 50; ++i)
		array[i] = i;

	array = (int*)myRealloc(array, 70 * sizeof(int));

	for (int i = 50; i < 70; ++i)
		array[i] = 21;

	myFree(array);

	return 0;
}