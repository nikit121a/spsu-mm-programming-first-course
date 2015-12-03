#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
 
int gcd(int x, int y)
{
	return y ? gcd(y, x % y) : x;
}

int main()
{
   char c[80];
   int mas[3] = { -1, -1, -1 };
   printf("Enter three numbers.\n");
   int flag = 0;

   while (flag == 0)
   {
	   fgets(c, 80, stdin);
	   sscanf(c, "%d%*[' ']%d%*[' ']%d%*[' ']", &mas[0], &mas[1], &mas[2]);
	   if (mas[0] >= 0 && mas[1] >= 0 && mas[2] >= 0)
	   {
		   flag = 1;
		   int a, b, d;
		   for (d = 0; d < 3; ++d)
			   for (b = 0; b < 3; ++b)
				   for (a = 0; a < 3; ++a)
					   if ((mas[a] * mas[a]) + (mas[b] * mas[b]) == (mas[d] * mas[d]))
					   {
						   if (gcd(mas[a], mas[b]) == 1 && gcd(mas[a], mas[d]) == 1 && gcd(mas[d], mas[b]) == 1)
						   {
							   printf("a=%d\tb=%d\tc=%d", mas[a], mas[b], mas[d]);
							   printf("      primitive Pythagorean triples\n");
						   }
						   else
						   {
							   printf("a=%d\tb=%d\tc=%d\n", mas[a], mas[b], mas[d], "Pythagorean triple (not primitive)");
						   }
						   return 0;
					   }
	   }
	   else
	   {
		   printf("Wrong input. Try again.\n");
	   }
   }
   printf("This is not Pythagorean triple\n");
   return 0;
}