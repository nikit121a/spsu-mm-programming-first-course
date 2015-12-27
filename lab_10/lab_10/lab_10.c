#include <stdio.h>
#include <string.h>

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))
#define INITAL_HUMAN 1000
#define INITAL_SIZE 100
#define K1 10
#define K2 10
#define K3 180
#define HEALTH 8
#define IMMUNITY 2
#define MAX_TIME 100

#pragma pack(push, 1)
typedef struct
{
	int health;
	char accessory;
}field_cell;

typedef struct {
	int radius;
	int strength;
	int health;
	int score;
}virus_type;

typedef struct {
	int i;
	int j;
}pos;

#pragma pack(pop)


int infection(field_cell** field, pos* zombie_list, int i, int j, virus_type virus, int h)
{
	if (field[i][j].health == 0)
	{
		field[i][j].health++;
		return 0;
	}
	int result = 0;
	for (int cur_i = max(0, i - virus.radius); cur_i <= min(INITAL_SIZE - 1, i + virus.radius); cur_i++)
	{
		for (int cur_j = max(0, j - virus.radius); cur_j <= min(INITAL_SIZE - 1, j + virus.radius); cur_j++)
		{
			if (field[cur_i][cur_j].accessory == 'H')
			{
				field[cur_i][cur_j].health -= max(0, virus.strength - IMMUNITY);
				if (field[cur_i][cur_j].health <= 0)
				{
					result++;
					zombie_list[h + result].i = cur_i;
					zombie_list[h + result].j = cur_j;
					field[cur_i][cur_j].accessory = 'Z';
					field[cur_i][cur_j].health = virus.health;
				}
			}
		}
	}
	return result;

}

int simulate(field_cell** inital_field, virus_type virus)
{
	int result = 0, head_zombie_list = -1;
	field_cell** field = (field_cell**)malloc(INITAL_SIZE * sizeof(field_cell*));
	for (int i = 0; i < INITAL_SIZE; i++)
	{
		field[i] = (field_cell*)malloc(INITAL_SIZE * sizeof(field_cell));
		memset(field[i], 0, INITAL_SIZE * sizeof(field_cell));
	}

	pos *zombie_list = (pos*)malloc((INITAL_SIZE + 100) * INITAL_SIZE * sizeof(pos));



	for (int i = 0; i < INITAL_SIZE; i++)
	{
		for (int j = 0; j < INITAL_SIZE; j++)
		{
			field[i][j] = inital_field[i][j];
			if (field[i][j].accessory == 'Z')
			{
				field[i][j].health = virus.health;
				head_zombie_list++;
				result++;
				zombie_list[head_zombie_list].i = i;
				zombie_list[head_zombie_list].j = j;
			}
		}
	}

	head_zombie_list++;
	zombie_list[head_zombie_list].i = -1;
	int cur_time = 0, cur_head_zombie_list = -1;

	while (cur_time < MAX_TIME)
	{
		cur_time++;
		cur_head_zombie_list++;
		while (zombie_list[cur_head_zombie_list].i != -1)
		{
			int cur_result = infection(field, zombie_list, zombie_list[cur_head_zombie_list].i,
				zombie_list[cur_head_zombie_list].j, virus, head_zombie_list);
			head_zombie_list += cur_result;
			result += cur_result;

			field[zombie_list[cur_head_zombie_list].i][zombie_list[cur_head_zombie_list].j].health--;
			if (field[zombie_list[cur_head_zombie_list].i][zombie_list[cur_head_zombie_list].j].health > 0)
			{
				head_zombie_list++;
				zombie_list[head_zombie_list] = zombie_list[cur_head_zombie_list];
			}
			cur_head_zombie_list++;
		}
		if (result == INITAL_HUMAN)
		{
			for (int ii = 0; ii < INITAL_SIZE; ii++)
			{
				free(field[ii]);
			}
			return result + MAX_TIME - cur_time;
		}
		head_zombie_list++;
		zombie_list[head_zombie_list].i = -1;
	}


	for (int i = 0; i < INITAL_SIZE; i++)
	{
		free(field[i]);
	}

	free(zombie_list);

	return result;
}

void main()
{
	srand(2);
	field_cell** field = (field_cell**)malloc(INITAL_SIZE * sizeof(field_cell*));
	for (int i = 0; i < INITAL_SIZE; i++)
	{
		field[i] = (field_cell*)malloc(INITAL_SIZE * sizeof(field_cell));
		memset(field[i], 0, INITAL_SIZE * sizeof(field_cell));
	}


	FILE *input;


	input = fopen("test.txt", "r");

	for (int i = 0; i < INITAL_SIZE; i++)
	{
		for (int j = 0; j < INITAL_SIZE; j++)
		{
			char buf;
			fscanf(input, "%c%c", &buf, &field[i][j].accessory);
			if (field[i][j].accessory == 'H')
			{
				field[i][j].health = HEALTH;
			}
		}
	}

	virus_type virus_list[15];

	for (int i = 0; i < 5; i++)
	{
		virus_list[i].radius = rand() % (K3 / (K1 + K2)) + 1;
		virus_list[i].strength = rand() % (K3 / (K1 + K2)) + 1;
		virus_list[i].health = K3 / (K1 * virus_list[i].radius + K2 * virus_list[i].strength);
		virus_list[i].score = simulate(field, virus_list[i]);
	}


	for (int generation = 1; generation < 10; generation++)
	{

		for (int i = 5; i < 15; i++)
		{
			int parent_1 = rand() % 5, parent_2 = rand() % 5;
			while (parent_1 = parent_2)
			{
				parent_2 = rand() % 5;
			}

			int edge = rand() % 3;

			switch (edge)
			{
			case 0:
				virus_list[i].radius = virus_list[parent_2].radius;
				virus_list[i].strength = virus_list[parent_2].strength;
			case 1:
				virus_list[i].radius = virus_list[parent_1].radius;
				virus_list[i].strength = virus_list[parent_2].strength;
			case 2:
				virus_list[i].radius = virus_list[parent_1].radius;
				virus_list[i].strength = virus_list[parent_1].strength;
			default:
				break;
			}


			if (rand() % 2 == 0) 
			{
				virus_list[i].radius = rand() % (K3 / (K1 + K2)) + 1;
			}
			else
			{
				virus_list[i].strength = rand() % (K3 / (K1 + K2)) + 1;
			}

			virus_list[i].health = K3 / (K1 * virus_list[i].radius + K2 * virus_list[i].strength);
			virus_list[i].score = simulate(field, virus_list[i]);
		}

		for (int i = 0; i < 5; i++) 
		{
			int cur_max = 0, cur_max_pos;
			for (int j = 5; j < 15; j++)
			{
				if (cur_max < virus_list[j].score)
				{
					cur_max = virus_list[j].score;
					cur_max_pos = j;
				}
			}
			virus_list[i] = virus_list[cur_max_pos];
			virus_list[cur_max_pos].score = -1;
		}

		printf("Best virus type in %d Generation: \n", generation);
		printf("  radius - %d, strength - %d, life - %d, score - %d;\n", virus_list[0].radius,
				virus_list[0].strength, virus_list[0].health, virus_list[0].score);
	}

	printf("\nAnwser: \n");
	printf(" Highest score - %d .\n Radius - %d, strength - %d, life -  %d;\n", virus_list[0].score,
		virus_list[0].radius, virus_list[0].strength, virus_list[0].health);


	_getch();

	for (int i = 0; i < INITAL_SIZE; i++)
	{
		free(field[i]);
	}

	free(field);

	return;
}