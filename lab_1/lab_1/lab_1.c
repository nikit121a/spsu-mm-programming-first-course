#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SURNAME 7
#define NAME 5
#define PATRONYMIC 9

int main()
{
	long long newcomp, comp = SURNAME * NAME * PATRONYMIC * (-1);
	newcomp = comp + 4294967296;
	int i;
	int head = 0;
	int a[100];
	while (newcomp > 0)
	{
		a[head] = newcomp % 2;
		newcomp = newcomp / 2;
		head++;
	}
	printf("Int32: ");
	for (i = 31; i >= 0; i--)
	{
		printf("%d", a[i]);
	}
	printf("\n");
	int ncomp = SURNAME * NAME * PATRONYMIC * (-1);
	int exponent = 127;
	printf("Float: 0");
	ncomp = abs(ncomp);
	int k = -1;
	for (i = 1; i < ncomp; i <<= 1)
	{
		k++;
	};
	exponent += k;
	for (i = 7; i >= 0; i--)
	{
		printf("%d", abs(((1 << i) & exponent) >> i));
	};
	for (i = k - 1; i >= 0; i--)
	{
		printf("%d", abs(((1 << i) & ncomp) >> i));
	};
	for (i = 22 - k; i >= 0; i--)
	{
		printf("0");
	};
	printf("\n");
	exponent = 1023;
	printf("Double conversion:\n1");
	k = -1;
	for (i = 1; i < ncomp; i <<= 1)
	{
		k++;
	};
	exponent += k;
	for (i = 10; i >= 0; i--)
	{
		printf("%d", abs(((1 << i) & exponent) >> i));
	};
	for (i = k - 1; i >= 0; i--)
	{
		printf("%d", abs(((1 << i) & ncomp) >> i));
	};
	for (i = 51 - k; i >= 0; i--)
	{
		printf("0");
	};
	_getch();
}