#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"

int Pythagoras(int edge1, int edge2, int edge3) // явл€ютс€ ли эти числа пифагоровой тройкой?..
{
	int l = 0;
	if((edge1*edge1 + edge2*edge2 == edge3*edge3) || (edge1*edge1 + edge3*edge3 == edge2*edge2) || (edge2*edge2 + edge3*edge3 == edge1*edge1))
	{
		l++;
	}
	return(l);
}

int Gcd(int edge1, int edge2, int edge3) // ¬заимно просты ли эти числа?..
{
	int gcd = edge2, r, l = 0;
	r = edge1; 
	while (r%gcd != 0)
	{
		int k = gcd;
		gcd = r%gcd;
		r = k;
	}
	r = edge3;
	while (r%gcd != 0)
	{
		int k = gcd;
		gcd = r%gcd;
		r = k;
	}
	if(gcd == 1)
	{
		l++;
	}
	return(l);
}

int main()
{
	int edge1, edge2, edge3;
	while (1)	// ¬ыполн€ем, пока не будут введены корректные числа
	{
		printf("Enter 3 integer positive numbers: ");
		scanf("%d%d%d", &edge1, &edge2, &edge3);
		scanf("%*[^\n]");
		if(edge1 > 0 && edge2 > 0 && edge3 > 0)
		{
			int pyt = Pythagoras(edge1, edge2, edge3);
			int gcd = Gcd(edge1, edge2, edge3);
			if(!pyt)
			{
				printf("%s\n", "This numbers is not Pythagoras three");
				printf("%s\n", "Please, try again");
			}
			if(pyt && gcd)
			{
				printf("%s\n", "This numbers is Pythagoras primitive three");
				break;
			}
			if(pyt)
			{
				printf("%s\n", "This numbers is Pythagoras three");
				break;
			}
		}
		else
		{
			printf("%s\n", "Incorrect input");
			printf("%s\n", "Please, try again");
		}
	}
	getchar();
	return 0;
}