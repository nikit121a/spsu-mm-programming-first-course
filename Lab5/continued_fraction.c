#include <stdio.h>
#include <math.h>
#define max 100

int main()
{
	int a[max], b[max], c[max], i = 2; 
	float x;
	scanf("%f", &x);
	while(x < 0.00001 || sqrt(x) - floor(sqrt(x)) < 0.00000001)
	{
		printf("Incorrect input, please try again:\n");
		scanf("%f", &x);
	}
	a[0] = floor(sqrt(x));
	b[0] = 0;
	b[1] = a[0];
	c[0] = 1;
	c[1] = x - a[0] * a[0];
	printf("Your fraction is: %d [ | ", a[0]);
	do
	{
		a[i - 1] = floor((a[0] + b[i - 1] + .0) / c[i - 1]);
		b[i] = a[i - 1] * c[i - 1] - b[i - 1];
		c[i] = (x - b[i] * b[i]) / c[i - 1];
		printf("%d | ", a[i - 1]);
		i++;
	} while(b[i - 1] != b[1] || c[i - 1] != c[1]);
	printf("], length of period equals to %d\n", i - 2);
	getchar();
	getchar();
	return 0;
}