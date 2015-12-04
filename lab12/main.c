#include <windows.h>
#include <WinBase.h>
#include <stdlib.h>

void* myMalloc(size_t size)
{
	return (void *)VirtualAlloc(NULL, size, MEM_COMMIT, PAGE_READWRITE);
}

void* myRealloc(int* Array, size_t newSize)
{
	return (void *)VirtualAlloc(Array, newSize, MEM_COMMIT, PAGE_READWRITE);
}

void* myFree(int* Array)
{
	VirtualFree(Array, 0, MEM_RELEASE);
}

int check(x)
{
	while (1)
	{
		printf("Enter the amount of numbers: ");
		scanf("%d", &x);
		scanf("%*[^\n]");
		if (x >= 0)
		{
			break;
		}
		else
		{
			printf("%s\n", "Incorrect input.");
			printf("%s\n", "Please, try again.");
		}
	}
	return x;
}

int main()
{
	int amount, counter;

	amount = check(&amount);
	
	int *Array = (int*)myMalloc(sizeof(int) * amount);
	
	if (amount != 0)
	{
		printf("Enter numbers: ");
		for (int i = 0; i < amount; i++)
		{
			scanf("%d", &Array[i]);
		}
	}
	else
	{
		printf("Enter numbers: -\n");
	}


	counter = check(&counter);

	myRealloc(Array, counter * sizeof(int));

	if (counter != 0)
	{
		printf("Enter numbers: ");
		for (int i = 0; i < counter; i++)
		{
			int temp;
			scanf("%d", &temp);
			Array[i + amount] = temp;
		}
	}
	else
	{
		printf("Enter numbers :-\n");
	}

	myFree(Array);

	system("pause");
	return 0;
}