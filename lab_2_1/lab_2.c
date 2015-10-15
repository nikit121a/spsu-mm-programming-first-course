#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int gcd(int a, int b)
{
	return (a) ? gcd(b%a, a) : b;
}

int main()
{
	float x, y, z;
	int a, b, c;
	int f = 0;
	float g = 0.000001;
	while (!f)
	{
		printf("Enter the numbers\n");
		scanf_s("%f%f%f", &x, &y, &z);
		if (x <= 0 || y <= 0 || z <= 0 || x - floor(x) > g || y - floor(y) > g || z - floor(z) > g)
		{
			printf("Incorrect input\n");

		}
		else
		{
			a = x;
			b = y;
			c = z;
			f = 1;
		}
	}
		if ((a*a + b*b == c*c) || (b*b + c*c == a*a) || (a*a + c*c == b*b))
		{
			if (gcd(gcd(a, b), c) == 1)
			{
				printf("Primitive pythagorean triple\n");
			}
			else
			{
				printf("Nonprimitive pythagorean triple\n");
			}
		}
		else
		{
			printf("Not a pythagorean triple\n");
		}
	getchar();
	return 0;
}
	

