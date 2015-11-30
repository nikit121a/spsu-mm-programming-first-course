#include <stdio.h>
#include <stdlib.h>



int head, a[100], base = 31;


void bin_arr(long long x)//create output
{
	head = -1;
	while (x > 0)
	{
		head++;
		a[head] = x % 2;
		x = x / 2;
	}

}

void cl_arr()//clear array
{
	for (int i = 0; i <= base; i++)
	{
		a[i] = 0;
	}
}


int main()
{
	long long cur_num, num = -756; //Lomakin(7) * Alexander(9 in rus) * Vladimirovich(12 in rus) = 756
	cur_num = num + 4294967296;

	bin_arr(cur_num);

	printf("Int32 represenation: ");

	for (int i = base; i >= 0; i--)
	{
		printf("%d", a[i]);
	}

	printf("\n");

	cl_arr();

	cur_num = -1 * num;

	bin_arr(cur_num);

	int k = 0;

	for (int i = base; i >= 0; i--)
	{
		if (a[i] = 1)
		{
			k = i;
		}
	}

	cl_arr();
	int s = head;

	printf("Float represenation: 1");

	bin_arr(head + 127);
	for (int i = 7; i >= 0; i--)
	{
		printf("%d", a[i]);
	}

	cl_arr();

	bin_arr(cur_num);

	for (int i = head - 1; i >= 0; i--)
	{
		printf("%d", a[i]);
	}
	for (int i = 22; i >= head; i--)
	{
		printf("0");
	}

	printf("\n");
	cl_arr();
	bin_arr(s + 1023);

	printf("Double represenation: 1");
	for (int i = 10; i >= 0; i--)
	{
		printf("%d", a[i]);
	}

	cl_arr();
	bin_arr(cur_num);


	for (int i = head - 1; i >= 0; i--)
	{
		printf("%d", a[i]);
	}


	for (int i = 51; i >= head; i--)
	{
		printf("0");
	}

	_getch();

}