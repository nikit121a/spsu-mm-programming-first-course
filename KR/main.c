#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* d;
int* new_d;
int size_d = 3, head = 0;


void put(int buffer)
{
	if(head == size_d)
	{
		new_d = (int*)malloc(sizeof(int) * size_d * 2);
		memset(new_d, 0, 8 * size_d);
		size_d *= 2;
		for (int i = 0; i < head; i++)
		{
			new_d[i] = d[i];
		}
		printf("\nNew size: %d\n", size_d);
		d = new_d;
	} 

	d[head] = buffer;
	head++;
	return;
}


int main()
{
	int size_d = 3;
	d = (int*)malloc(sizeof(int) * size_d);
	int action_num = 0;
	int buffer;
	
	while (action_num != 3)
	{
		printf("1 - add, 2 - get, 3 - exit: ");
		scanf("%d", &action_num);
		switch (action_num)
		{
		case 1:
			printf("Num: ");
			scanf("%d", &buffer);
			put(buffer, &head, &size_d);
			break;
		case 2:
			printf("Index: ");
			scanf("%d", &buffer);
			if (buffer < head)
			{
				printf("%d\n", d[buffer]);
			}
			else
			{
				printf("-1\n");
			}
			break;
		case 3:
			free(d);
			printf("");
			break;
		default:
			printf("Input the valid key\n");
			break;
		}
			
	}
	return 0;
}