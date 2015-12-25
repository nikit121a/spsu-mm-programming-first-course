#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int *primes;

int MDRS(int n)
{
	if ((n % 9) != 0)
	{
		return n % 9;
	}
	else
	{
		return 9;
	}
}
void findPrimes()
{
	int n = 1000000;
	int k = 0, l = 0;
	int *a = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
	a[1] = 0;

	for (int s = 2; s < n; s++)
	{
		if (a[s] != 0)
		{
			k++;
			for (int j = s * 2; j < n; j += s)
			{
				a[j] = 0;
			}
		}
	}
	primes = (int*)malloc(sizeof(int) * k);

	for (int i = 0; i < n; i++)
	{
		if (a[i] != 0)
		{
			primes[l] = a[i];
			l++;
		}
	}
	free(a);
}

void getPrimes(int *array, int n)
{
	int i = 0, j = 0;
	while (n > 1)
	{
		if (primes[i] <= n)
		{
			if (n % primes[i] == 0)
			{
				n = n / primes[i];
				array[j] = primes[i];
				j++;
			}
			if (n % primes[i] != 0)
			{
				i++;
			}
		}
	}
}

int getAnswer(int *array)
{
	int answer = 0;
	answer += array[0] + 5 * array[4] + 6 * array[5] + 7 * array[6] + 8 * array[7] + 9 * array[8];

	answer += min(array[3], array[1]) * 8;

	array[3] = array[3] - min(array[3], array[1]);
	array[1] = array[1] - min(array[3], array[1]);

	answer += 4 * array[3];

	answer += 9 * ((array[2] - array[2] % 2) / 2);
	array[2] = array[2] % 2;

	answer += 8 * ((array[1] - array[1] % 3) / 3);
	array[1] = array[1] % 3;

	int mod = min(array[2], array[1]);
	answer += mod * 6;

	array[2] = array[2] - mod;
	array[1] = array[1] - mod;

	answer += 3 * array[2];

	answer += 4 * ((array[1] - array[1] % 2) / 2);
	array[1] = array[1] % 2;
	
	answer += array[1] * 2;

	return answer;
}



int main()
{
	int t1 = time(NULL);
	int n = 1000000;
	findPrimes();

	int *arrayOfPrimes = malloc(sizeof(int)*20);
	for (int i = 0; i < 20; i++)
		arrayOfPrimes[i] = 0;

	int amountOfPrimes[9] = { 0 };
	unsigned long long answer = 0;


	for (int i = 1; i < n; i++)
	{
		getPrimes(arrayOfPrimes, i);

		for (int j = 0; j < 20; j++)
		{
			if (arrayOfPrimes[j] != 0)
				amountOfPrimes[MDRS(arrayOfPrimes[j]) - 1]++;
		}
		int temp = getAnswer(amountOfPrimes);
		if (temp > MDRS(i))
		{
			answer += temp;
		}
		else
		{
			answer += MDRS(i);
		}

		for (int i = 0; i < 20; i++)
			arrayOfPrimes[i] = 0;


		for (int i = 0; i < 9; i++)
			amountOfPrimes[i] = 0;
	}
		
	printf("The answer is ");
	printf("%llu\n", answer);

	free(arrayOfPrimes);
	int t3 = time(NULL);
	printf("Programm running time ");
	printf("%d\n", t3 - t1); // Programm running time
	system("pause");
	return 0;
}