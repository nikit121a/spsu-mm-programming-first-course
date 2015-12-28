#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define MIN(a, b) a < b ? a : b
#define MAX(a, b) a > b ? a : b
#define HP 100 // Person's health
#define HP_CHANGING 5 // The change of person's health
#define WIDTH 100 // The width of the field 
#define HEIGHT 100 // The height of the field 
#define RADIUS 30 // Maximum radius in which zombie is affecting
#define STRENGTH 100 // Maximum strength which zombie can use to affect
#define GENERAIONS 10 // The amount of generations
#define CROSS 5 // The amount of zombies who takes part in evolution
#define EMPTY -1
#define FULL_Z 0
#define FULL_P 1


int amountOfZombies = 50;

typedef struct _Person
{
	int health;
	int immunity;
}Person;

typedef struct _Zombie
{
	int radius;
	int strenght;
	int life;
}Zombie;

typedef struct _Point
{
	int x;
	int y;
	char busyness;
	Person person;
	Zombie zombie;
}Point;

Point field[HEIGHT][WIDTH];


int compare(const void *a, const void *b)
{
	return (*(int*)a - *(int*)b);
}

void makeField(FILE *file)
{
	int count = 0;
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			char c1, c2;;
			fscanf(file, "%c%c", &c1, &c2);
			if (c2=='E')
			{
				field[i][j].busyness = -1;
			}
			if (c2 == 'E')
			{
				field[i][j].busyness = EMPTY;
			}
			if (c2 == 'Z')
			{
				field[i][j].busyness = FULL_Z;
			}
			if (c2 == 'H')
			{
				field[i][j].busyness = FULL_P;
			}
		}
	}
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			field[i][j].y = i;
			field[i][j].x = j;
		}
	}
}

void makePerson()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (field[i][j].busyness == FULL_P)
			{
				field[i][j].person.health = HP;
				field[i][j].person.immunity = rand() % 101;
			}
		}
	}
}

void makeZombie(int k1, int k2, int k3)
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (field[i][j].busyness == FULL_Z)
			{
				field[i][j].zombie.radius = rand() % (RADIUS + 1);
				if (field[i][j].zombie.radius <5)
				{
					field[i][j].zombie.radius = 5;
				}
				field[i][j].zombie.strenght = rand() % (STRENGTH + 1);
				if (field[i][j].zombie.strenght < 15)
				{
					field[i][j].zombie.strenght = 15;
				}
				field[i][j].zombie.life = k3 / (k1 * field[i][j].zombie.radius + k2 * field[i][j].zombie.strenght);
			}
		}
	}
}

void makeNewZombie(int k1, int k2, int k3, int i, int j)
{
	field[i][j].zombie.radius = rand() % (RADIUS + 1);
	if (field[i][j].zombie.radius < 5)
	{
		field[i][j].zombie.radius = 5;
	}
	field[i][j].zombie.strenght = rand() % (STRENGTH + 1);
	if (field[i][j].zombie.radius < 15)
	{
		field[i][j].zombie.strenght = 15;
	}
	field[i][j].zombie.life = k3 / (k1 * field[i][j].zombie.radius + k2 * field[i][j].zombie.strenght);
	field[i][j].busyness = FULL_Z;
	amountOfZombies++;
}

void makeNewPoint(int i, int j)
{
	field[i][j].busyness = EMPTY;
	amountOfZombies--;
}

int zombieAttack(int k1, int k2, int k3)
{
	int amountOfDeath = 0;
	int temp;
	for (int i_z = 0; i_z < HEIGHT; i_z++)
	{
		for (int j_z = 0; j_z < WIDTH; j_z++)
		{
			if (field[i_z][j_z].busyness == FULL_Z)
			{
				for (int i_p = 0; i_p < HEIGHT; i_p++)
				{
					for (int j_p = 0; j_p < WIDTH; j_p++)
					{
						if (field[i_z][j_z].busyness == FULL_P)
						{
							if ((i_p - i_z) * (i_p - i_z) + (j_p - j_z)*(j_p - j_z) <= field[i_z][j_z].zombie.radius * field[i_z][j_z].zombie.radius)
							{
								temp = field[i_z][j_z].zombie.strenght - field[i_p][j_p].person.immunity;
								if (temp > 0)
								{
									field[i_p][j_p].person.health -= temp;
								}
							}
							if (field[i_p][j_p].person.health <= 0)
							{
								makeNewZombie(k1, k2, k3, i_p, j_p);
								amountOfDeath++;
							}
						}
					}
				}
				field[i_z][j_z].zombie.life--;
				if (field[i_z][j_z].zombie.life <= 0)
				{
					makeNewPoint(i_z, j_z);
				}
			}
		}
	}
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (field[i][j].busyness == FULL_P)
			{
				field[i][j].person.health = field[i][j].person.health < 95 ? field[i][j].person.health + HP_CHANGING : 100;
			}
		}
	}
	return amountOfDeath;
}

