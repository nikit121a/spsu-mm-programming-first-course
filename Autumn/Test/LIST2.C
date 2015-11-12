/* Leonid Voroshilov, 143 */ 
#include <stdlib.h>
#include <stdio.h>

typedef struct tagList List;

struct tagList 
{
  int Num;
  List *Next, *Prev;
};


int ListDisplay (List *L)
{
  int c = 0;
  List *ptr = L;
  if(L == NULL)
  {
    printf("Empty List");
  }
  else
  {
    while (L->Prev != NULL )
      L = L->Prev;

    while(L != NULL)
    {
      printf("%i ", L->Num);
      L = L->Next;
      c++;
    }
  }
  return c;
}


int ListAddToEnd (List **L, int Data)
{
  List *end = NULL;

  while(*L != NULL)
  {
    end = *L;
    L = &(*L)->Next; 
  }
  
  if((*L =(List *) malloc(sizeof(List))) == NULL)
    return 0;

  (*L)->Prev = end;
  (*L)->Next = NULL;
  (*L)->Num = Data;
  return 1;
}

int main (void)
{
	List *Start = NULL;
	int flag = 1;
	int tmp;
	char q;
	while(flag)
	{
		ListDisplay(Start);
		printf("\n 0 - exit \n 1 - add new item\n >>");

	
		scanf("%c", &q);

		switch(q)                          
		{
		case '0':
		  flag = 0;
		  break;
    
		case '1':
		  printf("Input your number: ");
		  scanf("%i", &tmp);
		  if (ListAddToEnd(&Start,tmp))
			printf("\nAll is correct!\n");
		  else
			printf("\nOperation has been failed! \n");
		  break;

		default:
			break;
		}
		scanf("%c", &q);
	}
	return 0;
}