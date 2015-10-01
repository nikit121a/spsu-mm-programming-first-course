#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("Numbers: 3");
	long long q = 4;
	for (int i = 3; i <= 31; i++)
	{
		q *= 2;
		long long sn0 = 4, sn;
		for (int j = 1; j <= i - 2; j++)
		{
			sn0 = (sn0 * sn0 - 2) % (q - 1);
		}
		if (sn0 == 0)
		{
			printf(", %d", q - 1);
		}
	}
	_getch();
}