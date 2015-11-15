#define N 999999
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>

int calculateSumOfDigits(long a)
{
	int root;
	long number = a;
	while (number / 10 != 0)
	{
		root = number % 10;
		number = number / 10 + root;
	}
	return number;
}

int calculateDigitalRoot(long start, long end, long number, long *numberArray)
{
	for (long j = start; j > end; j--)
	{
		if (number % j == 0)
		{
			return numberArray[j] + numberArray[number / j];
		}
	}
	return 0;
}

void prepareArray(long *numberArray)
{
	numberArray[0] = 0;
	numberArray[1] = 0;
	for (int i = 2; i < 10; i++)
	{
		numberArray[i] = i;
	}
	for (long number = 10; number <= N; number++)
	{
		int sumOfMultipliedDigits = 0;
		sumOfMultipliedDigits += calculateDigitalRoot(9, 1, number, numberArray);

		if (sumOfMultipliedDigits == 0) {
			sumOfMultipliedDigits += calculateDigitalRoot(ceil(sqrt(number)), 9, number, numberArray);
		}

		int sumOfDigits = calculateSumOfDigits(number);

		numberArray[number] = sumOfMultipliedDigits > sumOfDigits ? sumOfMultipliedDigits : sumOfDigits;
	}
}

int main()
{
	long *numberArray;
	long sum = 0;
	numberArray = malloc((N + 1) * sizeof(int));

	prepareArray(numberArray);
	for (int i = 2; i <= N; i++)
	{
		sum += numberArray[i];
	}
	printf_s("%d", sum);
	free(numberArray);
	_getch();
	return 0;
}