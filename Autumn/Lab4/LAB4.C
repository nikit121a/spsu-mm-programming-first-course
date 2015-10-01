#include <stdio.h>
#include <conio.h>
#include <math.h>

int simple_prime(int num)
{
	int i;
	for (i = 2; i < floor(sqrt(num)) + 1; i++)
		if (num % i == 0)
			return 0;
	return 1;
}

/*Lucas–Lehmer primality test*/
int  lucas_lehmer(int num)
{
	/* 2^q - 1 is prime if only q is prime and Lucas–Lehmer residue is zero.*/
	long long target 
		= pow(2, num) - 1, test = 4; 
	int i;
	if (simple_prime(num) == 0)
		return 0;
	for (i = 1; i < num - 1; i++)
		test = (test * test - 2) % target;

	if (test == 0)
		return 1;
	
	return 0;
}
void main(void)
{
	printf("Mersenne prime numbers: \n");
	int i;
	for (i = 3; i < 32; i++ )
		if (lucas_lehmer(i))
			printf("%2i -- %10lld\n", i, (long long)pow(2, i) - 1);
	printf("Press any key to continue...");
	_getch();

}