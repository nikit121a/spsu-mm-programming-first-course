#include <stdio.h>
#include <stdlib.h>
#include < math.h > 

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
	zombi[i].virus = rand() % 101;
	zombi[i].radius = rand() % 10;
	zombi[i].life = k3 / (k1*zombi[i].radius + k2*zombi[i].virus);
}


void humanskill(TheThing *human, int i)
{
	human[i].health = 100;
	human[i].immunity = rand() % 101;
	human[i].virus = 0;
	human[i].radius = 0;
	human[i].life = 0;
}


int main()
{
	int i = 0;
	int x, y, kolzombi, kolhuman = 950;
	printf("hfpvths gjkz, zombi");
	scanf("%d%d%d%", &x, &y, &kolzombi);

	//массивы структур зомби и людей
	TheThing *TheThing;
	TheThing = malloc(sizeof(TheThing) * 1000);

	//размещаем наших зомби
	int **pole = (int**)malloc(x*sizeof(int*));
	
	// ¬вод элементов массива
	//инициализаци€
	for (i = 0; i < x; i ++)  // цикл по строкам
	{
		// ¬ыделение пам€ти под хранение строк
		pole[i] = (int*)malloc(y*sizeof(int));
		for (int j = 0; j < y; j ++)  // цикл по столбцам
					pole[i][j] = -1;
	}
	////////////////////////////////////////////////////////////////////////
	int period = floor((x*y) / 1000);
	//расставить 1000 человек.
	int k = 0;
	for (i = 0; i < x; i += period)  // цикл по строкам
		for (int j = 0; j < y; j += period)  // цикл по столбцам
	{	
		pole[i][j] = k; 
		k++;
		TheThing[k].x = i;
		TheThing[k].y = j;
	}


	//нова€ попул€ци€
	int *population = (int*)malloc(kolzombi * sizeof(int));
	int k1 = rand() % 101, k2 = rand() % 101, k3 = rand() % 101;
	int createvirus = 0;

	while (createvirus <= 0)
	{
		//устанавливаем всем люд€м скилл
		for (i = 0; i < 1000; i++)
		{
			humanskill(TheThing, i);
		}
		int imunityvirus;


		//устанавливаем зомби скилл
		for (i = 0; i < kolzombi; i++)
		{	//перва€ попул€ци€. запоминаем мнеста заражени€
			if (createvirus == 0)
				population[i] = rand() % kolzombi;

			zombiskill(TheThing, population[i], k1, k2, k3);
		}
		//генетика!!
		if (createvirus < 0)
		{
			//любовь зомби. их замен€ют дети
			for (int k = 0; k < floor(kolzombi / 2); k++)
			{
				int life = TheThing[population[i*(rand() % 2 + 1)]].life;
				int virus = TheThing[population[i*(rand() % 2 + 1)]].virus;
				int radius = TheThing[population[i*(rand() % 2 + 1)]].radius;
				int life2 = TheThing[population[i*(rand() % 2 + 1)]].life;
				int virus2 = TheThing[population[i*(rand() % 2 + 1)]].virus;
				int radius2 = TheThing[population[i*(rand() % 2 + 1)]].radius;
				TheThing[population[i]].life = life;
				TheThing[population[i * 2]].life = life2;
				TheThing[population[i]].virus = virus;
				TheThing[population[i * 2]].virus = virus2;
				TheThing[population[i]].life = radius;
				TheThing[population[i * 2]].radius = radius2;
			}

			//мутаци€
			int j = kolzombi / 10;
			while (j > 0)
			{
				zombiskill(TheThing, population[rand() % kolzombi], rand() % 101, rand() % 101, rand() % 101);
			}

			//это просто селекци€, выживает сильнейший
			for (int k = 1; k < floor(kolzombi / 2); k++)
			{
				int strength1 = TheThing[population[i]].life + TheThing[population[i]].virus + TheThing[population[i]].radius;
				int strength2 = TheThing[population[i * 2]].life + TheThing[population[i * 2]].virus + TheThing[population[i * 2]].radius;
				if (strength1 > strength2)
				{
					TheThing[population[i * 2]].life = TheThing[population[i]].life;
					TheThing[population[i * 2]].virus = TheThing[population[i]].life;
					TheThing[population[i * 2]].radius = TheThing[population[i]].life;
				}
				else
				{
					TheThing[population[i]].life = TheThing[population[i * 2]].life;
					TheThing[population[i]].virus = TheThing[population[i * 2]].life;
					TheThing[population[i]].radius = TheThing[population[i * 2]].life;
				}
			}
		}

		//игра началась
		while (kolhuman != 0 || kolzombi != 0)
		{
			for (i = 0; i < 1000; i++)
			{
				// если зомби
				if (TheThing[i].health == 0)
				{
					//радиус
					for (int j = TheThing[i].x - TheThing[i].radius; j <= TheThing[i].x + TheThing[i].radius; j++)
						for (int k = TheThing[i].y - TheThing[i].radius; k <= TheThing[i].y + TheThing[i].radius; k++)
						{
							//заражаем соседей
							if (pole[j][k] != -1 && TheThing[pole[j][k]].health != 0)
								imunityvirus = TheThing[pole[j][k]].health - TheThing[i].virus;
							if (imunityvirus >= 0)
								TheThing[pole[j][k]].health -= imunityvirus;
							//превращаем их в зомби
							if (TheThing[pole[j][k]].health <= 0)
							{
								kolzombi++;
								kolhuman--;
								zombiskill(TheThing, pole[j][k], k1, k2, k3);
							}
						}
					//конец радиуса
					//уменьшаем жизнь зомби
					if (--TheThing[i].life <= 0)
					{
						TheThing[i].health = -100;
						kolzombi--;
					}
				}//конец зомби
				//люди, если здоровье минус - мЄртв.
				else
					//увеличиваем здоровье
					if (TheThing[i].health > 0 && TheThing[i].health <= 95)
					{
						TheThing[i].health += 5;
						if (TheThing[i].health > 100) TheThing[i].health = 100;
					}
				//конец люди
			}

			if (kolhuman <= 0)
			{
				printf("люди погибли.поздравл€ю");
				if (kolzombi <= 0)
				{
					printf("но зомби тоже. создать новый вирус?");
					int createvirus = 0;
				}
				int createvirus = 1;
			}

			if (kolzombi <= 0)
			{
				printf("зомби погибли. создание нового вируса");
				int createvirus = -1;
			}
		}
	}

		return 0;
	}