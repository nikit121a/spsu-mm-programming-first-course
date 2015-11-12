#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>


int check(char *massiv)
{
	for (int i = 0; i < strlen(massiv); i++)
	{
		while (!isalpha(massiv[i]))
		{
			printf_s("Error! Please, enter the correct form:");
			scanf_s("%s", massiv, 20);
		}
	}
	return 0;
}

int taskB(int O)
{
	if (O >= 2)
	{
		taskB(O / 2);
	}
	printf("%d", O % 2);
	return 0;
}

int DecToBin(int s)
{
	int a[64], i;

	for (i = 0; i < 64; i++)
	{
		a[i] = 0;
	}

	for (i = 0; s>0; i++)
	{
		a[i] = s % 2;
		s = s / 2;
	}

	int c = i;
	int t = 0;

	for (int j = 63, i = 0; i <= c; i++)
	{
		t = a[j];
		a[j] = a[i];
		a[i] = t;
		j -= 1;
	}
	for (i = 0; i < c; i++)
	{
		a[i] = 0;
	}

	printf_s("A positive floating point number of single precision:\n");
	int O = 127 + c - 1;
	printf_s("0");
	taskB(O);
	for (i = 64 - c + 1; i < 64; i++)
	{
		printf_s("%i", a[i]);
	}
	for (i = 22 - c; i >= 0; i--)
	{
		printf_s("0");
	}

	printf_s("\n");
	printf_s("A negative floating point number of double precision:\n");
	int o = 1023 + c - 1;
	printf_s("1");
	taskB(o);
	for (i = 64 - c + 1; i < 64; i++)
	{
		printf_s("%i", a[i]);
	}
	for (i = 51 - c; i >= 0; i--)
	{
		printf_s("0");
	}
	printf_s("\n");


	for (i = 0; i < 64; i++)
	{
		if (a[i] == 1)
		{
			a[i] = 0;
		}
		else
		{
			a[i] = 1;
		}
	}


	if (a[63] == 0)
	{
		a[63] = 1;
	}
	else
	{
		for (i = 63; i >= 0; i--)
		{
			if (a[i] == 1)
			{
				a[i] = 0;
			}
			else
			{
				a[i] = 1;
				break;
			}
		}

	}


	printf_s("Negative 32-bit integer\n");
	for (i = 32; i <64; i++)
	{
		printf_s("%i", a[i]);
	}
	return 0;
}

int main()
{
	const int MAX_LENGTH = 20;
	int s;
	char sur[MAX_LENGTH], nam[MAX_LENGTH], pat[MAX_LENGTH];
	printf_s("Enter your surname, name and patronymic:\n ");

	scanf_s("%s", sur, MAX_LENGTH);
	check(sur);
	scanf_s("%s", nam, MAX_LENGTH);
	check(nam);
	scanf_s("%s", pat, MAX_LENGTH);
	check(pat);

	s = strlen(sur) * strlen(nam) * strlen(pat);
	DecToBin(s);

	_getch();
	return 0;

}