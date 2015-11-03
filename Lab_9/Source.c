#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define BUF_SIZE 12

/* Читает double из консоли, возвращет 0 в случае успеха */
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
	int mdrs[100500], i;
	double x;
	printf("The program calculates the maximum digital roots sum (MDRS) \nof all factorizations you entered number.\n");

	while (read_double(&x))
		printf("Please, try again\n");

	for (i = 2; i <= x; i++)
	{
		mdrs[i] = i % 9;
		if (mdrs[i] == 0)
			mdrs[i] = 9;
	}

	/* Разложение числа i на 2 множителя(j и i/j) и поиск max суммы mdrs для них */
	for (i = 10; i <= x; i++)
	{
		int max = 0;
		for (int j = 2; j <= sqrt(i); j++)
			if (i%j == 0 && max < (mdrs[j] + mdrs[i / j]))
				max = mdrs[j] + mdrs[i / j];
		if (max > mdrs[i])
			mdrs[i] = max;		
	}

	printf("%d\n", mdrs[(int)x]);
	printf("Press any key to exit");

	_getch();
	return 0;
}