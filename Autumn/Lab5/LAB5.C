/* Leonid Voroshilov, 143*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int period_length(int n) 
{
	int a_0, a, b, c, b_0, c_0, result = 0;
	a_0 = sqrt(n * 1.0);
	b = b_0 = a_0;
	c = c_0 = n - a_0 * a_0;
	if (c == 0)
		return 0;
	do 
	{
		a = (a_0 + b) / c;
		b = a * c - b;
		c = (n - b * b) / c;
		result++;
		printf("%i ", a);
	} 
	while ((b != b_0) || (c != c_0));

	return result;
}

int main() 
{
	int n, n1;

	printf("Input n(your n will be round down): ");
	n1 = scanf("%d", &n);
	while (n1 < 1 || n < 0)
	{
		printf("\nIncorrect representation format\n");
		scanf("%*[^\n]");
		scanf("%*c");
		n1 = scanf("%d", &n);
	}
	printf("\nPeriod lenght is %i \nPress any key...", period_length(n));
	_getch();
	return 0;
}