#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void deg(double x, double y, double z)
{
	double angle;
	angle = acos((x * x + y * y - z * z) / (2 * x * y)) * 180 / acos(-1);
	int angle2 = angle;
	printf("%d,", angle2);
	angle = (angle - angle2) * 60;
	angle2 = angle;
	printf("%d'", angle2);
	angle = (angle - angle2) * 60;
	angle2 = angle;
	printf("%d''\n", angle2);
}

int main()
{
	float x, y, z;
	scanf_s("%f%f%f", &x, &y, &z);
	if (x < 0 || y < 0 || z < 0)
	{
		printf("Incorrect input\n");
		getchar();
		exit(0);
	}
	else
	{
		if (x + y <= z || x + z <= y || y + z <= x)
		{
			printf("Nope\n");
		}
		else
		{
			printf("Yes\n");
			deg(x, y, z);
			deg(z, x, y);
			deg(y, z, x);
		}

	}
	getchar();
	return 0;
}