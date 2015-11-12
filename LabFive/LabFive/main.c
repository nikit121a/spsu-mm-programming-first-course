
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>


int period_length(int n)
{
	int a_0;							// the integral part of the original root of a number
	int a;								//new integer part 
	int b, c, b_0, c_0;					//auxiliary variables for calculating integers								
	int result = 0;
	a_0 = sqrt(n * 1.0);
	b = b_0 = a_0;
	c = c_0 = n - a_0 * a_0;
	do
	{
		a = (a_0 + b) / c;
		printf_s("%d\n", a);
		b = a * c - b;
		c = (n - b * b) / c;
		result++;
	} while ((b != b_0) || (c != c_0));
	printf_s("Period: %d \n", result);
	return result;
}

int check(int a)

{
	while (sqrt(a) == int(sqrt(a)))
	{
		printf_s("Wrong number\n");
		printf_s("Enter positive number:\n");
		while (getchar() != '\n')
		{
			continue;
		}
		scanf_s("%i", &a);
	}

	while (a <= 0)
	{
		printf_s("Wrong number\n");
		printf_s("Enter positive number:\n");
		while (getchar() != '\n')
		{
			continue;
		}
		scanf_s("%i", &a);
	}
	while (sqrt(a) == int(sqrt(a)))
	{
		printf_s("Wrong number\n");
		printf_s("Enter positive number:\n");
		while (getchar() != '\n')
		{
			continue;
		}
		scanf_s("%i", &a);
	}

	return a;
}



int main()
{
	int n;
	printf_s("Enter the number\n");
	scanf_s("%d", &n);
	n = check(n);
	printf_s("Numbers: \n");
	period_length(n);

	_getch();
	return 0;
}