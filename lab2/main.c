#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int gcd(int a, int b) 
{
	if(b == 0)
		return a;
	else
		return gcd(b, a % b);
}

int main()
{
	int a = - 1, b = -1, c = - 1, x, y, z, f = 0;
	float af, bf, cf;
	float e = 0.0000001;

	while (!f)
	{
		printf("Input the numbers: ");
		scanf("%f%f%f", &af, &bf, &cf);
		scanf("%*[^\n]");
		if (af <= e || bf <= e || cf <= e ||
			af - floor(af) > e || bf - floor(bf) > e || 
			cf - floor(cf) > e)
		{
			printf("Incorrect input, try again\n");
		}
		else
		{
			a = af;
			b = bf;
			c = cf;
			f = 1;
		}
	}
	z = max(max(a, b), c);
	x = min(min(a, b), c);
	y = a + b + c - x - z;

	if(x * x + y * y == z * z)
	{
		printf("Pythagorean triple\n");
		if((gcd(y, x) == 1) && (gcd(z, y) == 1) && (gcd(z, x) == 1)) {
			printf("Relatively prime\n");
		}
	}
	else
	{
		printf("Not Pythagorean triple\n");
	}

	_getch();
	return 0;
}