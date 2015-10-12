#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define base 19683
#define int long long

int head[base], value[100 * base], next[100 * base], h = 0;
int n = 9, m = 12;



void fill_d(int* p, int cur_p, int cur_next_p, int nn)
{

	if(cur_p * 2 == base - 1) 
	{
		h++;
		next[h] = head[cur_next_p];
		value[h] = *p;
		head[cur_next_p] = h;
		return;
	}

	int q = 1, variable_p = cur_p, count = 0;

	while (count < n)
	{
		if(variable_p % 3 == 0)
		{
			break;
		}
		variable_p /= 3;
		q *= 3;
		count++;
	}

	if(q < base / 3 &&			//1
		(base / 3) % 3 == 0 &&
		(cur_next_p / (q * 3)) % 3 == 0)
	{
		fill_d(p, cur_p + q + q * 3, cur_next_p + q * 3, nn);
	}

	if(q < base / 3 &&			//2
		(variable_p / 3) % 3 == 0 &&
		(cur_next_p / q) % 3 == 0)
	{
		fill_d(p, cur_p + q + q * 3, cur_next_p + q, nn);
	}

	if(q > 1 &&			//3
		(cur_next_p / (q / 3)) % 3 == 0 &&
		(cur_next_p / q) % 3 == 0)
	{
		fill_d(p, cur_p + q, cur_next_p + q + q / 3, nn);
	}

	if(q < base / 3 &&			//4
		(cur_next_p / (q * 3)) % 3 == 0 &&
		(cur_next_p / q) % 3 == 0)
	{
		fill_d(p, cur_p + q, cur_next_p + q * 3 + q, nn);
	}

	if(q < base / 9 &&			//5
		(variable_p / 3) % 3 == 0 &&
		(variable_p / 9) % 3 == 0)
	{
		fill_d(p, cur_p + q + q * 3 + q * 9, cur_next_p, nn);
	}

	if((cur_next_p / q) % 3 == 0)			//6
	{
		fill_d(p, cur_p + q, cur_next_p + 2 * q, nn);
	}

	return;
}

int main()
{

	long long ** a = (long long**)malloc(sizeof(long long) * (m + 1)); //create
	for (int i = 0; i <= m; i++)
	{
		a[i] = (long long*)malloc(sizeof(long long) * base);
	}

	for (int i = 0; i < base; i++) //basic val
	{
		head[i] = -1;
	}

	int q = base / 3;

 	for (int i = 0; i < base; i++)  //fill d
	{
		int cur_next_p = 0, cur_i = i, cur_q = 1, cur_p = 0;
		while (cur_i > 0)
		{
			cur_next_p += ((cur_i % 3) / 2) * cur_q;
			cur_p += ((cur_i % 3) - (cur_i % 3) / 2) * cur_q;
			cur_q *= 3;
			cur_i /= 3;
		}
		fill_d(&i, cur_p, cur_next_p, q);
	}

	for (int i = 0; i <= m; i++)
	{
		for (int j = 0; j < base; j++)
		{
			a[i][j] = 0;
		}
	}

	for (int i = 0; i < base; i++) //fill 1 row
	{
		int cur_h = head[i];
		while (cur_h > -1)
		{
			if(value[cur_h] == 0)
			{
				a[1][i]++;
			}
			cur_h = next[cur_h];
		}
	}

	 
	for (int i = 2; i <= m; i++) //main "for"
	{
		for (int j = 0; j < base; j++)
		{
			int cur_h = head[j];
			while (cur_h > -1)
			{
				a[i][j] += a[i - 1][value[cur_h]];
				cur_h = next[cur_h];
			}
		}
	}

	printf("Answer: %llu\n", a[m][0]);

	_getch();
	free(a);
	return 0;
}