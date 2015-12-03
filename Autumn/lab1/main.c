#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>


void printbin(int num)
{
	unsigned char highBit = 1 << (CHAR_BIT - 1);
	const int signBit = 0;
	const int Exponentn = 8;
	unsigned char *p = (unsigned char *)&num;
	int bitNumber = 0;
	for (int i = sizeof(int) - 1; i >= 0; --i)
		{
			unsigned char nextByte = p[i];
			for (int i = 0; i < CHAR_BIT; ++i)
			{
				bool isSet = (nextByte & highBit) != 0;
				printf("%d", isSet ? 1 : 0);
				nextByte <<= 1;
				++bitNumber;
			}
			printf(" ");
		}
}

void printdoub(double num)
{
	unsigned char highBit = 1 << (CHAR_BIT - 1);
	const int signBit = 0;
	const int Exponentn = 8;
	unsigned char *p = (unsigned char *)&num;
	int bitNumber = 0;
	for (int i = sizeof(double) - 1; i >= 0; --i)
	{
		unsigned char nextByte = p[i];
		for (int i = 0; i < CHAR_BIT; ++i)
		{
			bool isSet = (nextByte & highBit) != 0;
			printf("%d", isSet ? 1 : 0);
			nextByte <<= 1;
			++bitNumber;
		}
		printf(" ");
	}

}

void printfl(float num)
{
	unsigned char highBit = 1 << (CHAR_BIT - 1);
	const int signBit = 0;
	const int Exponentn = 8;
	unsigned char *p = (unsigned char *)&num;
	int bitNumber = 0;
	for (int i = sizeof(float) - 1; i >= 0; --i)
	{
		unsigned char nextByte = p[i];
		for (int i = 0; i < CHAR_BIT; ++i)
		{
			bool isSet = (nextByte & highBit) != 0;
			printf("%d", isSet ? 1 : 0);
			nextByte <<= 1;
			++bitNumber;
		}
		printf(" ");
	}

}

int main(){

	printf("Keep your last name, first name and patronymic.\n");
	int LengthOfTheName = 0, i = 0;
	char family[80], name[80], lastname[80], c[250];
	printf("Keep your last name, first name and patronymic.\n");	
	int flag = 0;

	while (flag == 0)
	{
		fgets(c, 80, stdin);	
			sscanf(c, "%[A-Za-z]%*[' ']%[A-Za-z]%*[' ']%[A-Za-z]", &family, &name, &lastname);
			int number = strlen(family) + strlen(name) + strlen(lastname);
			if (strlen(c) == number + 3)
			{
				flag = 1;
				number = strlen(family) * strlen(name) * strlen(lastname);
				printf("Negative 32-bit integer\n");
				printbin(-number);
				printf("\nPositive floating-point single precision of IEEE 754\n");
				printfl(number);
				printf("\nNegative floating-point double-precision IEEE 754\n");
				printdoub(-number);
			}
			else
			{
				printf("Wrong input. Try again.\n");
			};
		
	}

	return 0;
}