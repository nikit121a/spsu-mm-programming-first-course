#include <stdio.h>

int relatively_prime(unsigned int x, unsigned int y)
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
	unsigned int a, b, c, z;
	printf("The program checks whether three entered integer (primitive)Pythagorean triples.");
	scanf_s("%u%u%u", &a, &b, &c);
	
	if (a > c)
		z = c, c = a, a = z;

	if (b > c)
		z = c, c = b, b = z;

	if ((c*c == a*a + b*b) && (relatively_prime(c, b)))
		printf("Primitive Pythagorean triples");

	if ((c*c == a*a + b*b) && (!relatively_prime(c, b)))
		printf("Pythagorean triples");

	if (c*c != a*a + b*b)
		printf("Not Pythagorean triples");

	printf("\nPress any key to exit");
	_getch();

	return 0;
}
