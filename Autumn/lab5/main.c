#include <stdio.h>
#include <math.h> 

void period_length(int n)
{
	int a_0, a, b, c, b_0, c_0, result = 0;
	a_0 = sqrt(n * 1.0);
	b = b_0 = a_0;
	c = c_0 = n - a_0 * a_0;
	printf_s("Numbers: \n");
	do
	{
		a = (a_0 + b) / c;
		printf("%d\n", a);
		b = a * c - b;
		c = (n - b * b) / c;
		result++;
	} while ((b != b_0) || (c != c_0));
	printf("Period: %d \n", result);
}

int main()
{
	int n, period = 0;
	printf("Enter numbers.\n");
	int flag = 0;
	char c[80], c2[80];

	while (flag == 0)
	{
		fgets(c, 80, stdin);
		sscanf(c, "%d", &n);
		if (strlen(c) == strlen(itoa(n, c2, 10)) + 1)
		{
			flag = 1;
			period_length(n);
		}
		else
		{
			printf("Wrong input. Try again.\n");
		}
	}
	return 0;
}