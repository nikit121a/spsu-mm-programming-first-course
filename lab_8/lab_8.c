#include<stdio.h>

long long dp[11][1000007];
int a[] = { 1, 2, 5, 10, 20, 50, 100, 200 };

int main()
{
	int n, k = 8, i, j;

	scanf_s("%d", &n);
	dp[0][0] = 1;
	for (i = 1; i <= k; i++) {
		for (j = 0; j <= n; j++)
			dp[i][j] = dp[i - 1][j];
		for (j = a[i - 1]; j <= n; j++)
			dp[i][j] += dp[i][j - a[i - 1]];
	}
	printf("%lld", dp[k][n]);
	return 0;
}