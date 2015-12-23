#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define min(a, b) a < b ? a : b
#define max(a, b) a > b ? a : b
#define COUNT 10 // Number of ancestors
#define DEPTH 10 // Number of generations
#define ITERATIONS 5 // Time of emulating
#define MAX_HP 100 // Max HP of the humans
#define HP_INCREASE 5 // How many HP will be recovered
#define PERSONS 1000 // Count of the persons on the field
#define STRENGTH 45 // Max randomly choosed Strength - 1
#define RADIUS 4 // Coefficient that associates sizes of the field and randomly choosed radius
#define POSSIBILITY 45 // Number that control random generator in the multiply function
#define MUTATION 9 // Possibility of the mutation, should be less than POSSIBILITY / 2

typedef struct
{
	int x;
	int y;
} point; 

typedef struct
{
	int strength;
	int radius;
	int period;
} gen;

typedef struct
{
	int index;
	int value;
} info;

void swap(point *a, point *b)
{
	point temp;
	temp.x = a->x;
	temp.y = a->y;
	a->x = b->x;
	a->y = b->y;
	b->x = temp.x;
	b->y = temp.y;
	return;
}

void multiply(gen *ancestors, info *inf, int height, int width, int k1, int k2, int k3)
{
	int i, j, k, temp, possibility;
	gen *result;
	time_t t;
	srand((unsigned)time(&t));
	result = (gen*)malloc(sizeof(gen) * COUNT);
	k = 0;
	for(i = 0; i < COUNT / 2; i++)
	{
		for(j = i + 1; j < COUNT / 2 && k < COUNT; j++)
		{
			possibility = rand() % POSSIBILITY;
			if(possibility < MUTATION)
			{
				// Mutation
				result[k].strength = rand() % STRENGTH;
				temp = min(height / RADIUS, width / RADIUS);
				temp = max(temp, 1);
				result[k].radius = rand() % temp;
				result[k].period = k3 / (max(k1 * result[k].radius + k2 * result[k].strength, 1));
			}
			// Crossingover
			if(possibility >= MUTATION && possibility < POSSIBILITY / 2)
			{
				result[k].strength = ancestors[inf[i].index].strength;
				result[k].radius = ancestors[inf[j].index].radius;
				result[k].period = k3 / (max(k1 * result[k].radius + k2 * result[k].strength, 1));
			}
			if(possibility >= POSSIBILITY / 2)
			{
				result[k].strength = ancestors[inf[j].index].strength;
				result[k].radius = ancestors[inf[i].index].radius;
				result[k].period = k3 / (max(k1 * result[k].radius + k2 * result[k].strength, 1));
			}
			k++;
		}
	}
	memcpy(ancestors, result, sizeof(gen) * COUNT);
	return;
}

int emulation(char **field, int **immunity, int height, int width, int radius,int strength, int period, int steps)
{
	// Hold human's health points and count of zombie's turns at options[][]
	int i, j, k, n, count = 0, iter = 0;
	int **options;
	if(radius * strength * period == 0)
	{
		return 0;
	}
	options = (int**)malloc(sizeof(int*) * height);
	for(i = 0; i < height; i++)
	{
		options[i] = (int*)malloc(sizeof(int) * width);
		for(j = 0; j < width; j++)
		{
			if(field[i][j] == 'H')
			{
				options[i][j] = MAX_HP;
			}
			if(field[i][j] == 'Z')
			{
				options[i][j] = period;
			}
		}
	}
	while(iter < steps)
	{
		// Simulating through the model
		for(i = 0; i < height; i++)
		{
			for(j = 0; j < width; j++)
			{
				if(field[i][j] == 'Z' && options[i][j] != 0) 
				{
					// For zombies that can act
					for(k = (max(i - radius, 0)); k < (min(i + radius + 1, height)); k++)
					{
						for(n = (max(j - radius, 0)); n < (min(j + radius + 1, width)); n++)
						{
							if(field[k][n] == 'H' && options[k][n] > 0)
							{
								options[k][n] = (strength - immunity[k][n] >= 0) ? options[k][n] - (strength - immunity[k][n]) : options[k][n];
							}
						}
					}
				}
			}
		}
		for(i = 0; i < height; i++)
		{
			for(j = 0; j < width; j++)
			{
				if(field[i][j] == 'Z')
				{
					// Remove zombies that can't act
					if(options[i][j] <= 1)
					{
						field[i][j] = '.';
					}
					else
					{
						options[i][j]--;
					}
				}
				if(field[i][j] == 'H' && options[i][j] <= 0)
				{
					// Transform humans with zero or less health points into zombies
					field[i][j] = 'Z';
					options[i][j] = period;
					count++;
				}
				if(field[i][j] == 'H' && options[i][j] > 0 && options[i][j] > MAX_HP - HP_INCREASE)
				{
					// Increase health points of humans
					options[i][j] += HP_INCREASE;
				}
			}
		}
		iter++;
	}
	for(i = 0; i < height; i++)
	{
		free(options[i]);
	}
	free(options);
	return count;
}

