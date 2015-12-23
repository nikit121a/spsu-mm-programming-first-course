#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))
#define inital_s 100
#define h_human 10
#define stamp 15
#define parent_stamp 5
#define max_time 100
enum id { H = 'H', Z = 'Z' };

#pragma pack(push, 1)
typedef struct
{
	int health;
	int immunity;
	enum id identification;
}s_human;
typedef struct
{
	int radius;
	int strength;
	int life;
	int points;
}s_zombie;
typedef struct
{
	int x;
	int y;
}position;
#pragma pack(pop)


int eden(s_human** cur_human, position* p_zombie, int x, int y, s_zombie virus, s_human** o_human, int count) //Eden of the Earth
{
	if (cur_human[x][y].health == 0)
	{
		return 0;
	}
	int result = 0;
	//проходим по всему радиусу действия вируса у данного зомби, если это зомби,то ничего не делаем, иначе - вычисляем новую жизнь человека
	//или превращаем его в зомби.
	for (int running_x = max(0, x - virus.radius); running_x <= min(inital_s - 1, x + virus.radius); running_x++)
	{
		for (int running_y = max(0, y - virus.radius); running_y <= min(inital_s - 1, y + virus.radius); running_y++)
		{
			if (cur_human[running_x][running_y].identification == 'H')
			{
				cur_human[running_x][running_y].health -= max(0, virus.strength - o_human[running_x][running_y].immunity);
				if (cur_human[running_x][running_y].health <= 0)
				{
					result++;
					p_zombie[count + result].x = running_x;
					p_zombie[count + result].y = running_y;
					cur_human[running_x][running_y].identification = 'Z';
					cur_human[running_x][running_y].health = virus.life;
				}
			}
		}
	}
	//возвращаем количество новозараженных зомби
	return result;

}

int game(s_human** original_human, s_zombie virus)
{

	int result = 0, count_of_zombie = -1;
	s_human** human = (s_human**)malloc(inital_s * sizeof(s_human*));					//выделяем память под массив, содержащий информацию
	for (int i = 0; i < inital_s; i++)													//об оставшихся в живых
	{
		human[i] = (s_human*)malloc(inital_s * sizeof(s_human));
		memset(human[i], 0, inital_s * sizeof(s_human));
	}

	position *p_zombie = (position*)malloc(inital_s * inital_s * sizeof(position));		//позиция зомби на поле

	for (int i = 0; i < inital_s; i++)
	{
		for (int j = 0; j < inital_s; j++)
		{
			human[i][j] = original_human[i][j];
			if (human[i][j].identification == 'Z')										//находим все позиции зомби
			{
				human[i][j].health = virus.life;
				count_of_zombie++;
				result++;
				p_zombie[count_of_zombie].x = i;
				p_zombie[count_of_zombie].y = j;
			}
		}
	}
	int time = 0;

	int cur_count_of_zombie = count_of_zombie;
	while (cur_count_of_zombie != 0)													//количество зараженных
	{
		int cur_zombie = 0;
		time++;
		//result=количество зараженных на данный момент
		while (cur_zombie != result - 1)													//повторяем, пока не просмотрим всех зомби
		{
			int cur_result = eden(human, p_zombie, p_zombie[cur_zombie].x,
				p_zombie[cur_zombie].y, virus, original_human, count_of_zombie);

			cur_count_of_zombie += cur_result;
			count_of_zombie += cur_result;
			result += cur_result;

			human[p_zombie[cur_zombie].x][p_zombie[cur_zombie].y].health--;				//забираем один день жизни у зомби
																						//делаем проверку, жив ли зомби
			if (human[p_zombie[cur_zombie].x][p_zombie[cur_zombie].y].health == 0)
			{
				cur_count_of_zombie--;
			}
			cur_zombie++;																//переходим к следующему зомби
		}
		for (int x = 0; x < inital_s; x++)
		{
			for (int y = 0; y < inital_s; y++)
			{
				if (human[x][y].identification == 'H' && human[x][y].health != 10)
				{
					human[x][y].health += 1;
				}
			}
		}
		if (result == 1000)																//если все люди стали зомби
		{
			for (int l = 0; l < inital_s; l++)
			{
				free(human[l]);
			}
			free(human);
			free(p_zombie);
			return result + max_time - time;
		}
	}

	for (int j = 0; j < inital_s; j++)													//об оставшихся в живых
	{
		free(human[j]);
	}
	free(human);
	free(p_zombie);

	return result;
}


