#include "stdio.h"
#include "stdlib.h"


void push_back2(int x, int *Time, int n)
{
	int *A = (int*)malloc((n + 1)*sizeof(int));
	A[n] = x;
	for (int i = 0; i < n; i++)
	{
		A[i] = Time[i];
	}
	free(Time);
	/*for (int i = 0; i < n + 1; i++)
	{
		printf("%d", A[i]);
		printf(" ");
	}
	printf("\n");*/
}

void push_back(int x, int*A, int n) // ѕередаем число, которое хотим добавить, сам массив и количество в нем элементов.
{
	int *Time = (int*)malloc(n*sizeof(int));
	for (int i = 0; i < n; i++)
	{
		Time[i] = A[i];
	}
	free(A);
	push_back2(x, Time, n);
}

void get_element(int k, int*A, int n) // ѕередаем индекс числа, которое хотим получить, сам массив и количество в нем элементов.
{
	int l = -1; // ¬ыводим ее, если пользователь вышел за пределы массива.
	if((k <= n - 1) && (k >= 0))
	{
		l = A[k];
	}
	printf("%s\n", "If there isn't element with such index, the result is -1");
	printf("The element with such index: ");
	printf("%d\n", l);
}


int main()
{
	int n, x, k;
	printf("Enter the size of array: ");
	scanf("%d", &n);
	int *A = (int*)malloc(n*sizeof(int));
	for (int i = 0; i < n; i++)
	{
		A[i] = 0;
	}
	printf("Enter the number, which you want to add: ");
	scanf("%d", &x);
	push_back(x, A, n);
	n++;
	printf("Enter the index of the number, which you want to get: ");
	scanf("%d", &k);
	get_element(k, A, n);
	free(A);
	system("pause");
	return 0;
}