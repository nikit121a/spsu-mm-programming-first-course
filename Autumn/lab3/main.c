#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#define PI 3.14159265   

void grad(double x, double y, double z)
{
	double cosA, minA, secA;
	cosA = acos((pow(y, 2) + pow(z, 2) - pow(x, 2)) / (2 * y * z))* 180.0 / PI;
	int g1 = (int)cosA;
	minA = ((cosA - g1) * 60);
	int g = (int)minA;
	secA = ((minA - g) * 60);
	int g2 = (int)secA;

	printf("%d  %d' %d''\n", g1, g, g2);
}

int main()
{
	float a = 0, b = 0, c = 0;
	char s[250];
	printf("ddtlbnt lkbys cnjhjy\n");
	int flag = 0;
	while (flag == 0)
	{
		fgets(s, 80, stdin);
		sscanf(s, "%f%*[' ']%f%*[' ']%f%*[' ']", &a, &b, &c);
	if (a > 0 && b > 0 && c > 0)
	{
		flag = 1;
		if (a < b + c && b < a + c && c < a + b)
		{
			printf("Треугольник существует.\n");
			grad(a, b, c);
			grad(b, c, a);
			grad(c, a, b);
		}
		else
			printf("Треугольник не существует.\n");
	}
	else
	{
		printf("error. again\n");
	};
	};

	return 0;
}