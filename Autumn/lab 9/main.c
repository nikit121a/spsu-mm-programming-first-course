#define N 1000000
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>

int mdrs(int n)
{
	int r;
	while (n / 10 != 0)
	{
		r = n % 10;
		n = n / 10 + r;
	}
	return n;
}

int main()
{
	int answer = 0;
	int *array = (int *)malloc((N + 1) * sizeof(int));

	for (int i = 0; i < 10; i++)
		array[i] = i;

	for (int i = 10; i < N; i++)
	{
		int sum = 0;


		for (long j = 2; j <= sqrt(i); j++)
		{
			if ((i % j == 0) && (sum < (array[j] + array[i / j])))
			{
				sum = array[j] + array[i / j];
			}
		}


		if (sum > mdrs(i))
			array[i] = sum;
		else
			array[i] = mdrs(i);

		for (int i = 2; i < N; i++)
			sum += array[i];
	}

	printf_s("%d", answer);
	free(array);
	return 0;
}