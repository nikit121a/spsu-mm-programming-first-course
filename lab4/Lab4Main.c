#include "stdio.h"
#include "stdlib.h"
#include "math.h"   

int prime(long long k)
{
	int l = 0;
	for (int i = 2; i<sqrt(k); i++)
	{
		if(k%i == 0)
		{
			l++;
			break;
		}
	}
	return(l);
}


int main()
{
	int count = 1;
	for (int n = 1; n < 32; n++)
	{
		if((n != 1) && (n % 2 != 0) && (n % 3 != 0))
		{
			long long numMer = pow(2, n) - 1;
			int prm = prime(numMer);
			if (prm == 0)
			{
				printf("%d", count);
				printf(" mersenne number: ");
				printf("%d\n", numMer);
				count++;
			}
		}
		if((n == 2) || (n == 3))
		{
			long long numMer = pow(2, n) - 1;
			printf("%d", count);
			printf(" mersenne number: ");
			printf("%d\n", numMer);
			count++;
		}
	}
	getchar();
	return 0;
}




