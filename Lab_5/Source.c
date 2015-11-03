#include <stdio.h>
#include <stdlib.h>
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
		if (sqrt(*value) == floor(sqrt(*value)))
		{
			printf("Error: square root is rational.\n");
			return 1;
		}
		if (*value<=0)
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
	int a_0, a, b, c, b_0, c_0, period = 0;
	double n;
	printf("The program finds the period of the continued fraction of the \nsquare root integer you entered.\n");

	while (read_double(&n))
		printf("Please, try again\n");

	printf("Period: \n");
	a_0 = sqrt(n);
	b = b_0 = a_0;
	c = c_0 = n - a_0*a_0;
	do
	{
		a = (a_0 + b) / c;
		b = a*c - b;
		c = (n - b*b) / c;
		period++;
		printf("%d ", a);
	} 
	while
		((b != b_0) || (c != c_0));

	printf("\nPeriod length:\n%d\n", period);

	printf("Press any key to exit");
	_getch();

	return 0;
}