#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 12
#define PI 3.141592653589793238462

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
		if (*value <= 0)
		{
			printf("Error: not a positive number.\n");
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

void print_angle(double a, double b, double c)
{
	double x = acos((b * b + c * c - a * a) / (2 * b * c)) * 180 / PI;
	int grad, min, sec;
	grad = x;
	x = (x - grad) * 3600;
	min = x / 60;
	sec = x;
	sec %= 60;
	printf("%02d'%02d\"%02d\n", grad, min, sec);
}

int main()
{
	double a, b, c;	
	printf("The program calculates the angles of a triangle with sides you entered.\n");

	do
	{
		printf("a=");
		while (read_double(&a))
			printf("Please, try again\na=");

		printf("b=");
		while (read_double(&b))
			printf("Please, try again\nb=");

		printf("c=");
		while (read_double(&c))
			printf("Please, try again\nc=");

		if (a >= b + c || b >= a + c || c >= a + b)
			printf("Error: Not tringle.\nPlease, try again\n");
	}
	while
		(a >= b + c || b >= a + c || c >= a + b);
	
	printf("\nalpha:");
	print_angle(a, b, c);
	printf("\nbeta: ");
	print_angle(b, a, c);
	printf("\ngamma:");
	print_angle(c, b, a);

	printf("Press any key to exit");
	_getch();
}