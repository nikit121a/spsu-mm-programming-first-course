#include <stdio.h>

int main()
{
	int v[8] = {1, 5, 10, 25, 50, 100, 200};	

	long **d = (long **)malloc(8 * sizeof(long));
	for (int i = 0; i < 8; i++)
	{
		d[i] = (long *)malloc(30000 * sizeof(long));
	}


	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 30001; j++)
			d[i][j] = 0;
	d[0][0] = 1;

	for (int i = 0; i < 30000; i++)
		for (int j = 0; j < 8; j++)
			for (int k = j; k < 8; k++)
				if (i + v[k] <= 30000)
					d[k][i + v[k]] += d[j][i];


	int n;
	scanf("%d", &n);

		unsigned long long ans = 0;
		for (int i = 0; i < 8; i++)
			ans += d[i][n];

		if (ans > 1)
		{ 
			printf("There are ");
			printf("%d", ans);
			printf(" ways");
		}
		else
		{ 
			printf("There is only 1 way");
		}

	return 0;
}