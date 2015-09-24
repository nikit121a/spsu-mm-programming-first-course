#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n;
	//long long d[100000];
	int p[7] = { 2, 5, 10, 20, 50, 100, 200 };

	scanf("%d", &n);
	int* d = (int)malloc(sizeof(long long) * n);

	for (int i = 0; i <= n; i++)
	{
		d[i] = 1;
	}

	for (int i = 0; i < 7; i++)
	{
		for (int z = n; z >= 1; z--)
		{
			int j = z;
			while (j >= p[i])
			{
				d[z] += d[j - p[i]];
				j -= p[i];
			}
		}
	}

	printf("%d", d[n]);
	free(d);
}