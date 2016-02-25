#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M_T MEM_TAB
#define M_S 10000
#define M_T_S MEM_TAB_SIZE

/*  [i][0] - ptr = MEMORY+ i * sizeof(char)
[i][1] - the amount of allocated memory for [i][0]
[i][2] - = 0 => lock
= 1 => free*/
int* MEM_TAB[3];
char* MEMORY;
int MEM_TAB_SIZE = 0;

void init()
{
	MEM_TAB[0] = malloc(sizeof(int));
	MEM_TAB[1] = malloc(sizeof(int));
	MEM_TAB[2] = malloc(sizeof(int));
	M_T[0][0] = 0;
	M_T[1][0] = M_S;
	M_T[2][0] = 1;
	MEMORY = malloc(M_S + 1 * sizeof(int));
	for (int i = 0; i <= M_S; i++)
		MEMORY[i] = 0;
}

void print_mem_tab()
{
	printf("\n");
	printf("     ptr |  size | free\n");
	printf("   ------|-------|-----\n");
	printf("0)     0 | %5.d | %1.d\n", M_T[1][0], M_T[2][0]);
	int i = 1;
	while (i <= M_T_S)
	{
		printf("%d) %5.d | %5.d | %1.d\n", i, M_T[0][i], M_T[1][i], M_T[2][i]);
		i++;
	}
}

/*return ptr on MEMORY + [i][0]
return NULL if there are no place */
void* mymalloc(size_t size)
{

	int i = 0;
	while (M_T[1][i] * M_T[2][i] < size)
	{
		i++;
		if (i > M_S)
		{
			printf("No more place for new %d bytes.\n", size);
			return NULL;
		}
	}
	M_T[2][i] = 0;
	if (size < M_T[1][i])
	{
		M_T_S++;
		for (int k=0; k <= 2; k++)
			memcpy(M_T[k], M_T[k], (M_T_S + 1) * sizeof(int));

		for (int j = M_T_S; j >= i + 1; j--)
		{
			M_T[0][j] = M_T[0][j - 1];
			M_T[1][j] = M_T[1][j - 1];
			M_T[2][j] = M_T[2][j - 1];
		}

		M_T[0][i + 1] = M_T[0][i] + size;
		M_T[1][i + 1] = M_T[1][i] - size;
		M_T[2][i + 1] = 1;
		M_T[1][i] = size;
	}
	return MEMORY + M_T[0][i];
}

/*[i][0] == a => [i][2] = 1
If more than one "1" in [i][2] row => makes only one "1" */
void myfree(void* a)
{
	int i = 0;
	while (M_T[0][i] != (char*)a - (char*)MEMORY)
	{
		i++;
		if (i > M_S)
		{
			printf("Not exsist\n");
			return;
		}
	}
	M_T[2][i] = 1;
	if (i < M_T_S && M_T[2][i + 1] == 1)
	{
		M_T[1][i] += M_T[1][i +1];
		for (int j = i + 1; j < M_T_S; j++)
		{
			M_T[0][j] = M_T[0][j + 1];
			M_T[1][j] = M_T[1][j + 1];
			M_T[2][j] = M_T[2][j + 1];
		}
		M_T_S--;
		for (int k = 0; k <= 2; k++)
			memcpy(M_T[k], M_T[k], (M_T_S + 1) * sizeof(int));

	}
	if (i > 0 && M_T[2][i - 1] == 1)
	{
		M_T[1][i - 1] += M_T[1][i];
		for (int j = i; j < M_T_S; j++)
		{
			M_T[0][j] = M_T[0][j + 1];
			M_T[1][j] = M_T[1][j + 1];
			M_T[2][j] = M_T[2][j + 1];
		}
		M_T_S--;
		for (int k = 0; k <= 2; k++)
			memcpy(M_T[k], M_T[k], (M_T_S + 1) * sizeof(int));
	}
}

/*return ptr on new malloc ptr "a"
return NULL if it not possible */
void* myrealloc(void* ptr, int size_changing)
{
	int i = 0;
	while (M_T[0][i] != (char*)ptr - (char*)MEMORY)
	{
		i++;
		if (i > M_S)
		{
			printf("Not exsist2\n");
			return NULL;
		}
	}
	if (-size_changing > M_T[1][i])
	{
		printf("Can't be less than %d in realloc\n", -M_T[1][i]);
		return NULL;
	}

	void* temp;
	int old_size = M_T[1][i];
	temp = malloc(M_S * sizeof(char));
	memcpy(temp, MEMORY + M_T[0][i], sizeof(char)*old_size);
	myfree(ptr);
	ptr = mymalloc(size_changing + old_size);
	memcpy(ptr, temp, sizeof(char)*old_size);
	return ptr;
}

int main()
{
	init();

	int *a = mymalloc(sizeof(int) * 6);
	int *b = mymalloc(sizeof(int) * 13);
	int *c = mymalloc(sizeof(int) * 54);
	int *d = mymalloc(sizeof(int) * 99);
	a[4] = 55;
	print_mem_tab();
	printf("a[4] before realloc->>%d\n", a[4]);

	a = myrealloc(a, 219);
	printf("\nrealloc a (+219)");
	print_mem_tab();
	printf("a[4] after realloc--->>%d\n", a[4]);

	a = myrealloc(a, -39);
	printf("\nrealloc a (-39)");
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

	free(MEMORY);
	_getch();
}