/* Leonid Voroshilov, 143*/
#define _CRT_SECURE_NO_WARNINGS
#define PI 3.1415926

#include <stdio.h>
#include <math.h>


/* Return the angle opposite side a (in degree)*/
double get_angle(double a, double b, double c)
{
	double cos_a = (b * b + c * c - a * a) / (2 * c * b);
	return 180 / PI * acos(cos_a);
}

void print_angle(double angle)
{
	int degr, min, sec;
	degr = floor(angle);
	angle = (angle - degr) * 60;
	min = floor(angle);
	angle = (angle - min) * 60;
	sec = floor(angle);

	printf("%-3i degr %-2i min  %-2i sec\n", degr, min, sec);
}
int main(void)
{
	double a, b, c; //sides
	int n = 0;
	printf("Input sides of a triangle:");
	n = scanf("%lf %lf  %lf", &a, &b, &c);
	while(n < 3)
	{
		printf("\nIncorrect representation format.\nInput sides of a triangle:");
		scanf("%*[^\n]");
		scanf("%*c");
		n = scanf("%lf %lf  %lf", &a, &b, &c);
	}
		if (a <= 0 || b <= 0 || c <= 0)
		printf("\nSides of tiangle must be greater than zero!!");
	else
	{
		if((a < b + c) && (c < a + b) && (b < a + c))
		{
			printf("\nThere is a triangle with that sides and the angles are:\n");
			print_angle(get_angle(a, b, c));
			print_angle(get_angle(b, a, c));
			print_angle(get_angle(c, b, a));
		}
		else
			printf("\nThere is no triangle with that sides");
	}
	printf("\n Press any key to continue...");
	_getch();
	return 0;
}
