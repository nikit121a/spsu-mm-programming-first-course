#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int *primes;

int MDRS(int x)
{
	if (x % 9 == 0)
	{
		return 9;
	}
	else
	{
		return x % 9;
	}
}


int main()
{
	int t1 = time(NULL);
	int N = 1000000;
	int *array = (int)malloc(sizeof(int) * (N + 1));
	unsigned long long answer = 44;

	for (int i = 1; i < 10; i++)
	{
		array[i] = i;
	}
	for (int i = 10; i < N; i++)
	{
		int curDigitRoot = 0;
		for (long j = 2; j <= sqrt(i); j++)
		{
			if (curDigitRoot < (array[j] + array[i / j]) && i % j == 0)
			{
				curDigitRoot = array[j] + array[i / j];
			}
		}
		
		if (curDigitRoot > MDRS(i))
		{
			answer += curDigitRoot;
			array[i] = curDigitRoot;
		}
		else
		{
			answer += MDRS(i);
			array[i] = MDRS(i);
		}
	}


	printf("The answer is ");
	printf("%llu\n", answer);
	free(array);
	int t3 = time(NULL);
	printf("Programm running time ");
	printf("%d\n", t3 - t1); // Programm running time
	system("pause");
	return 0;
}