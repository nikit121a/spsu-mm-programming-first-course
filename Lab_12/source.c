#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M_T MEM_TAB
#define M_S 100000

/*  [i][0] - ptr = MEMORY+ i * sizeof(char)
[i][1] - the amount of allocated memory for [i][0]
[i][2] - = 0 => lock
= 1 => free*/
int MEM_TAB[100002][3];
char* MEMORY;

void init()
{
	M_T[0][1] = 100000;
	M_T[0][2] = 1;
	M_T[100001][0] = -1;
	MEMORY = malloc(100001 * sizeof(int));
	for (int i = 0; i < 100001; i++)
		MEMORY[i] = 0;
}

void print_mem_tab()
{
	printf("\n");
	printf("     ptr |  size | free\n");
	printf("   ------|-------|-----\n");
	printf("0)     0 | %5.d | %1.d\n", M_T[0][1], M_T[0][2]);
	int i = 1;
	while (M_T[i][0] != 0)
	{
		printf("%d) %5.d | %5.d | %1.d\n", i, M_T[i][0], M_T[i][1], M_T[i][2]);
		i++;
	}
}

/*return ptr on MEMORY + [i][0]
return NULL if there are no place */
void* mymalloc(size_t size)
{
	int i = 0;
	while (M_T[i][1] * M_T[i][2] < size)
	{
		i++;
		if (i > M_S)
		{
			printf("No more place for new %d bytes.\n", size);
			return NULL;
		}
	}
	M_T[i][2] = 0;
	if (size < M_T[i][1])
		for (int j = M_S; j > i + 1; j--)
		{
			M_T[j][0] = M_T[j - 1][0];
			M_T[j][1] = M_T[j - 1][1];
			M_T[j][2] = M_T[j - 1][2];
		}
	M_T[i + 1][0] = M_T[i][0] + size;
	M_T[i + 1][1] = M_T[i][1] - size;
	M_T[i + 1][2] = 1;
	M_T[i][1] = size;
	return MEMORY + M_T[i][0];
}

/*[i][0] == a => [i][2] = 1
If more than one "1" in [i][2] row => makes only one "1" */
void myfree(void* a)
{
	int i = 0;
	while (M_T[i][0] != (char*)a - (char*)MEMORY)
	{
		i++;
		if (i > M_S)
		{
			printf("Not exsist\n");
			return;
		}
	}
	M_T[i][2] = 1;
	if (i > 0 && M_T[i + 1][2] == 1)
	{
		M_T[i][1] += M_T[i + 1][1];
		for (int j = i + 1; j < M_S; j++)
		{
			M_T[j][0] = M_T[j + 1][0];
			M_T[j][1] = M_T[j + 1][1];
			M_T[j][2] = M_T[j + 1][2];
		}
	}
	if (i<M_S && M_T[i - 1][2] == 1)
	{
		M_T[i - 1][1] += M_T[i][1];
		for (int j = i; j < M_S; j++)
		{
			M_T[j][0] = M_T[j + 1][0];
			M_T[j][1] = M_T[j + 1][1];
			M_T[j][2] = M_T[j + 1][2];
		}
	}
}

/*return ptr on new malloc ptr "a"
return NULL if it not possible */
void* myrealloc(void* a, int x)
{
	int i = 0;
	while (M_T[i][0] != (char*)a - (char*)MEMORY)
	{
		i++;
		if (i > M_S)
		{
			printf("Not exsist2\n");
			return NULL;
		}
	}
	if (-x > M_T[i][1])
	{
		printf("Can't be less than %d in realloc\n", -M_T[i][1]);
		return NULL;
	}

	void* temp;
	int old_size = M_T[i][1];
	temp = malloc(100000 * sizeof(char));
	memcpy(temp, MEMORY + M_T[i][0], sizeof(char)*old_size);
	myfree(a);
	a = mymalloc(x + old_size);
	memcpy(a, temp, sizeof(char)*old_size);
	return a;
}

int main()
{
	init();

	int *a = mymalloc(sizeof(int) * 6);
	int *b = mymalloc(sizeof(int) * 13);
	int *c = mymalloc(sizeof(int) * 124);
	int *d = mymalloc(sizeof(int) * 54);
	int *e = mymalloc(sizeof(int) * 999);
	a[4] = 55;
	print_mem_tab();
	printf("a[4] before realloc->>%d\n", a[4]);

	a = myrealloc(a, 8219);
	printf("\nrealloc a (+8219)");
	print_mem_tab();
	printf("a[4] after realloc--->>%d\n", a[4]);

	a = myrealloc(a, -309);
	printf("\nrealloc a (-309)");
	print_mem_tab();

	myfree(d);
	printf("\nfree d");
	print_mem_tab();

	myfree(c);
	printf("\nfree c");
	print_mem_tab();

	myfree(a);
	printf("\nfree a");
	print_mem_tab();

	int *z = mymalloc(sizeof(int) * 25);
	printf("\nmalloc z (25*4=100)");
	print_mem_tab();

	_getch();
}