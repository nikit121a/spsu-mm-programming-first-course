#include <stdio.h>
#include <stdlib.h>
#include <math.h> 

typedef struct  TheThing{
	int radius;
	int virus;
	int life;
	int health;
	int immunity;
	int x;
	int y;
}TheThing;


void zombiskill(TheThing *zombi, int i, int k1, int k2, int k3)
{
	zombi[i].health = 0;
	zombi[i].immunity = 0;
	zombi[i].virus = rand() % 101 + 1;
	zombi[i].radius = rand() % 10 + 1;
	zombi[i].life = k3 / (k1*zombi[i].radius + k2*zombi[i].virus);
}


void humanskill(TheThing *human, int i)
{
	human[i].health = 100;
	human[i].immunity = rand() % 101 + 1;
	human[i].virus = 0;
	human[i].radius = 0;
	human[i].life = 0;
}


int main()
{
	int i = 0;
	int x, y, kolzombi;
	while (i == 0)
	{
		printf("Enter two numbers: the size of the square of the field and the number of zombies\n");
		scanf("%d%d", &x, &kolzombi);
		y = x;
		double alina = sqrt((x*y) / 1000);
		if (alina <= 0) printf("so many people. try again\n");
		else i = 1;
	}

	int kolzombinew = kolzombi;

	TheThing *TheThingcopy;
	TheThingcopy = malloc(28 * 1000);
	//������� �������� ����� � �����
	// int * 7 ��������� ��������� thething
	TheThing *TheThing;
	TheThing = malloc(28 * 1000);

	//��������� ����� �����
	int **pole = (int**)malloc(x*sizeof(int*));

	// ���� ��������� �������
	//�������������
	for (i = 0; i < x; i++)  // ���� �� �������
	{
		// ��������� ������ ��� �������� �����
		pole[i] = (int*)malloc(y*sizeof(int));
		for (int j = 0; j < y; j++)  // ���� �� ��������
			pole[i][j] = -1;
	}
	////////////////////////////////////////////////////////////////////////

	int period = sqrt((x*y) / 1000);
	//���������� 1000 �������.
	int k = 0;
	for (i = 0; i < x; i += period)  // ���� �� �������
		for (int j = 0; j < y; j += period)  // ���� �� ��������
		{
			if (k == 1000) { break; break; }
			pole[i][j] = k;
			TheThing[k].x = i;
			TheThing[k].y = j;
			k++;
		}


	//����� ���������
	int *population = (int*)malloc(kolzombi * sizeof(int));
	int k1 = rand() % 101 + 1, k2 = rand() % 101 + 1, k3 = rand() % 101 + 1;
	int createvirus = 0;
	int life, virus, radius, life2, virus2, radius2;
	while (createvirus <= 0)
	{
		kolzombi = kolzombinew;
		int kolhuman = 1000 - kolzombinew;
		//������������� ���� ����� �����
		for (i = 0; i < 1000; i++)
		{
			humanskill(TheThing, i);
		}
		int imunityvirus = -1;;


		//������������� ����� �����
		for (i = 0; i < kolzombi; i++)
		{	//������ ���������. ���������� ������ ���������
			if (createvirus == 0)
				population[i] = rand() % kolzombi + 1;

			zombiskill(TheThing, population[i], k1, k2, k3);
		}


		//��������!!
		if (createvirus < 0)
		{
			//������ ����� k  � k*2. �� �������� ����, �������������� ������� ������� � ���� ���������� ������� ���������� ��������
			for (int k = 0; k < kolzombi; k++)
			{

				int randomlove = rand() % 1;
				if (randomlove == 0)	TheThing[population[k]].life = life;
				else	TheThing[population[k]].life = life2;
				randomlove = rand() % 1;
				if (randomlove == 0)		TheThing[population[k]].virus = virus;
				else	TheThing[population[k]].virus = virus2;
				randomlove = rand() % 1;
				if (randomlove == 0)		TheThing[population[k]].life = radius;
				else	TheThing[population[k]].radius = radius2;
			}

			//�������
			int j = kolzombi / 10;
			while (j > 0)
			{
				zombiskill(TheThing, population[rand() % kolzombi + 1], rand() % 101 + 1, rand() % 101 + 1, rand() % 101 + 1);
			}

			//��� ������ ��������, �������� ����������
			for (int k = 1; k < floor(kolzombi / 2); k++)
			{
				int strength1 = TheThing[population[k]].life + TheThing[population[k]].virus + TheThing[population[k]].radius;
				int strength2 = TheThing[population[k * 2]].life + TheThing[population[k * 2]].virus + TheThing[population[k * 2]].radius;
				if (strength1 > strength2)
				{
					TheThing[population[k * 2]].life = TheThing[population[k]].life;
					TheThing[population[k * 2]].virus = TheThing[population[k]].life;
					TheThing[population[i * 2]].radius = TheThing[population[k]].life;
				}
				else
				{
					TheThing[population[k]].life = TheThing[population[k * 2]].life;
					TheThing[population[k]].virus = TheThing[population[k * 2]].life;
					TheThing[population[k]].radius = TheThing[population[k * 2]].life;
				}
			}
		}


		int	endpole = 0;
		int kolpeopleitiration = 0, kolpeopleitiration2 = 0, itiratoin = -1, itiratoin2 = -1;
		//���� ��������

		for (int zom = 0; zom < kolzombi; zom++)
		{
			kolzombi = kolzombinew;
			kolhuman = 1000 - kolzombinew;
			for (i = 0; i < 1000; i++)
			{
				// ���� �����
				if (TheThing[i].health == 0)
				{
					TheThingcopy[i] = TheThing[population[zom]];
				}
				else
				{
					TheThingcopy[i] = TheThing[i];
				}
			}

			while (kolhuman > 0 && kolzombi > 0)
			{
				for (i = 0; i < 1000; i++)
				{
					// ���� �����
					if (TheThingcopy[i].health == 0)
					{
						for (int j = TheThingcopy[i].x - TheThingcopy[i].radius; j <= TheThingcopy[i].x + TheThingcopy[i].radius; j++)
						{
							//������
							if (endpole != 0) break;
							for (int k = TheThingcopy[i].y - TheThingcopy[i].radius; k <= TheThingcopy[i].y + TheThingcopy[i].radius; k++)
							{
								//�������� �������
								endpole = 0;
								if (k >= y) { k = y - 1; endpole = 1; }
								if (j >= x) { j = x - 1;  endpole = 1; }
								if (k < 0)	k = 0;
								if (j < 0)	j = 0;
								if (pole[j][k] != -1 && TheThingcopy[pole[j][k]].health != 0 && pole[j][k] != i)
									imunityvirus = TheThingcopy[pole[j][k]].health - TheThingcopy[i].virus;
								else imunityvirus = -1;
								if (imunityvirus >= 0)
									TheThingcopy[pole[j][k]].health -= imunityvirus;
								//���������� �� � �����
								if (TheThingcopy[pole[j][k]].health <= 0)
								{
									kolzombi++;
									kolhuman--;
									zombiskill(TheThingcopy, pole[j][k], k1, k2, k3);
								}
								if (endpole != 0) break;
							}
							TheThingcopy[i].life--;
						}
					}//����� �����
					//����, ���� �������� ����� - ����.
					else
					{
						//����������� ��������
						if (TheThingcopy[i].health > 0 && TheThingcopy[i].health <= 95)
						{
							TheThingcopy[i].health += 5;
							if (TheThingcopy[i].health > 100) TheThingcopy[i].health = 100;
						}
						if (TheThingcopy[i].health < 0 && TheThingcopy[i].health != -100)
						{
							TheThingcopy[i].health = -100;
							kolzombi--;
						}
					}
					//����� ����
				}
			}

			//��� �� ����� � ����� ������� ������
			if (kolhuman <= 0)
			{

				printf("people died. Congratulations\n");
				if (kolzombi <= 0)
				{
					printf("�� ����� ����. ������� ����� �����? 0 - ���, 1 - ��\n");
					int s;
					scanf("%d", &s);
					if (s == 0) return 0;
					else createvirus = -1;
				}
				return 0;
			}
			if (kolzombi <= 0)
			{
				//2 ������ ������
				if (kolpeopleitiration < kolhuman)

					if (kolpeopleitiration2 < kolhuman)
					{
						kolpeopleitiration2 = kolhuman;
						itiratoin2 = population[zom];
					}
					else
					{
						kolpeopleitiration2 = kolpeopleitiration;
						itiratoin2 = itiratoin;
						kolpeopleitiration = kolhuman;
						itiratoin = population[zom];
					}

				printf("zombie killing. creating a new virus\n");
				int createvirus = -1;
				//�������������� ���� �����
				life = TheThingcopy[itiratoin2].life;
				virus = TheThingcopy[itiratoin2].virus;
				radius = TheThingcopy[itiratoin2].radius;
				life2 = TheThingcopy[itiratoin].life;
				virus2 = TheThingcopy[itiratoin].virus;
				radius2 = TheThingcopy[itiratoin].radius;

			}
		}

		return 0;
	}
}