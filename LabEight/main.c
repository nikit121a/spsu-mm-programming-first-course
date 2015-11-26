#include <stdio.h>
#include <conio.h>
#include <stdlib.h>



int money(int number)
{
	long **array = (long **)malloc(8 * sizeof(long));
	for (int l = 0; l < 8; l++)
	{
		array[l] = (long *)malloc(100000 * sizeof(long));
	}

	int numbers[8] = { 1,2,5,10,20,50,100,200 };
	int i, j;
	//создание двумерного массива
	for (i = 0; i < 8; i++)					//заполняем первый столбец единицами
	{
		array[i][0] = 1;
	}
	for (j = 0; j <= number; j++)			//заполняем первую строку единицами
	{
		array[0][j] = 1;
	}
	for (i = 1; i < 8; i++)
	{
		for (j = 1; j <= number; j++)
		{
			if (j < numbers[i])
			{
				array[i][j] = array[i - 1][j];
			}
			else
			{
				array[i][j] = array[i - 1][j] + array[i][j - numbers[i]];
			}
		}
	}
	return array[7][number];
}

int main()
{
	double coin;
	printf_s("Enter your count\n");
	scanf_s("%lf", &coin);
	while ((coin < 0) || ((int)coin != coin))
	{
		printf_s("Wrong number\n");
		printf_s("Enter three natural numbers:\n");
		while (getchar() != '\n')
		{
			continue;
		}
		scanf_s("%lf", &coin);
	}

	printf_s("count: %d", money((int)coin));
	_getch();
	return 0;
}