int main()
{
	int count, height, width, k1, k2, k3; // Parametrs of the model
	int	i, j, len, k, n, strength, radius, period, value, old_max = 0;
	int **immunity;
	char **field, **fieldcopy;
	point *places;
	gen *gens;
	info *information;
	time_t t;
	srand((unsigned)time(&t));
	gens = (gen*)malloc(sizeof(gen) * COUNT);
	information = (info*)malloc(sizeof(info) * COUNT / 2);
	memset(information, 0, sizeof(info) * COUNT / 2);

	printf("Input the number of zombies, height and width of field, constants k1, k2, k3,\nk3 = (k1 * radius + k2 * strength) / life:\n");
	scanf_s("%d %d %d %d %d %d", &count, &height, &width, &k1, &k2, &k3);

	while(count <= 0 || count > PERSONS || height <= 0 || width <= 0 || height * width < PERSONS || k1 <= 0 || k2 <= 0 || k3 <= 0)
	{
		printf("Incorrect input: all numbers should be natural,\ncount of zombies should be less or equal to 1000,\narea of the field must be more or equal to 1000.\nTry again:\n");
		scanf_s("%d %d %d %d %d %d", &count, &height, &width, &k1, &k2, &k3);
	}

	k = PERSONS - count; // number of peoples
	places = (point*)malloc(sizeof(point) * height * width);
	field = (char**)malloc(sizeof(char*) * height);
	immunity = (int**)malloc(sizeof(int*) * height);
	fieldcopy = (char**)malloc(sizeof(char*) * height);
	for(i = 0; i < height; i++)
	{
		field[i] = (char*)malloc(sizeof(char) * width);
		immunity[i] = (int*)malloc(sizeof(int) * width);
		fieldcopy[i] = (char*)malloc(sizeof(char) * width);
	}
	// Following code place humans and zombies randomly
	for(i = 0; i < height * width; i++)
	{
		places[i].y = i % height;
		places[i].x = i / height;
	}
	len = height * width;
	for(i = 0; i < k; i++)
	{
		j = rand() % len;
		field[places[j].y][places[j].x] = 'H';
		immunity[places[j].y][places[j].x] = rand() % 101;
		swap(&places[j], &places[len - 1]);
		len--;
	}
	for(i = 0; i < count; i++)
	{
		j = rand() % len;
		field[places[j].y][places[j].x] = 'Z';
		swap(&places[j], &places[len - 1]);
		len--;
	}
	for(i = 0; i < height * width - PERSONS; i++)
	{
		j = rand() % len;
		field[places[j].y][places[j].x] = '.';
		swap(&places[j], &places[len - 1]);
		len--;
	}
	for(i = 0; i < height; i++)
	{
		for(j = 0; j < width; j++)
		{
			printf("%c", field[i][j]);
		}
		printf("\n");
	}

	// Randomly choose the gens of the first generation
	for(i = 0; i < COUNT; i++)
	{
		for(j = 0; j < height; j++)
		{
			memcpy(fieldcopy[j], field[j], sizeof(char) * width);
		}
		gens[i].strength = rand() % STRENGTH;
		k = min(height / RADIUS, width / RADIUS);
		k = max(k, 1);
		gens[i].radius = rand() % k;
		gens[i].period = k3 / (max(k1 * gens[i].radius + k2 * gens[i].strength, 1));
		value = emulation(fieldcopy, immunity, height, width, gens[i].radius, gens[i].strength, gens[i].period, ITERATIONS);
		j = 0;
		while(j < COUNT / 2 && value < information[j].value)
		{
			j++;
		}
		if(j < COUNT / 2)
		{
			for(k = COUNT / 2 - 1; k > j; k--)
			{
				information[k].index = information[k - 1].index;
				information[k].value = information[k - 1].value;
			}
			information[j].index = i;
			information[j].value = value;
		}
	}
	n = 0;
	while(n < DEPTH && old_max < information[0].value)
	{
		multiply(gens, information, height, width, k1, k2, k3);
		old_max = information[0].value;
		for(i = 0; i < COUNT; i++)
		{
			for(j = 0; j < height; j++)
			{
				memcpy(fieldcopy[j], field[j], sizeof(char) * width);
			}
			value = emulation(fieldcopy, immunity, height, width, gens[i].radius, gens[i].strength, gens[i].period, ITERATIONS);
			j = 0;
			while(j < COUNT / 2 && value < information[j].value)
			{
				j++;
			}
			if(j < COUNT / 2)
			{
				for(k = COUNT / 2 - 1; k > j; k--)
				{
					information[k].index = information[k - 1].index;
					information[k].value = information[k - 1].value;
				}
				information[j].index = i;
				information[j].value = value;
			}
		}
		n++;
	}
	printf("Best type was received on the %d generation.\nRadius: %d;\nStrength: %d;\nPeriod: %d;\nAnd it infects %d humans.\nPress any key to exit...", n + 1, gens[information[0].index].radius, gens[information[0].index].strength, gens[information[0].index].period, information[0].value);
	getchar();
	getchar();
	return 0;
}