#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define max_health 100
#define death_health 0
#define health_regen 5
#define simulation_time 100
#define max_generation 10

struct people
{
	int health;
	int immun;
	int zmb;
	int x;
	int y;
	int vir_timer;
};

struct virus
{
	int strength;
	int radius;
	int life_time;
	int score;
};


int simulate(struct people *h, struct virus virus)
{
	struct people human[1000];
	for (int i = 0; i < 1000; i++)
		human[i] = h[i];

	int cur_damage;
	int score = 0;

	for (int i = 0; i < 1000; i++)
		if (human[i].zmb)
			human[i].vir_timer = virus.life_time;

	for (int t = simulation_time; t > 0; t--)
	{
		for (int i = 0; i < 1000; i++)
		{
			if (human[i].zmb == 1 && human[i].vir_timer > 0)
			{
				for (int j = 0; j < 1000; j++)
					if (abs(human[j].x - human[i].x) + abs(human[j].y - human[i].y) <= virus.radius
						&& human[j].zmb == 0)
					{
						if (virus.strength - human[j].immun < 0)
							cur_damage = 0;
						else
							cur_damage = virus.strength - human[j].immun;
						human[j].health -= cur_damage;

						if (human[j].health <= death_health)
						{
							score++;
							if (j > i)
								human[j].zmb = -1; // become zombie next time
							if (j < i)
							{
								human[j].zmb = 1;   // become zombie next time automatic
								human[j].vir_timer = virus.life_time;
							}
						}
					}
				human[i].vir_timer--;
			}
			if (human[i].zmb == -1)
			{
				human[i].zmb = 1;
				human[i].vir_timer = virus.life_time;
			}
		}
		for (int i = 0; i < 1000; i++)
		{
			human[i].health += health_regen;
			if (human[i].health > max_health)
				human[i].health = max_health;
		}
	}

	return score;
}


int main()
{
	int coeff;
	int any;
	printf("Random coeff.");
	scanf("%d", &coeff);
	for (int i = 0; i <= coeff; i++)
		any = rand();

	struct people human[1000];

	int z = 0;
	char poly[100][100];
	FILE *polygon;
	polygon = fopen("poly.txt", "rb");

	char new_poly[100][100];
	int k = 0;
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
		{ 
			new_poly[i][j] = ' ';
			fread(&poly[i][j], sizeof(char), 1, polygon);
			if (poly[i][j] == '|')
			{
				human[k].health = max_health;
				human[k].immun = rand() % 101;
				human[k].zmb = 0;
				human[k].x = i;
				human[k].y = j;
				human[k].vir_timer = 0;
				k++;
			}
			if (poly[i][j] == 'Z')
			{
				human[k].health = death_health;
				human[k].zmb = 1;
				human[k].x = i;
				human[k].y = j;
				human[k].vir_timer = 0;
				z++;
				k++;
			}
		}

	struct virus virus[15];

	int k1, k2, k3;
	int n;
	do
	{
		printf("Your three integer parameters ( k1^2 + k2^2 < k3  for better result)  \n");
		printf("for example: 11 11 400 (tested when zombie <= 10) (%d zombie now):  \n", z);
		scanf("%d%d%d", &k1, &k2, &k3);
		for (int i = 0; i < 5; i++)
		{
			virus[i].radius = rand() % (k3 / (k1 + k2)) + 1;  
			virus[i].strength = rand() % (k3 / (k1 + k2)) + 1;
			virus[i].life_time = k3 / (k1 * virus[i].radius + k2 * virus[i].strength) + 10;
			virus[i].score = simulate(human, virus[i]);
			printf("%d %d %d\n%d\n\n", virus[i].radius, virus[i].strength, virus[i].life_time, virus[i].score);
		}
		printf("If everything ok input 0\n");
		scanf("%d", &n);
	} 
	while (n != 0);


	for (int generation = 1; generation < max_generation; generation++)  //evolution
	{
		printf("  %d Generation: \n", generation);

		for (int j = 0; j < 5; j++)
		{
			printf("%d virus: radius = %3.d, strength = %3.d, life time = %3.d, score : %3.d;\n", j+1,
					 virus[j].radius, virus[j].strength, virus[j].life_time, virus[j].score);
		}
		for (int i = 5; i < 15; i++)  //reproduction
		{
			int parent_1 = rand() % 5;
			int	parent_2 = rand() % 5;
			while (parent_1 == parent_2)
			{
				parent_2 = rand() % 5;
			}

			int temp = rand() % 10;

			switch (temp)
			{
			case 1:
				virus[i].radius = virus[parent_2].radius;
				virus[i].strength = virus[parent_1].strength;
				virus[i].life_time = virus[parent_1].life_time;
				break;
			case 2:
				virus[i].radius = virus[parent_1].radius;
				virus[i].strength = virus[parent_2].strength;
				virus[i].life_time = virus[parent_1].life_time;
				break;
			case 3:
				virus[i].radius = virus[parent_2].radius;
				virus[i].strength = virus[parent_2].strength;
				virus[i].life_time = virus[parent_1].life_time;
				break;
			case 4:
				virus[i].radius = virus[parent_1].radius;
				virus[i].strength = virus[parent_1].strength;
				virus[i].life_time = virus[parent_2].life_time;
				break;
			case 5:
				virus[i].radius = virus[parent_2].radius;
				virus[i].strength = virus[parent_1].strength;
				virus[i].life_time = virus[parent_2].life_time;
				break;
			case 6:
				virus[i].radius = virus[parent_1].radius;
				virus[i].strength = virus[parent_2].strength;
				virus[i].life_time = virus[parent_2].life_time;
				break;
			case 0: 
			case 7:
			case 8: 
			case 9:	//mutation
				virus[i].radius = rand() % (k3 / (k1 + k2)) + 1;
				virus[i].strength = rand() % (k3 / (k1 + k2)) + 1;
				virus[i].life_time = k3 / (k1 * virus[i].radius + k2 * virus[i].strength) + 10;
				break;
			default:
				break;
			}

			virus[i].score = simulate(human, virus[i]);
		}

		for (int i = 0; i < 5; i++) //selection
		{
			int max = 0, cur_max = 0;
			for (int j = 5; j < 15; j++)
			{
				if (max <= virus[j].score)
				{
					max = virus[j].score;
					cur_max = j;
				}
			}
			virus[i] = virus[cur_max];
			virus[cur_max].score = -1;
		}
		printf("\n");
	}

	printf("  %d Generation: \n", max_generation);

	for (int j = 0; j < 5; j++)
	{
		printf("%d virus: radius = %3.d, strength = %3.d, life time = %3.d, score : %3.d;\n", j+1, virus[j].radius,
			virus[j].strength, virus[j].life_time, virus[j].score);
	}

	printf("\nMax possible score: %d\n", 1000-z);

	_getch();
}