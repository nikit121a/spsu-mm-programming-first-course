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
	scanf_s("%f%f%f", &x, &y, &z);
	int a = x;
	int b = y;
	int c = z;
	float g = 0.000001;
	if (x <= 0 || y <= 0 || z <= 0 || x - floor(x) > g || y - floor(y) > g || z - floor(z) > g)
	{
		printf("Incorrect input\n");
		getchar();
		exit(0);
	}
	else
	{
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
}
