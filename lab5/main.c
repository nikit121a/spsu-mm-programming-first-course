#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void main()
{
	int check = 0;
	int n;

	while (!check)
	{
		printf("Input the number: ");
		scanf("%d", &n);
		scanf("%*[^\n]");
		if (n < 0 || sqrt(n) == floor(sqrt(n))) {
			printf("incorrect input, try again\n");
		}
		else
		{
			check = 1;
		}

	}

	printf("Sequence: ");

	int a_0; //inital int part
	int a;  //new int part 
	int b, b_0, c, c_0; //need for calc new numbers
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

	printf("\nPeriod: %d", ans);

	getch();

	return 0;
}