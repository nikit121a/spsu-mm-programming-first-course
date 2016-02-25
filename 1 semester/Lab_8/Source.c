#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BUF_SIZE 12

int read_double(double *value)
{
	int length = 0;
	char* end = NULL;
	char buf[BUF_SIZE] = "";

	/* Чтение в буфер */
	fgets(buf, sizeof(buf), stdin);

	/* Удаление символа перевода строки */
	length = strlen(buf);
	if (buf[length - 1] == '\n')
	{
		buf[--length] = '\0';

		/* Перевод из строки в число */
		*value = strtod(buf, &end);

		/* Обработка ошибок */
		if (length == 0)
		{
			printf("Error: empty string.\n");
			return 1;
		}
		if (*end != '\0')
		{
			printf("Error: incorrect simbol.\n");
			printf("\t%s\n", buf);
			printf("\t%*c\n", (int)(end - buf) + 1, '^');
			return 1;
		}
		if (*value - floor(*value) != 0)
		{
			printf("Error: not integer.\n");
			return 1;
		}
		if (*value <= 0)
		{
			printf("Error: not positive.\n");
			return 1;
		}
	}
	else
	{
		/* Строка прочитана не полностью
		Пропустить остаток строки*/
		scanf("%*[^\n]");
		scanf("%*c");
		printf("Error: not more than %d simbols.\n", BUF_SIZE - 2);
		return 1;
	}

	return 0;
}

int main()
{
	int value[8], N[8][10000], i, j;
	double x;

	printf("The program calculates the number of ways to change the amount you entered \n");
	printf("pence coins in denominations of 1, 2, 5, 10, 20, 50, 100, 200 pence.\n");

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 10000; j++)
		{
			if (i * j == 0)
				N[i][j] = 1;
			else
				N[i][j] = 0;
		}

	value[0] = 1;
	value[1] = 2;
	value[2] = 5;
	value[3] = 10;
	value[4] = 20;
	value[5] = 50;
	value[6] = 100;
	value[7] = 200;

	while (read_double(&x))
		printf("Please, try again\n");

	for (i = 1; i < 8; i++)
		for (j = 1; j <= x; j++)
		{
			if (j < value[i])
				N[i][j] = N[i - 1][j];
			else
				N[i][j] = N[i - 1][j] + N[i][j - value[i]];
		}

	printf("Number of ways to change:\n%d\nPress any key to exit", N[7][j-1]);
	_getch();

	return 0;
}