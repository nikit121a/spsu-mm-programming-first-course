#include <stdio.h>
#include <stdlib.h>
#include <math.h>





int main()
{
	int n;
	while (1)
	{
		printf("Enter the amount of penny: ");
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
	int money[8] = { 1, 2, 5, 10, 20, 50, 100, 200 };
	unsigned long long d[8][10000];
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

	system("pause");

	return 0;
}