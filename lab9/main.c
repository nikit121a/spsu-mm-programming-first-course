#include <stdio.h>
#include <stdlib.h>
#include <string.h>





int main()
{
	int f, st, n, inf = 1000000;

	int* min_div = (int*)malloc(sizeof(int) * inf);
	for (int i = 2; i < inf; i++)
	{
		min_div[i] = i;
	}

	for (int i = 2; i < inf; i++)             
	{
		if (min_div[i] == i)
		{
			int j = 1;
			while (j * i < inf)
			{
				min_div[j * i] = min(i, min_div[i * j]);
				j++;
			}
		}
	}

	int** d = (int**)malloc(sizeof(int) * inf);
	for (int i = 0; i < inf; i++)
	{
		d[i] = (int*)malloc(sizeof(int) * 9);
	}	

	for (int i = 1; i < inf; i++)
	{
		for (int j = 0; j <= 8; j++)
		{
			d[i][j] = 0;
		}
	}

	for (int i = 2; i <= inf - 1; i++)
	{
		for (int j = 0; j <= 8; j++)
		{
			d[i][j] = d[i / min_div[i]][j];
		}
		d[i][min_div[i] % 9]++;
	}
	

	long long sum = 0;

	
	for (int i = 2; i <= inf - 1; i++)
	{
		d[i][0] += (d[i][0] + (d[i][3] / 2));
		d[i][3] %= 2;

		d[i][8] += min(d[i][2], d[i][4]);
		if(d[i][4] > d[i][2])
		{
			d[i][4] -= d[i][2];
			d[i][2] = 0;
		}
		else
		{
			d[i][2] -= d[i][4];
			d[i][4] = 0;
		}

		if(d[i][2] >= 3)
		{
			d[i][8] += d[i][2] / 3;
			d[i][2] %= 3;
		}

		if(d[i][2] > 0 && d[i][3] > 0)
		{
			d[i][6]++;
			d[i][3]--;
			d[i][2]--;
		}
		sum += d[i][0] * 9 + d[i][1] * 1 + d[i][2] * 2 +
			d[i][3] * 3 + d[i][4] * 4 + d[i][5] * 5 +
			d[i][6] * 6 + d[i][7] * 7 + d[i][8] * 8;
	}
		

	printf("The answer is %d", sum);
	_getch();
	free(d);
	return 0;
}