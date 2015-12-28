#include <stdio.h>
#include <math.h>

int main()
{
	int n;
	int flag = 0;
	printf("Enter the amount of money\n");
	char c[80], c2[80];
	while (flag == 0)
	{
	fgets(c, 80, stdin);
	sscanf(c, "%d", &n);
	
		if (strlen(c) == strlen(itoa(n, c2, 10)) + 1)
		{
			flag = 1;

			int v[8] = { 1, 5, 10, 25, 50, 100, 200 };

			long **d = (long **)malloc(8 * sizeof(long));
			for (int i = 0; i < 8; i++)
			{
				d[i] = (long *)malloc(n * sizeof(long));
			}


			for (int i = 0; i < 8; i++)
				for (int j = 0; j < n + 1; j++)
					d[i][j] = 0;
			d[0][0] = 1;

			for (int i = 0; i < n; i++)
				for (int j = 0; j < 8; j++)
					for (int k = j; k < 8; k++)
						if (i + v[k] <= n)
							d[k][i + v[k]] += d[j][i];

			unsigned long long ans = 0;
			for (int i = 0; i < 8; i++)
				ans += d[i][n];

			if (ans > 1)
			{
				printf("There are ");
				printf("%d", ans);
				printf(" ways \n");
			}
			else
			{
				printf("There is only 1 way \n");
			}
		}
		if (flag == 0) printf("Error, try again \n");
	}

	return 0;
}