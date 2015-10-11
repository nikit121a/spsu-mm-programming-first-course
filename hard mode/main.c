#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#pragma comment(linker, "/STACK:1000000000")

#define osn 19683
#define int long long

int head[osn], value[100 * osn], next[100 * osn], h = 0;
int n = 9, m = 12, ed = osn;



int tmt(int* p, int cur_p, int cur_np, int nn)
{

	if(cur_p * 2 == osn - 1)
	{
		h++;
		next[h] = head[cur_np];
		value[h] = *p;
		head[cur_np] = h;
		return 0;
	}

	int q = 1, chp = cur_p, count = 0;

	while (count < n)
	{
		if(chp % 3 == 0)
		{
			break;
		}
		chp /= 3;
		q *= 3;
		count++;
	}

	if(q < osn / 3 &&			//1
		(chp / 3) % 3 == 0 &&
		(cur_np / (q * 3)) % 3 == 0)
	{
		tmt(p, cur_p + q + q * 3, cur_np + q * 3, nn);
	}

	if(q < osn / 3 &&			//2
		(chp / 3) % 3 == 0 &&
		(cur_np / q) % 3 == 0)
	{
		tmt(p, cur_p + q + q * 3, cur_np + q, nn);
	}

	if(q > 1 &&			//3
		(cur_np / (q / 3)) % 3 == 0 &&
		(cur_np / q) % 3 == 0)
	{
		tmt(p, cur_p + q, cur_np + q + q / 3, nn);
	}

	if(q < osn / 3 &&			//4
		(cur_np / (q * 3)) % 3 == 0 &&
		(cur_np / q) % 3 == 0)
	{
		tmt(p, cur_p + q, cur_np + q * 3 + q, nn);
	}

	if(q < osn / 9 &&			//5
		(chp / 3) % 3 == 0 &&
		(chp / 9) % 3 == 0)
	{
		tmt(p, cur_p + q + q * 3 + q * 9, cur_np, nn);
	}

	if((cur_np / q) % 3 == 0)			//6
	{
		tmt(p, cur_p + q, cur_np + 2 * q, nn);
	}

	return 0;
}

int main()
{

	long long ** a = (long long**)malloc(sizeof(long long) * (m + 1));
	for (int i = 0; i <= m; i++)
	{
		a[i] = (long long*)malloc(sizeof(long long) * osn);
	}

	for (int i = 0; i < osn; i++)
	{
		head[i] = -1;
	}

	int q = osn / 3;

 	for (int i = 0; i < ed; i++)
	{
		int cur_np = 0, cur_i = i, g = 1, cur_p = 0;
		while (cur_i > 0)
		{
			cur_np += ((cur_i % 3) / 2) * g;
			cur_p += ((cur_i % 3) - (cur_i % 3) / 2) * g;
			g *= 3;
			cur_i /= 3;
		}
		tmt(&i, cur_p, cur_np, q);
	}

	for (int i = 0; i <= m; i++)
	{
		for (int j = 0; j < osn; j++)
		{
			a[i][j] = 0;
		}
	}

	for (int i = 0; i < osn; i++)
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


	for (int i = 2; i <= m; i++)
	{
		for (int j = 0; j < osn; j++)
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
	return 0;
}