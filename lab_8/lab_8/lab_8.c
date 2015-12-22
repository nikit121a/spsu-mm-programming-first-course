#include <stdio.h>
#include <stdlib.h>

int main()
{

	int p[7] = { 2, 5, 10, 20, 50, 100, 200 };
	int n, k = 8, i, j;
	int f = 0;
	while (!f)
	{
		printf("Enter the number: ");
		scanf("%d", &n);
		scanf("%*[^\n]");
		if (n < 0)
		{
			printf("Incorrect input\n");
		}
		else
		{
			f = 1;
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
	printf("The number of ways to compose %d pennies:", n);
	printf("%d\n", d[n]);
	free(d);
	_getch();
}