#include <stdio.h>
#include <math.h>

int is_prime_number(int a)
{
	for (int i = 2; i <= sqrt(a); i++)
		if (a % i == 0)
			return 0;
	return 1;
}

int main()
{
	printf("Prime Mersenne numbers from 1 to 2^31:\n");
	for (int i = 2; i <= 31; i++)
	{
		int mersenne_number = (1 << i) - 1;
		if (is_prime_number(mersenne_number))
			printf("%d\n", mersenne_number);
	}
	printf("Please press eny key to exit\n");
	_getch();

	return 0;
}
