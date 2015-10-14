#include <stdio.h>
#include <math.h>

#define name 7 // Length of name
#define sur 6 // Length of surname
#define middle 10 // Length of middlename

void get_int32(int n) 
{

	/*
		Prints number 'n' in Int32 binary representation
	*/
	int i;
	printf("Int32 conversion: ");	
	for(i = 31; i >= 0; i--)
		printf("%d", abs(((1 << i) & n) >> i));
	printf("\n");
}

void get_float(int n)
{

	/*
		Prints number 'n' in Float binary representation
	*/
	int i, k, exponent = 127;
	
	printf("Float conversion: %d", n >= 0 ? 0 : 1);
	n=abs(n);
	for(i = 1, k = 0; i < n; i <<= 1, k++);
	k--;
	exponent += k;
	for(i = 7; i >= 0; i--)
		printf("%d",abs(((1 << i) & exponent) >> i));
	for(i = k - 1; i >= 0; i--)
		printf("%d",abs(((1 << i) & n) >> i));
	for(i = 22 - k; i >= 0; i--)
		printf("0");
	printf("\n");
}

void get_double(int n)
{

	/*
		Prints number 'n' in Double binary representation
	*/
	int i, k, exponent = 1023;
	
	printf("Double conversion:\n%d", n >= 0 ? 0 : 1);
	n=abs(n);
	for(i = 1, k = 0; i < n; i <<= 1, k++);
	k--;
	exponent += k;
	for(i = 10; i >= 0; i--)
		printf("%d",abs(((1 << i) & exponent) >> i));
	for(i = k - 1; i >= 0; i--)
		printf("%d",abs(((1 << i) & n) >> i));
	for(i = 51 - k; i >= 0; i--)
		printf("0");
	printf("\n");
}

int main()
{

	int number = name * sur * middle; //according to condition

	printf("The original number is %d\n", number);

	get_int32(-number);
	get_float(number);
	get_double(-number);

	printf("Press 'Enter' to close the console...");
	
	getchar();

	return 0;
}