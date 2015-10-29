
#include <stdio.h>
#include <conio.h>
#include <math.h>


bool Simple(int n)
{
	if (n % 2 == 0)
	{
		return false;
	}

	for (int i = 3; i <= ceil(sqrt(n)); i += 2)
	{
		if (n % i == 0)
		{
			return false;
		}
	}
	return true;
}

int main(void)
{
	const int N = 31;
	printf_s("Simple numbers of Mersen:\n");
	for (int i = 1; i <= N; i++)
	{
		if (Simple(i))
		{
			printf("%.0f\n", pow(2, i) - 1.0);
		}
	}
	_getch();
	return 0;
}