#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void periodLength(int n)
{
	int a_0, a, b, c, b_0, c_0, result = 0;
	a_0 = sqrt(n * 1.0);
	b = b_0 = a_0;
	c = c_0 = n - a_0 * a_0;
	if(c == 0)
	{
		printf("Period: 0");
		printf("\n");
		printf("The length of the period: 0");
		return;
	}
	else
	{
		printf("Period: ");
		do
		{
			a = (a_0 + b) / c;
			b = a*c - b;
			c = (n - b*b) / c;
			printf("%d", a);
			printf(" ");
			result++;
		} while ((b != b_0) || (c != c_0));
		printf("\n");
		printf("The length of the period: ");
		printf("%d", result);
		return;
	}
}


int main()
{
	int n;
	while (1)
	{
		printf("Enter positive integer number: ");
		scanf("%d", &n);
		scanf("%*[^\n]");
		if(n >= 0)
		{
			printf("%d\n", n);
			break;
		}
		else
		{
			printf("%s\n", "Incorrect input.");
			printf("%s\n", "Please, try again.");
		}
	}
	periodLength(n);
	printf("\n");
	system("pause");
	return 0;
}