void evolution(int k1, int k2, int k3)
{
	int *points = (int*)malloc(sizeof(int) * CROSS);
	points[0] = rand() % amountOfZombies;
	while (1)
	{
		int temp = rand() % amountOfZombies;
		if (temp != points[0])
		{
			points[1] = temp;
			break;
		}
	}
	while (1)
	{
		int temp = rand() % amountOfZombies;
		if (temp != points[0] && temp != points[1])
		{
			points[2] = temp;
			break;
		}
	}
	while (1)
	{
		int temp = rand() % amountOfZombies;
		if (temp != points[0] && temp != points[1] && temp != points[2])
		{
			points[3] = temp;
			break;
		}
	}
	while (1)
	{
		int temp = rand() % amountOfZombies;
		if (temp != points[0] && temp != points[1] && temp != points[2] && temp != points[3])
		{
			points[4] = temp;
			break;
		}
	}

	qsort(points, CROSS, sizeof(int), compare);

	Point *zombie = (Point*)malloc(sizeof(Point) * CROSS);
	int l = 0, m = 0, n = 0;
	for (int i = 0; i < HEIGHT; i++)
	{
		if (m == 5)
		{
			break;
		}
		for (int j = 0; j < WIDTH; j++)
		{
			if (m == 5)
			{
				break;
			}
			if (field[i][j].busyness == FULL_Z)
			{
				if (l == points[n])
				{
					zombie[m] = field[i][j];
					m++;
					n++;
				}
				l++;
				
			}

		}
	}

	double crossing = (rand() % 10) / 10;
	for (int i = 0; i < CROSS; i++)
	{
		zombie[i].zombie.strenght = zombie[rand() % 6].zombie.strenght * (1 - crossing) + zombie[rand() % 6].zombie.strenght * crossing;
		zombie[i].zombie.radius = zombie[rand() % 6].zombie.radius * (1 - crossing) + zombie[rand() % 6].zombie.radius * crossing;
		zombie[i].zombie.life = k3 / (k1 * zombie[i].zombie.radius + k2 * zombie[i].zombie.strenght);
	}

	//mutation
	double temp = (rand() % 100) / 100;
	if (temp < (1 / 10))
	{
		int k = rand() % (amountOfZombies + 1);
		zombie[k].zombie.strenght = rand() % STRENGTH;
		zombie[k].zombie.radius = rand() % RADIUS;
		zombie[k].zombie.life = k3 / (k1 * zombie[k].zombie.radius + k2 * zombie[k].zombie.strenght);
	}
	for (int i = 0; i < CROSS; i++)
	{
		field[zombie[i].y][zombie[i].x] = zombie[i];
	}
}




int main()
{
	srand((unsigned int)time(NULL));
	int k1, k2, k3;
	FILE *file = fopen("file.txt", "r");
	fscanf(file, "%d", &k1);
	fscanf(file, "%d", &k2);
	fscanf(file, "%d", &k3);
	
	makeField(file);

	makePerson();
	makeZombie(k1, k2, k3);

	int countOfDeathPrevious = 0, countOfDeathNext = 0, countOfGenerations = 1;
	while (countOfGenerations < GENERAIONS && countOfDeathPrevious >= countOfDeathNext)
	{
		countOfGenerations++;
		countOfDeathPrevious = countOfDeathNext;
		countOfDeathNext = zombieAttack(k1, k2, k3);
		evolution(k1, k2, k3);
	}
	if (countOfDeathPrevious > countOfDeathNext)
	{
		countOfGenerations--;
		countOfDeathNext = countOfDeathPrevious;
	}
	printf("The best result in generation %d, virus was affected on %d people.", countOfGenerations, countOfDeathNext);
	return 0;
}



