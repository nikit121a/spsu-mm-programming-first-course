#define N 1000000
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>


int DigitSum(long a)
{
	int tmp;
	while (a / 10 != 0)
	{
		tmp = a % 10;
		a = a / 10 + tmp;
	}
	return a;
}


long calculation(long *mas)
{
	long sum = 0;
	for (int i = 0; i < 10; i++)
	{
		mas[i] = i;
	}

	for (long n = 10; n < N; n++)
	{
		int mult_digits = 0;
		int sum_digits = DigitSum(n);

		for (long j = 2; j <= ceil(sqrt(n)); j++)
		{
			if ((n % j == 0) && (mult_digits < (mas[j] + mas[n / j])))
			{
				mult_digits = mas[j] + mas[n / j];
			}
		}

		if (mult_digits > sum_digits)
			mas[n] = mult_digits;
		else
			mas[n] = sum_digits;
	}

	for (int i = 2; i < N; i++)
		sum += mas[i];

	return sum;
}

int main()
{
	long *mas;
	mas = (long *)malloc((N + 1) * sizeof(int)); 
	
	printf_s("SMDRS = %d", calculation(mas));
	free(mas); 
	_getch();
	return 0;
}