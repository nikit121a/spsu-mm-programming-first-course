#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
	int koeff;
	int any;
	scanf("%d", &koeff);
	printf("\n");
	for (int i = 0; i <= koeff; i++)
		any = rand();

	int k = 0;

	char poly[100][100];
	int people[1000][2];
	int zombie[1000][2];
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			poly[i][j] = ' ';

	int r1;
	int r2;
	int i = 0;
	while (i != 1000)
	{
		r1 = rand() % 100;
		r2 = rand() % 100;
		if (poly[r1][r2] == ' ')
		{
			i++;
			poly[r1][r2] = '|';
			people[i][0] = r1;
			people[i][1] = r2;
		}
	}
	i = 0;
	while (i < rand() % 50)
	{
		k = rand() % 1000;
		if (poly[people[k][0]][people[k][1]] == '|')
		{
			i++;
			zombie[i][0] = people[k][0];
			zombie[i][1] = people[k][1];
			poly[people[i][0]][people[i][1]] = 'Z';
		}
	}
	
	FILE *polygon;
	polygon = fopen("poly.txt", "wb");
	char e = '\n';

	int p = 0, z = 0;
	for (i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (poly[i][j] == '|')
				p++;
			if (poly[i][j] == 'Z')
				z++;
			fwrite(&poly[i][j], sizeof(char), 1, polygon);
		}
	}
	printf("people : %d\nzombie : %d", p, z);

	_getch();

	
}