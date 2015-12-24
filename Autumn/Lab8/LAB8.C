/* Leonid Voroshilov, 143*/
#define _CRT_SECURE_NO_WARNINGS


#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int main(void)
{
	int N, i, j, k;
	int val[] = { 1, 2, 5, 10, 20, 50, 100, 200};
	

	printf("Amount(will be round down): ");
	i = scanf("%d", &N);
	while (i != 1 || N <= 0)
	{
		printf("\nIncorrect representation format.\nInput 1 number:");
		scanf("%*[^\n]");
		scanf("%*c");
		i = scanf("%d", &N);
	}

	int **d = (int**)malloc(8 * sizeof(int));

	for (int i = 0; i < 8; i++)
	{
		d[i] = (int*)malloc((N + 1) * sizeof(int));
	}

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j <= N; j++)
		{
			d[i][j] = 0;
		}
	}

	d[0][0] = 1;

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < 8; j++)
		{
			for (k = j; k < 8; k++)
			{
				if (i + val[k] <= N)
				{
					d[k][i + val[k]] = d[k][i + val[k]] + d[j][i];
				}
			}
		}
	}

	unsigned long long res = 0;
	for (int i = 0; i < 8; i++)
		res += d[i][N];


	printf("%lli\n", res);

	for (int i = 0; i < 8; i++)
		free(d[i]);


	system("pause");
	return 0;
}
