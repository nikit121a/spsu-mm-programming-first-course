#include <stdio.h>
#include <tchar.h>
#include <conio.h>

int GCD(int a, int c)
{
	int r, min, max;

	if(a > c)
	{
		max = a;
		min = c;
	}
	else
	{
		max = c;
		min = a;
	}

	r = max % min;
	if(r != 0)
	{
		return GCD(min, r);
	}
	else
	{
		return min;
	}
}

int main()
{
	int a, b, c, max;

	printf_s("Enter three natural numbers:\n");
	scanf_s("%i %i %i", &a, &c, &max);
	while((a <= 0) || (c <= 0) || (max <= 0))
	{
		printf_s("Wrong number\n");
		printf_s("Enter three natural numbers:");
		while(getchar() != '\n')
		{
			continue;
		}
		scanf_s("%i %i %i", &a, &c, &max);
	}

	if(a > max)
	{
		b = max;
		max = a;
		a = b;
	}
	if(c > max)
	{
		b = max;
		max = c;
		c = b;
	}


	if((a * a) + (c * c) == (max * max))
	{
		if(GCD(GCD(a, c), max) == 1)
		{
			printf_s("These numbers are simple Pifagor's Three");
		}
		else
		{
			printf_s("These numbers are Pifagor's Three");
		}

	}
	else
	{
		printf_s("These numbers are not Pifagor's three");
	}
	_getch();
	return 0;
}

