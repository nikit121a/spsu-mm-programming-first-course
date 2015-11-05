#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"

void printBinaryRepresentation(char*a,int k)
{
	
	for (int i =k-1; i >=0; i--)
	{
		for (int j = 7; j>=0 ; j--)
		{
			printf("%d", (a[i] >> j) & 1);
		}
		printf(" ");
	}
	printf("\n");
}

void BinInt(int n) // Представление в виде int32.
{
	int size = sizeof(int);
	char* a = (char*)(&n);
	printBinaryRepresentation(a, size);
}

void BinFloat(float n) // Представление в виде float.
{
	int size = sizeof(float);
	char* a = (char*)(&n);
	printBinaryRepresentation(a,size);
}

void BinDouble(double n) // Представление в виде double.
{
	int size = sizeof(double);
	char* a = (char*)(&n);
	printBinaryRepresentation(a,size);
}

int main()
{
	int n = strlen("Platonova")* strlen("Mariia")* strlen("Victorovna");
	printf("The result of multiplication: ");
	printf("%d\n", n);
	printf("Int32 representation: ");
	BinInt(-n);
	printf("Float representation: ");
	BinFloat(-n);
	printf("Double representation: ");
	BinDouble(-n);
	getchar();
	return 0;
}