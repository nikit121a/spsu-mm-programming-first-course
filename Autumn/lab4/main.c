#include <stdio.h>
#include <math.h>

void main( )
{
	printf("Mersenne primes: 3");
	for (int p = 3; p < 32; p++)
	{
		long long M = pow(2, p) - 1;
		long long L = 4;
		for (int k = 1; k < p - 1; k++)
			L = (L * L - 2) % M; // L(p-1) mod M
				if (L == 0)
				{ 
					printf("%d  ", M);
				}
	}
}
