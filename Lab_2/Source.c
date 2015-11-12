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


int relatively_prime(int x, int y)
{
	int o;
	while (x%y)
	{
		o = x%y;
		x = y;
		y = o;
	}
	if (y == 1)
		return 1;
	else
		return 0;
}

int main()
{
	double a, b, c;
	int z;

	printf("The program checks whether three entered integer (primitive)Pythagorean triples.");

	printf("a=");
	while (read_double(&a))
		printf("Please, try again\na=");

	printf("b=");
	while (read_double(&b))
		printf("Please, try again\nb=");

	printf("c=");
	while (read_double(&c))
		printf("Please, try again\nc=");
		
	if (a > c)
		z = c, c = a, a = z;

	if (b > c)
		z = c, c = b, b = z;

	if ((c * c == a * a + b * b) && (relatively_prime(c, b)))
		printf("Primitive Pythagorean triples");

	if ((c * c == a * a + b * b) && (!relatively_prime(c, b)))
		printf("Pythagorean triples");

	if (c * c != a * a + b * b)
		printf("Not Pythagorean triples");

	printf("\nPress any key to exit");
	_getch();

	return 0;
}
