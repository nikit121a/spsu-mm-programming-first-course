#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void main()
{
	int f = 0;
	int n;
	while (!f)
	{
		printf("Input the number: ");
		scanf("%d", &n);
		scanf("%*[^\n]");
		if (n < 0 || sqrt(n) == floor(sqrt(n))) {
			printf("incorrect input\n");
		}
		else
		{
			f = 1;
		}

	}
	printf("Sequence: ");
	int a_0;
	int a;  
	int b, b_0, c, c_0; 
	a_0 = sqrt(n);
	b = a_0 = b_0 = a_0;
	c = c_0 = n - a_0 * a_0;
	int ans = 0;
	do
	{
		a = (a_0 + b) / c;
		printf("%d ", a);
		b = a * c - b;
		c = (n - b * b) / c;
		ans++;
	} while
		(b != b_0 || c != c_0);
	printf("\n");
	printf("Period: %d", ans);
	_getch();
	return 0;
}