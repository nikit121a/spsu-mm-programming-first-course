#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n, i, j, **result, coins[8] = {1, 2, 5, 10, 20, 50, 100, 200}, len = 8;
	printf("Input natural number of pennies:\n");
	scanf_s("%d", &n);  
	while(n <= 0)
	{
		printf("This is not a natural number, try again:\n");
		scanf_s("%d", &n);  
	}
	n++;
	result = (int**)malloc(sizeof(int*) * len);
	for(i = 0; i < len; i++)
	{
		result[i] = (int*)malloc(sizeof(int) * n);
	}
	for(i = 0; i < n; i++)
	{
		result[0][i] = 1;
	}
	for(i = 0; i < len; i++)
	{
		result[i][0] = 1;
	}
	for(i = 1; i < len; i++)
	{
		for(j = 1; j < n; j++)
		{
			if(j < coins[i])
			{
				result[i][j] = result[i - 1][j];
			} else
			{
				result[i][j] = result[i - 1][j] + result[i][j - coins[i]];
			}
		}
	}
	printf("\nThere are %d ways to give the odd", result[len - 1][--n]);
	getchar();
	getchar();
	for (i = 0; i < len; i++)
	{
		free(result[i]);
	}
	free(result);
	return 0;
}
