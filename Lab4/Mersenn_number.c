#include <stdio.h>
#define HIGH 32 // Greatest number - 2^HIGH-1 

long long primality(unsigned int x) // Lucas-Lehmer test for Mersenne numbers
{
	long long s = 4, i, num = (1 << x) - 1;
	for (i = 0; i < x - 2; i++)
	{
		s = (s * s - 2) % num;
	}
	return s;
}

int main()
{
	unsigned int i;
	printf("All prime Mersenn numbers under 2^32 using format 'index - number':\n2 - 3\n");
	for (i = 3; i < HIGH; i++)
	{
		if(!primality(i))
		{
			printf("%d - %d\n", i, (1 << i) - 1);
		}
	}

	getchar();
	getchar();

	return 0;
}