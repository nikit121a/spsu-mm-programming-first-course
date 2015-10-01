/* Leonid Voroshilov, 143*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h.>
#include <math.h>
#include <conio.h>

void swap(int *a, int *b)
{
	int  tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

/*Euclidean algorithm*/
int gcd(int a, int b) 
{
	int c;
	while (b) 
	{
		c = a % b;
		a = b;
		b = c;
	}
	return abs(a);
}

int main (void)
{
	int num1, num2, num3; // unsorted numbers
	int x, y, z;          // sorted one (x^2 + y^2 = z^2)
	int n;

	printf("Input 3 numbers:");
	n = scanf("%d %d %d", &num1, &num2, &num3);
	while (n < 3)
	{
		printf("\nIncorrect representation format.\nInput 3 numbers:");
		scanf("%*[^\n]");
		scanf("%*c");
		n = scanf("%d %d %d", &num1, &num2, &num3);
	}
	/*searching for maximum number*/
	if (num1 > num2)
		swap(&num1, &num2);
	if(num2 > num3)
		swap(&num2, &num3);

	x = num1, y = num2,	z = num3;
	if(x * x + y * y == z * z)
	{
		printf("\n This is the Pythagorean numbers ");

		if (gcd(gcd(x, y), z) == 1)
			printf("and they are co-prime\n");
		else
			printf("but they are not co-prime\n");

	}
	else
		printf("\n This is not the Pythagorean numbers");
	_getch();
	printf("Press any key to exit");
	return 0;
}
