#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main()
{
	int n;
	while (1)
	{
		printf("Enter the amount of penny (if the number is not an integer, the program will work with a whole part of the number): ");
		scanf("%d", &n);
		scanf("%*[^\n]");
		if (n >= 0)
		{
			break;
		}
		else
		{
			printf("%s\n", "Incorrect input.");
			printf("%s\n", "Please, try again.");
		}
	}
	int **d = (int*)malloc(8 * sizeof(int));
	int *money = (int*)malloc(8 * sizeof(int));

	for (int i = 0; i < 8; i++)
	{
		d[i] = (int*)malloc(100000 * sizeof(int));
	}

	money[0] = 1;
	money[1] = 2;
	money[2] = 5;
	money[3] = 10;
	money[4] = 20;
	money[5] = 50;
	money[6] = 100;
	money[7] = 200;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 10000; j++)
		{
			d[i][j] = 0;
		}
	}

	d[0][0] = 1;

	for (int i = 0; i < 10000; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			for (int k = j; k < 8; k++)
			{
				if (i + money[k] <= 10000)
				{
					d[k][i + money[k]] = d[k][i + money[k]] + d[j][i];
				}
			}
		}
	}

	unsigned long long answer = 0;
	for (int i = 0; i < 8; i++)
	{
		answer += d[i][n];
	}

	printf("The answer is ");
	printf("%d\n", answer);

	for (int i = 0; i < 8; i++)
	{
		free(d[i]);
	}
	free(money);
	system("pause");
	return 0;
}