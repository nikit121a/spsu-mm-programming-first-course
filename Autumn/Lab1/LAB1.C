/*Leonid Voroshilov, 143*/
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "LAB1.H"



void IntEval(int num)
{
	int i;
	printf("Int32 represenation: ");
	//Simply read and print representation
	for (i = LEN_INT - 1 ; i >= 0 ; i--)
	  printf("%i",  (num >> i) & 1);
}

void FloatEval(float num)
{

	if(LEN_FLOAT ==  LEN_INT - 1)
	{
		/*The quickest way to present number is to read it from memory.
		  But binary operationst whit float and double are forbidden.
		  In uinion all elements use same memory. So we can try to cheat a bit: 
		  write in union number as float, and then read as int (if only sizes of types are equal).*/
		union	MyFloat
		{
			float asFloat;
			long int asInteger;
		} testFloat;
		int i;

		testFloat.asFloat = num;

		printf("\nFloat32 represenation: ");
		for (i = LEN_INT - 1; i >= 0; i--)
			printf("%i", (testFloat.asInteger >> i) & 1);
	}
	else
	{
		/*If not - we can create representation by ourselves (according to task - num is always integer)*/
		int i, len, exp;
		int mem[STANDART_FLOAT] = { 0 }; //array as "memory" to put number in it

		if(num < 0)
		{
			num *= -1;
			mem[31] = 1;                 //sign
		}
		len = floor(log2(num));          //firs position with '1'(we can ignore this '1')

		num -= pow(2, len);
		for (i = len - 1; i >= 0; i--)
		{
			if(num >= pow(2, i))
			{
				num -= pow(2, i);
				mem[22 - (len - 1  - i)] = 1;
			}
		}
		exp = len + 127;
		for (i = 30; i >=23; i--) 
		{
			if(exp >= pow(2, i- 23))
			{
				exp -= pow(2, i - 23);
				mem[i] = 1;
			}
		}
		printf("\nFloat32 represenation: ");
		for (i = 31; i >= 0; i--)
			printf("%i", mem[i]);
	}
}

/*Algorithm is same as in float*/
void DoubleEval(double num)
{
	if(LEN_DOUBLE == LEN_LONG)
	{
		union MyDouble
		{
			double asDouble;
			long long asLong;
		} testDouble;
		int i;
		testDouble.asDouble = num;

		printf("\nDouble64 represenation: ");
		for (i = LEN_DOUBLE - 1; i >= 0; i--)
			printf("%lli", (testDouble.asLong >> i) & 1);
	}
	else
	{
		int i, len, exp;
		int mem[STANDART_DOUBLE] = { 0 };

		if(num < 0)
		{
			num *= -1;
			mem[63] = 1;
		}
		len = floor(log2(num));

		num -= pow(2, len);
		for (i = len - 1; i >= 0; i--)
		{
			if(num >= pow(2, i))
			{
				num -= pow(2, i);
				mem[51 - (len - 1 - i)] = 1;
			}
		}
		exp = len + 1023;
		for (i = 62; i >= 52; i--)
		{
			if(exp >= pow(2, i - 52))
			{
				exp -= pow(2, i - 52);
				mem[i] = 1;
			}
		}
		printf("\nDouble64 represenation: ");
		for (i = 63; i >= 0; i--)
			printf("%i", mem[i]);
	}

}

int main(void)
{
	int eval = strlen("Voroshilov") * strlen("Leonid") * strlen("Andreevich") * -1;
	printf("Number: %i\n", eval);
	IntEval(eval);
	FloatEval(eval * -1);
	DoubleEval(eval);
	printf("\nPress 'Enter'to continue...");
	getchar();
	return 0;
}