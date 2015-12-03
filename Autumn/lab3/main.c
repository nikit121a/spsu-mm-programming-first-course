#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#define PI 3.14159265   

void grad(double x, double y, double z)
{
	double A, cosA;
	cosA = acos((pow(y, 2) + pow(z, 2) - pow(x, 2)) / (2 * y * z))* 180.0 / PI;

	double minA, secA;
	int  intA = (int)cosA;
	minA = ((cosA - intA) * 60);
	int intmin = (int)minA;
	secA = ((minA - intmin) * 60);
	int intsec = (int)secA;

	printf("angle :%d° %d' %d'' \n", intA, intmin, intsec);
}

int main()
{
	float a = 0, b = 0, c = 0;
	printf("Enter three numbers.\n");
	scanf("%f%*[' ']%f%*[' ']%f%*[' ']", &a, &b, &c);
	if (a > 0 && b > 0 && c > 0)
	{
		if (a < b + c && b < a + c && c < a + b)
		{
			printf("Triangle exists.\n");
			grad(a, b, c);
			grad(b, c, a);
			grad(c, a, b);
		}
		else
			printf("Triangle is not exists.\n");
	}
	else
	{
		printf("Input Error. Try again.\n");
	};

	return 0;
}