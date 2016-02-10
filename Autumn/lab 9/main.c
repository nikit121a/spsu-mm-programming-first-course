#define N 1000000
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>

int main()
{
	long answer = 0;
	int *array = (int *)malloc((N + 1) * sizeof(int));

	array[0] = 0;
	array[1] = 0;
	for (int n = 2; n < N; ++n)
	{
		int k = n % 9;
		array[n] = k ? k : 9;
	}
	for (int i = 2; 2 * i < N; ++i)
		for (int j = 2; i * j < N; ++j)
		{
			if (array[i*j] < array[i] + array[j])
				array[i*j] = array[i] + array[j];
		}

	for (int n = 2; n < N; ++n)
		answer += array[n];
	
	printf_s("%d", answer);
	free(array);
	return 0;
}