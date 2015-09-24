#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n = -1, check = 0;
	int p[7] = { 2, 5, 10, 20, 50, 100, 200 };

	while (!check)
	{
		printf("Input the amount of money in pennies: ");
		scanf("%d", &n);
		scanf("%*[^\n]");
		if (n < 0)  {
			printf("incorrect input, try again\n");
		}
		else
		{
			check = 1;
		}

	}
	
	int* d = (int)malloc(sizeof(int) * (n + 1));

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
	_getch();
}