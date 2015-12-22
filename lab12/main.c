#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MEMORY_SIZE 404


void *memoryStart;
void *buffer;
int *memoryInfo;


void init()
{
	memoryStart = malloc(MEMORY_SIZE);
	buffer = malloc(MEMORY_SIZE);
	memoryInfo = malloc(sizeof(int) * MEMORY_SIZE);

	for (int i = 0; i < MEMORY_SIZE; ++i)
		memoryInfo[i] = 0;

}

void *myMalloc(int size)
{
	int indexOfLastZero = -1;
	for (int i = 0; i < MEMORY_SIZE; ++i)
	{
		if (indexOfLastZero != -1 && (i - indexOfLastZero) == size)
		{
			for (int j = 0; j < size; ++j)
				memoryInfo[j + i - size] = 1;
			memoryInfo[i - size] = size;
			return (void*)((char*)memoryStart + i - size);
		}
		if (memoryInfo[i] == 0)
		{
			if (indexOfLastZero == -1)
				indexOfLastZero = i;
		}
		else
		{
			indexOfLastZero = -1;
		}
	}

	return NULL;
}

void myFree(void *data)
{
	int index = (int)((char*)data - memoryStart);
	int size = memoryInfo[index];
	for (int i = 0; i < size; ++i)
		memoryInfo[index + i] = 0;
}

void *myRealloc(void *data, int size)
{
	memcpy(buffer, data, size);
	myFree(data);

	int *startPointer = myMalloc(size);
	if (startPointer == NULL)
		return NULL;

	memcpy(startPointer, buffer, size);
	return startPointer;


}

int main()
{
	init();
	int *array = (int *)myMalloc(50 * sizeof(int));
	for (int i = 0; i < 50; ++i)
		array[i] = i + 1;

	array = (int *)myRealloc(array, 100 * sizeof(int));
	for (int i = 50; i < 100; ++i)
		array[i] = 1234;

	myFree(array);

	return 0;
}