#define N 1000000
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>

//we compute the digital root of the numbers
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


void prepareArray(long *numberArray)
{
	numberArray[0] = 0;
	numberArray[1] = 1;
	for (int i = 2; i < 10; i++)
	{
		numberArray[i] = i;
	}
	for (long number = 10; number < N; number++)
	{
		int sumOfMultipliedDigits = 0;
		int sumOfDigits = calculateSumOfDigits(number);

		for (long j = 2; j <=ceil(sqrt(number)); j++)
		{
			if ((number % j == 0) && (sumOfMultipliedDigits < (numberArray[j] + numberArray[number / j])))
			{
				sumOfMultipliedDigits = numberArray[j] + numberArray[number / j];
			}
		}

		//compare digital root of the numbers and the individual factors
		numberArray[number] = sumOfMultipliedDigits > sumOfDigits ? sumOfMultipliedDigits : sumOfDigits;
	}
}

int main()
{
	long *numberArray;
	long sum = 0;
	numberArray =(long *)malloc((N + 1) * sizeof(int)); //allocates memory for an array

	prepareArray(numberArray);
	for (int i = 2; i < N; i++) //calculate our sum
	{
		sum += numberArray[i];
	}
	printf_s("%d", sum);
	free(numberArray); //frees memory
	_getch();
	return 0;
}