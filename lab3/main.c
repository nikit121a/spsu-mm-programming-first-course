#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void angle(double x, double y, double z)
{
	double ang;
	ang = acos((x * x + y * y - z * z) / (2 * x * y));
	ang *= 180;
	ang /= acos(-1);
	int p = ang;
	printf("%d,", p);
	ang = (ang - p) * 60;
	p =  ang;
	printf("%d'", p);
	ang = (ang - p) * 60;
	p = ang;
	printf("%d''\n", p);
}

int main()
{
	float x = -1, y = -1, z = -1;
	int check = 0;

	while (!check)
	{
		printf("Input the numbers: ");
		scanf("%f%f%f", &x, &y, &z);
		scanf("%*[^\n]");
		if (x < 0 || y < 0 || z < 0) {
			printf("incorrect input, try again\n");
		}
		else
		{
			check = 1;
		}

	}


	if(x + y <= z || x + z <= y || y + z <= x)
	{
		printf("No");
	}
	else
	{
		printf("Yes\n");
		angle(x, y, z);
		angle(z, y, x);
		angle(x, z, y);
	}
	_getch();
	return 0;
}