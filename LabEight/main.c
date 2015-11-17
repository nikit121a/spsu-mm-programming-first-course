#include <stdio.h>
#include <conio.h>


int recursive(int number, int coinValue, int returnValue)
{
	if (coinValue >= 200 && number / 200 > 0)
	{
		returnValue = recursive(number - 200, 200, returnValue);
	}
	if (coinValue >= 100 && number / 100 > 0)
	{
		returnValue = recursive(number - 100, 100, returnValue);
	}
	if (coinValue >= 50 && number / 50 > 0)
	{
		returnValue = recursive(number - 50, 50, returnValue);
	}
	if (coinValue >= 20 && number / 20 > 0)
	{
		returnValue = recursive(number - 20, 20, returnValue);
	}
	if (coinValue >= 10 && number / 10 > 0)
	{
		returnValue = recursive(number - 10, 10, returnValue);
	}
	if (coinValue >= 5 && number / 5 > 0)
	{
		returnValue = recursive(number - 5, 5, returnValue);
	}
	if (coinValue >= 2 && number / 2 > 0)
	{
		returnValue = recursive(number - 2, 2, returnValue);
	}
	if (number > 0)
	{
		returnValue = recursive(number - 1, 1, returnValue);
	}
	if (number == 0)
	{
		returnValue++;
	}
	return returnValue;

}




int main()
{
	int coin;
	printf_s("Enter your count\n");
	scanf_s("%d", &coin);

	while (coin < 0)
	{
		printf_s("Wrong number\n");
		printf_s("Enter three natural numbers:\n");
		while (getchar() != '\n')
		{
			continue;
		}
		scanf_s("%i" , &coin);
	}

	printf_s("count: %d", recursive(coin, 200, 0));
	_getch();
	return 0;

}