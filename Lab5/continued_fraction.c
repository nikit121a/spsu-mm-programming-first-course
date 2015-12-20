#include <stdio.h>
#include <math.h>

int main()
{
	int a, b, c, new_a, new_b, new_c, i = 2; 
	float x;
	scanf("%f", &x);
	while(x < 0.00001 || sqrt(x) - floor(sqrt(x)) < 0.00000001)
	{
		printf("Incorrect input, please try again:\n");
		scanf("%f", &x);
	}
	a = floor(sqrt(x));
	new_b = a;
	b = a;
	new_c = c = x - a * a;
	printf("Your fraction is: %d [ | ", a);
	do
	{
		new_a = floor((a + b + .0) / c);
		b = new_a * c - b;
		c = (x - b * b) / c;
		printf("%d | ", new_a);
		i++;
	} while(b != new_b || c != new_c);
	printf("], length of period equals to %d\n", i - 2);
	getchar();
	getchar();
	return 0;
}