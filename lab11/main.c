#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define inital_h 1000
#define inital_s 100

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


int infection(field_cell** field, pos* zombie_list, int i, int j, virus_type virus, int immunity, int h) //spread the infection
{
	if (field[i][j].health == 0)
	{
		field[i][j].health++;
		return 0;
	}
	int result = 0;//zombie can infect humans in the square radius*radius;
	for (int cur_i = max(0, i - virus.radius); cur_i <= min(inital_s - 1, i + virus.radius); cur_i++)
	{
		for (int cur_j = max(0, j - virus.radius); cur_j <= min(inital_s - 1, j + virus.radius); cur_j++)
		{
			if(field[cur_i][cur_j].accessory == 'H')
			{
				field[cur_i][cur_j].health -= max(0, virus.strength - immunity);
				if(field[cur_i][cur_j].health <= 0)
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

int simulate(field_cell** inital_field, int max_time, virus_type virus, int immunity)//simulation of virus propagation
{
	int result = 0, head_zombie_list = -1;
	field_cell** field = (field_cell**)malloc(inital_s * sizeof(field_cell*));
	for (int i = 0; i < inital_s; i++)
	{
		field[i] = (field_cell*)malloc(inital_s * sizeof(field_cell));
		memset(field[i], 0, inital_s * sizeof(field_cell));
	}
	
	pos *zombie_list = (pos*)malloc((inital_s + 100) * inital_s * sizeof(pos));



	for (int i = 0; i < inital_s; i++) //There are coordinates of zombies in zombie_list 
	{
		for (int j = 0; j < inital_s; j++)
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

	while (cur_time < max_time) 
	{
		cur_time++;
		cur_head_zombie_list++;
		while (zombie_list[cur_head_zombie_list].i != -1) //-1 shows that new day begins
		{
			int cur_result = infection(field, zombie_list, zombie_list[cur_head_zombie_list].i,
				zombie_list[cur_head_zombie_list].j, virus, immunity, head_zombie_list);
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
		if(result == inital_h) //means that there no more humans on the field
		{
			for (int ii = 0; ii < inital_s; ii++)
			{
				free(field[ii]);
			}
			return result + max_time - cur_time;
		}
		head_zombie_list++;
		zombie_list[head_zombie_list].i = -1;
	}


	for (int i = 0; i < inital_s; i++)
	{
		free(field[i]);
	}

	free(zombie_list);

	return result;
}

void main()
{
	srand(1);
	field_cell** field = (field_cell**)malloc(inital_s * sizeof(field_cell*));
	for (int i = 0; i < inital_s; i++)
	{
		field[i] = (field_cell*)malloc(inital_s * sizeof(field_cell));
		memset(field[i], 0, inital_s * sizeof(field_cell));
	}

	
	FILE *input;
	int k1, k2, k3, h_health, h_immunity; //parameters (k1, k2, k3) and human health and immunity
	

	input = fopen("test.txt", "r");  

	fscanf(input, "%d%d%d%d%d", &k1, &k2, &k3, &h_health, &h_immunity);
	

	for (int i = 0; i < inital_s; i++)
	{
		for (int j = 0; j < inital_s; j++)
		{
			char buf;
			fscanf(input, "%c%c", &buf, &field[i][j].accessory);
			if (field[i][j].accessory == 'H')
			{
				field[i][j].health = h_health;
			}
		}
	}

	virus_type virus_list[15];

	for (int i = 0; i < 5; i++)
	{
		virus_list[i].radius = rand() % (k3 / (k1 + k2)) + 1;  //For correct work is necessary that random values for 
		virus_list[i].strength = rand() % (k3 / (k1 + k2)) + 1;//radius and strength are chosen from range 1..(k3 / (k1 + k2)) + 1
		virus_list[i].health = k3 / (k1 * virus_list[i].radius + k2 * virus_list[i].strength);
		virus_list[i].score = simulate(field, 100, virus_list[i], h_immunity); //score shows how succefull the virus type is
	}


	for (int generation = 1; generation < 10; generation++)  //evolution
	{
		printf("  %d Generation: \n", generation);

		for (int j = 0; j < 5; j++)
		{
			printf("%d type: radius - %d, strength - %d, life - %d, score - %d;\n", j, virus_list[j].radius, 
				virus_list[j].strength, virus_list[j].health, virus_list[j].score);
		}
		for (int i = 5; i < 15; i++)//reproduction
		{
			int parent_1 = rand() % 5 , parent_2 = rand() % 5;
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


			if (rand() % 2 == 0) //mutation
			{
				virus_list[i].radius = rand() % (k3 / (k1 + k2)) + 1;
			}
			else
			{
				virus_list[i].strength = rand() % (k3 / (k1 + k2)) + 1;
			}

			virus_list[i].health = k3 / (k1 * virus_list[i].radius + k2 * virus_list[i].strength); 
			virus_list[i].score = simulate(field, 100, virus_list[i], h_immunity);
		}

		for (int i = 0; i < 5; i++) //selection
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
	}

	printf("  %d Generation: \n", 10);

	for (int j = 0; j < 5; j++)
	{
		printf("%d type: radius - %d, strength - %d, life - %d, score - %d;\n", j, virus_list[j].radius,
			virus_list[j].strength, virus_list[j].health, virus_list[j].score);
	}


	printf("*************************\n");
	printf(" The most successful virus type scored %d points.\n Its radius - %d, strength - %d, life -  %d;\n", virus_list[0].score,
		virus_list[0].radius,	virus_list[0].strength, virus_list[0].health);


	_getch();

	for (int i = 0; i < inital_s; i++)
	{
		free(field[i]);
	}

	free(field);

	return;
}