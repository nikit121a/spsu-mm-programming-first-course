#include <stdio.h>
#include <math.h>

#define EPS 0.000001

int is_triangle(int a, int b, int c)
{
	return a + b > c && a + c > b && b + c > a;
}

int main()
{
	float a, b, c;
	double alpha, betta, gamma, a_min, b_min, g_min, a_sec, b_sec, g_sec;
	printf("Input three positive numbers:\n");
	scanf("%f %f %f", &a, &b, &c);

	while (a * b * c < EPS || a < EPS || b < EPS || c < EPS)
	{
		printf("Your input is incorrect, try again:\n");
		scanf("%f %f %f", &a, &b, &c);
		scanf("%*[^\n]");
	}

	if(is_triangle(a, b, c))
	{
		alpha = acos((b * b + c * c - a * a) / 2.0 / c / b) * 180.0 / acos(-1.0);
		a_min = (alpha - floor(alpha)) * 60.0;
		a_sec = (a_min - floor(a_min)) * 60.0;

		betta = acos((a * a + c * c - b * b) / 2.0 / c / a) * 180.0 / acos(-1.0);
		b_min = (betta - floor(betta)) * 60.0;
		b_sec = (b_min - floor(b_min)) * 60.0;

		gamma = acos((a * a - c * c + b * b) / 2.0 / a / b) * 180.0 / acos(-1.0);
		g_min = (gamma - floor(gamma)) * 60.0;
		g_sec = (g_min - floor(g_min)) * 60.0;

		printf("This triangle exists.\nIt has angles:\na = %3.0f degrees %2.0f'%2.0f''\nb = %3.0f degrees %2.0f'%2.0f''\nc = %3.0f degrees %2.0f'%2.0f''\n", 
			alpha, a_min, a_sec, betta, b_min, b_sec, gamma, g_min, g_sec);
	} 
	else
	{
		printf("This triangle doesn't exist.\n");
	}

	getchar();
	getchar();

	return 0;
}