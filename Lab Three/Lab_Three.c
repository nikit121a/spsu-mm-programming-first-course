


#define M_PI       3.14159265358979323846
#include <stdio.h>
#include <math.h>
#include <conio.h>

void check(int a, int b, int c)
{
	while ((a <= 0) || (c <= 0) || (b <= 0))
	{
		printf_s("Wrong number\n");
		printf_s("Enter three positive numbers:\n");
		while (getchar() != '\n')
		{
			continue;
		}
		scanf_s("%i %i %i", &a, &c, &b);
	}
}

double angle(double a, double b, double c)
{
	double s, p, rad1, rad2, rad3, grad1, grad2, grad3;
	p = (a + b + c) / 2.0;
	s = sqrt(p * (p - a) * (p - b) * (p - c));
	rad1 = asin(2.0 * s / (a * b));
	rad2 = asin(2.0 * s / (a * c));
	rad3 = asin(2.0 * s / (c * b));
	grad1 = rad1 * 180.0 / M_PI;
	grad2 = rad2 * 180.0 / M_PI;
	grad3 = rad3 * 180.0 / M_PI;
	double min1 = (grad1 - (int)grad1) * 60;
	double min2 = (grad2 - (int)grad2) * 60;
	double min3 = (grad3 - (int)grad3) * 60;
	int sec1 = (min1 - (int)min1) * 60;
	int sec2 = (min2 - (int)min2) * 60;
	int sec3 = (min3 - (int)min3) * 60;
	printf_s("Value of the first angle:%.0f grad, %.0f min, %i sec.\n", floor(grad1), floor(min1), sec1);
	printf_s("Value of the second angle:%.0f grad, %.0f min, %i sec.\n", floor(grad2), floor(min2), sec2);
	printf_s("Value of the third angle:%.0f grad, %.0f min, %i sec.", floor(grad3), floor(min3), sec3);
	return 0;
}

int main(void)
{
	int a, b, c;
	printf_s("Enter three poitive numbers:\n");
	scanf_s("%d %d %d", &a, &b, &c);
	check(a, b, c);
	if ((a + b > c) && (a + c > b) && (b + c > a))
	{
		printf_s("There is a non-degenerate triangle\n");
		angle(a, b, c);
	}

	else
	{
		printf_s("Non-degenerate triangle does not exist\n");
	}
	_getch();
	return 0;
}