int main()
{
	srand(1);
	s_human** human = (s_human**)malloc(inital_s * sizeof(s_human*));
	for (int i = 0; i < inital_s; i++)
	{
		human[i] = (s_human*)malloc(inital_s * sizeof(s_human));
		memset(human[i], 0, inital_s * sizeof(s_human));
	}


	FILE *input;
	int k1, k2, k3;

	input = fopen("field.txt", "r");

	fscanf(input, "%d %d %d", &k1, &k2, &k3);
	for (int i = 0; i < inital_s; i++)
	{
		for (int j = 0; j < inital_s; j++)
		{
			char buf;
			fscanf(input, "%c%c", &buf, &human[i][j].identification);
			if (human[i][j].identification != 'Z')
			{
				human[i][j].health = h_human;
				human[i][j].immunity = rand() % 19 + 1;
			}
		}
	}

	s_zombie virus[stamp];

	//k3=life(k1*radius+k2*strenght)
	for (int i = 0; i < parent_stamp; i++)
	{
		virus[i].radius = rand() % (k3 / (k1 + k2)) + 1;
		virus[i].strength = rand() % (k3 / (k1 + k2)) + 1;
		virus[i].life = k3 / (k1 * virus[i].radius + k2 * virus[i].strength);
		virus[i].points = game(human, virus[i]);											//скорость распространения вируса
	}

	for (int generation = 1; generation < 20; generation++)										//генерация разных поколений
	{
		printf("  %d Generation: \n", generation);

		for (int j = 0; j < 5; j++)
		{
			printf("%d type: radius - %d, strength - %d, life - %d, points - %d;\n", j, virus[j].radius,
				virus[j].strength, virus[j].life, virus[j].points);
		}
		for (int i = parent_stamp; i < stamp; i++)
		{
			int parent1 = rand() % 5, parent2 = rand() % 5;										//выбор родителей для потомков
			while (parent1 = parent2)
			{
				parent2 = rand() % 5;
			}

			switch (rand() % 3)
			{
			case 0:
				virus[i].radius = virus[parent2].radius;
				virus[i].strength = virus[parent2].strength;
				break;
			case 1:
				virus[i].radius = virus[parent1].radius;
				virus[i].strength = virus[parent2].strength;
				break;
			case 2:
				virus[i].radius = virus[parent1].radius;
				virus[i].strength = virus[parent1].strength;
				break;
			default:
				virus[i].radius = virus[parent2].radius;
				virus[i].strength = virus[parent1].strength;
				break;
			}


			if (rand() % 2 == 0)																//создаём мутацию гена
			{
				virus[i].radius = rand() % (k3 / (k1 + k2)) + 1;
			}
			else
			{
				virus[i].strength = rand() % (k3 / (k1 + k2)) + 1;
			}

			virus[i].life = k3 / (k1 * virus[i].radius + k2 * virus[i].strength);
			virus[i].points = game(human, virus[i]);
		}
		for (int i = 0; i < parent_stamp; i++)
		{
			int max_points = 0, max_index;													//выбор новых 5 особей
			for (int j = 5; j < 15; j++)
			{
				if (max_points < virus[j].points)
				{
					max_points = virus[j].points;
					max_index = j;
				}
			}
			virus[i] = virus[max_index];
			virus[max_index].points = 0;
		}
	}

	printf("  %d Generation: \n", 20);

	for (int j = 0; j < parent_stamp; j++)
	{
		printf("%d type: radius - %d, strength - %d, life - %d, points - %d;\n", j, virus[j].radius,
			virus[j].strength, virus[j].life, virus[j].points);
	}
	printf("\n");
	printf(" The most successful virus type points %d.\n Its radius - %d, strength - %d, life -  %d;\n", virus[0].points,
		virus[0].radius, virus[0].strength, virus[0].life);

	_getch();

	for (int i = 0; i < inital_s; i++)
	{
		free(human[i]);
	}
	free(human);
	return 0;
}