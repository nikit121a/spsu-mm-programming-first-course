#include <stdio.h>
#include <stdlib.h>
#include <math.h>
long long power(int t, int k)
{
	long long res = 1;
	while (k)
	{
		if (k & 1)
		{
			res *= t;
		}
		t *= t;
		k >>= 1;
	}
	return res;
}

long long gcd(long long a, long long b)
{
	return (a) ? gcd(b%a, a) : b;
}


int main()
{
	int k = 1;
	for (int i = 2; i <= 31; i++)
	{
		k = 1;
		long long z = power(2, i) - 1;
		for (long long j = 2; j < round(sqrt(z)) ; j++)
		{
			
			if (gcd(j, z) != 1)
			{
				
				k = 0;
			}
		}
		if (k == 1)
		{
			printf("%d\n", z);
		}

	}
			getchar();
}