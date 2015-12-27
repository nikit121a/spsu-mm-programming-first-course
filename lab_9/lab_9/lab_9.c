#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>


#define N 1000000

int main()
{
	int *d;
	d = (int*)malloc((N + 1) * sizeof(int));

	for (int i = 0; i < 10; i++)
	{
		d[i] = i;
	}


	for (int i = 10; i < N; i++)
	{
		int cur_ans = 0;

		for (long j = 2; j <= ceil(sqrt(i)); j++)
		{
			if ((i % j == 0) && (cur_ans < (d[j] + d[i / j])))
			{
				cur_ans = d[j] + d[i / j];
			}
		}
		if (cur_ans >(i % 9))
		{
			d[i] = cur_ans;
		}
		else
		{
			d[i] = i % 9;
		}
	}

	int sum = 0;

	for (int i = 2; i < N; i++)
	{
		sum += d[i];
	}


	printf_s("The anwser: %d\n", sum);
	free(d);
	_getch();
	return 0;
}
