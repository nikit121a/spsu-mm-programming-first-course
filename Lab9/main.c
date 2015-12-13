#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1000000
#define WIDTH 20 //max number of prime dividers
#define DR(x) digital_root(x)

int digital_root(int x)
{
	if(x % 9)
	{
		return x % 9;
	}
	else
	{
		return 9;
	}
}

int **primes()
{
	int i, j, k, **table;
	table = (int**)malloc(sizeof(int*) * N);
	for(i = 0; i < N; i++)
	{
		table[i] = (int*)malloc(sizeof(int) * WIDTH);
		memset(table[i], 0, sizeof(int) * WIDTH);
	}
	for(i = 2; i < N; i++)
	{
		if(table[i][0] == 0)
		{
			for(j = 1; j * i < N; j++)
			{

				k = 0;
				while(table[j * i][k] != 0)
				{
					k++;
				}
				table[j * i][k] = i;
			}
		}
	}
	return table;
}

int MDRS(int *count)
{
	int sum = count[0] * 1 + count[4] * 5 + count[5] * 6 + count[6] * 7 + count[7] * 8 + count[8] * 9;
	while(count[1] != 0 && count[3] != 0)
	{
		sum += 8;
		count[1]--;
		count[3]--;
	}
	if(count[1] / 3 > 0)
	{
		sum += (count[1] / 3) * 8;
		count[1] %= 3;
	}
	if(count[2] / 2 > 0)
	{
		sum += (count[2] / 2) * 9;
		count[2] %= 2;
	}
	while(count[1] != 0 && count[2] != 0)
	{
		sum += 6;
		count[1]--;
		count[2]--;
	}
	sum += count[1] * 2 + count[2] * 3 + count[3] * 4;
	return sum;
}

int main()
{
	int **prime = primes(), i, j, *mdrs, sum = 0, temp, count[9] = {0};
	mdrs = (int*)malloc(sizeof(int) * N);
	for(i = 2; i < 10; i++)
	{
		mdrs[i] = i;
		sum += mdrs[i];
	}
	for(i = 10; i < N; i++)
	{
		temp = i;
		memset(count, 0, sizeof(int) * 9);
		while(temp != 1)
		{
			count[DR(prime[temp][0]) - 1]++;
			temp /= prime[temp][0];
		}
		j = MDRS(count);
		mdrs[i] = max(DR(i), j);
		sum += mdrs[i];
	}
	printf("%d", sum);
	getchar();
	free(mdrs);
	return 0;
}