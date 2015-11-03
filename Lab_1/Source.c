#include <stdio.h>

void print_int32 (int a)
{
	printf("Negative binary form :\n");
	for (int i = 31; i >= 0; i--)
		if (a >= 0)
			printf("%d", ((a >> i) % 2));
		else
			printf("%d", -((a >> i) % 2));
	printf("\n\n");
}

void print_float (int a, char *binary_representation[])
{
	printf("Float form :\n");
	float f = a;
	unsigned char *x_f = &f;
	char hexadecimal_buf[10];
	sprintf(hexadecimal_buf, "%02x%02x%02x%02x", (unsigned char)x_f[3],
												 (unsigned char)x_f[2],
												 (unsigned char)x_f[1],
												 (unsigned char)x_f[0]);
	for (int i = 0; i < 8; ++i)
	{
		if (hexadecimal_buf[i] - '0' >= 0 && hexadecimal_buf[i] - '0' <= 9)
			printf("%s", binary_representation[hexadecimal_buf[i] - '0']);
		else
			printf("%s", binary_representation[hexadecimal_buf[i] - 'a' + 10]);
	}
	printf("\n\n");
}

void print_double(int a, char *binary_representation[])
{
	printf("Negatige double form :\n");
	double d = a;
	unsigned char *x_d = &d;
	char hexadecimal_buf[20];
	sprintf(hexadecimal_buf, "%02x%02x%02x%02x%02x%02x%02x%02x", (unsigned char)x_d[7],
																 (unsigned char)x_d[6],
																 (unsigned char)x_d[5],
																 (unsigned char)x_d[4],
																 (unsigned char)x_d[3],
																 (unsigned char)x_d[2],
																 (unsigned char)x_d[1],
																 (unsigned char)x_d[0]);
	for (int i = 0; i < 16; ++i)
	{
		if (hexadecimal_buf[i] - '0' >= 0 && hexadecimal_buf[i] - '0' <= 9)
			printf("%s", binary_representation[hexadecimal_buf[i] - '0']);
		else
			printf("%s", binary_representation[hexadecimal_buf[i] - 'a' + 10]);
	}
	printf("\n");
}

int main()
{
	int a;
	printf("View the product of autors long name and patronymic surnames in the\nnegative binary, float and negative double form:\n\n");
	a = 6 * 4 * 10;
	
	char *binary_representation[] = 
	{	"0000",
		"0001",
		"0010",
		"0011",
		"0100",
		"0101",
		"0110",
		"0111",
		"1000",
		"1001",
		"1010",
		"1011",
		"1100",
		"1101",
		"1110",
		"1111",
	};
	
	print_int32(-a);

	print_float(a, binary_representation);
	
	print_double(-a, binary_representation);

	printf("Press any key to exit\n");
	_getch();

	return 0;
}