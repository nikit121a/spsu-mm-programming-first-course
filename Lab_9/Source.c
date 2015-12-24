#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define BUF_SIZE 12
#define x 1000000

///* Читает double из консоли, возвращет 0 в случае успеха */
//int read_double(double *value)
//{
//	int length = 0;
//	char* end = NULL;
//	char buf[BUF_SIZE] = "";
//
//	/* Чтение в буфер */
//	fgets(buf, sizeof(buf), stdin);
//
//	/* Удаление символа перевода строки */
//	length = strlen(buf);
//	if (buf[length - 1] == '\n')
//	{
//		buf[--length] = '\0';
//
//		/* Перевод из строки в число */
//		*value = strtod(buf, &end);
//
//		/* Обработка ошибок */
//		if (length == 0)
//		{
//			printf("Error: empty string.\n");
//			return 1;
//		}
//		if (*end != '\0')
//		{
//			printf("Error: incorrect simbol.\n");
//			printf("\t%s\n", buf);
//			printf("\t%*c\n", (int)(end - buf) + 1, '^');
//			return 1;
//		}
//		if (*value - floor(*value) != 0)
//		{
//			printf("Error: not integer.\n");
//			return 1;
//		}
//		if (*value <= 0)
//		{
//			printf("Error: not positive.\n");
//			return 1;
//		}
//	}
//	else
//	{
//		/* Строка прочитана не полностью
//		Пропустить остаток строки*/
//		scanf("%*[^\n]");
//		scanf("%*c");
//		printf("Error: not more than %d simbols.\n", BUF_SIZE - 2);
//		return 1;
//	}
//	return 0;
//}

int main()
{
	int i;
	int* mdrs;
	mdrs = malloc(1000001 * sizeof(int));
		
	//double x;
	printf("The program calculates the maximum digital roots sum (MDRS) \nof all factorizations you entered number.\n");

	//while (read_double(&x))
	//	printf("Please, try again\n");

	for (i = 2; i <= x; i++)
	{
		mdrs[i] = i % 9;
		if (mdrs[i] == 0)
			mdrs[i] = 9;
	}
	int k = 45;
	/* Разложение числа i на 2 множителя(j и i/j) и поиск max суммы mdrs для них */
	for (i = 10; i <= x; i++)
	{
		int max = 0;
		for (int j = 2; j <= sqrt(i); j++)
			if (i%j == 0)
				if(max < (mdrs[j] + mdrs[i / j]))
					max = mdrs[j] + mdrs[i / j];
		if (max > mdrs[i])
			mdrs[i] = max;

		if (i % 10000 == 0)
			printf("%d\n", i/10000);
		if ((i - 2500) % 10000 == 0)
			printf("..");
		if ((i - 5000) % 10000 == 0)
			printf("..");
		if ((i - 7500) % 10000 == 0)
			printf("..");
		k += mdrs[i];
	}

	printf("%d = %d\n",(int)x, mdrs[(int)x]);
	printf("summ = %d\n", k);
	printf("Press any key to exit");

	_getch();
	free(mdrs);
	return 0;
}