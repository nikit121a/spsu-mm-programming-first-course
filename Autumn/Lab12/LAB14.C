/*Leonid Voroshilov, 143*/
#define _CRT_SECURE_NO_WARNINGS 
#define FREE 0
#define FILL 1

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

typedef struct tagList List;
struct tagList
{
	void * ptr;
	int type;
	unsigned int size;
	List *Next, *Prev;
};


#define MEM_SIZE 1000 

List * ptrs;
int NUM;

void * BULK;

void init()
{
	BULK = malloc(MEM_SIZE * sizeof(char));
	ptrs = (List *)malloc(sizeof(List));

	if (BULK == NULL)
	{
		printf("Memory allocation error!\n");
		return;
	}

	ptrs->Prev = NULL;
	ptrs->Next = NULL;
	ptrs->ptr = BULK;
	ptrs->type = FREE;
	ptrs->size = MEM_SIZE;

	NUM = 1;
}
void listDelete(List * ptr)
{
	if (ptr == NULL)
		return;
	listDelete(ptr->Next);
	free(ptr);
}
void deinit()
{
	free(BULK);
	listDelete(ptrs);

}

void * myMalloc(size_t size)
{
		List *tmp = ptrs;

		while ((tmp->type != FREE) && (tmp->size < size))
		{
				tmp = tmp->Next;
				if (tmp == NULL)
					return NULL;
		}

		tmp->type = FILL;
		if (tmp->size > size)
		{
			if (tmp->Next == NULL)
			{
				tmp->Next = malloc(sizeof(List));
				if (tmp->Next == NULL)
					return NULL;
				tmp->Next->Prev = tmp;
				tmp->Next->ptr = (char * )tmp->ptr + size;
				tmp->Next->Next = NULL;
				tmp->Next->size = tmp->size - size;
				tmp->size = size;
				tmp->Next->type = FREE;
				
				return tmp->ptr;
			}
			else
			{
				if (tmp->Next->type == FILL)
				{

					List * a = (List * )malloc (sizeof(List));
					if (a == NULL)
						return NULL;

					a->Prev = tmp;
					a->Next = tmp->Next;
					a->ptr = (char *)tmp->ptr + size;
					a->size = tmp->size - size;
					a->type = FREE;
					tmp->size = size;
					tmp->Next->Prev = a;
					tmp->Next = a;
					return tmp->ptr;
				}
				else
				{
					tmp->Next->size = tmp->Next->size + tmp->size - size;
					tmp->Next->ptr = (char *)tmp->Next->ptr - size;
					tmp->size = size;
					return tmp->ptr;
				}
			}

		}
		return tmp->ptr;
}

void myFree(void *ptr)
{
	List * tmp = ptrs;

	while (tmp != NULL)
	{
		if (ptr >= tmp->ptr && ptr <= (char *)tmp->ptr + tmp->size)
		{
			tmp->type = FREE;
			ptr = NULL;
			//trashcleaner();
			return;
		}
		else
			tmp = tmp->Next;
	}
}

void trashcleaner(void)
{
	List * tmp = ptrs;
	if (tmp->Next == NULL)
		return;
	while (tmp->Next != NULL)
	{
		if (tmp->type == FREE && tmp->Next->size == FREE)
		{
			List *l = tmp->Next;
			tmp->size += l->size;
			tmp->Next = l->Next;
			l->Next->Prev = tmp;
			free(l);
		}
            tmp = tmp->Next;
	}
}

void * myRealloc(void *ptr, int size)
{
	List * tmp = ptrs;
	int delta;


	if (ptr == NULL)
		return myMalloc(size);
	else if (size == 0)
	{
		myFree(ptr);
		return NULL;
	}

	while (tmp != NULL)
	{
		if (ptr >= tmp->ptr && ptr <= (char *)tmp->ptr + tmp->size)
		{
			delta = (char*)ptr - tmp->ptr;
			if (size > tmp->size)
			{
				if (tmp->Next != NULL && tmp->Next->type == FREE && tmp->size + tmp->Next->size >= size)
				{
					tmp->Next->size = tmp->Next->size - (size - tmp->size);
					tmp->Next->ptr = (char *)tmp->Next->ptr + (size - tmp->size);
					tmp->size = size;
					return ptr;
				}
				else if (tmp->Prev != NULL && tmp->Prev->type == FREE && tmp->size + tmp->Prev->size >= size)
				{
					int size_d = tmp->Prev->size - size;
					if (size_d >= 0)
					{
						memcpy(tmp->Prev->ptr, tmp->ptr, tmp->size);
						tmp->ptr = (char *)tmp->ptr - size_d;
						tmp->Prev->type = FILL;
						tmp->type = FREE;
						tmp->size = tmp->size + size_d;
						trashcleaner();
						return (char *)tmp->Next->ptr + delta;
					}
					else
					{
						memcpy(tmp->Prev->ptr, tmp->ptr, tmp->size);
						tmp->ptr = (char *)tmp->ptr - (tmp->Prev->size - tmp->size) + size;
						tmp->size = tmp->size - (tmp->Prev->size - tmp->size);
						tmp->Prev->type = FILL;
						tmp->type = FREE;
						trashcleaner();
						return (char *)tmp->Prev->ptr + delta;
					}
				}
				else
				{
					List *r = ptrs, *m = malloc(sizeof(List));

					while (r != NULL)
					{
						if (r->size >= size && r->type == FREE)
							break;
						r = r->Next;
					}

					if (r == NULL)
						return NULL;

					tmp->type = FREE;
					r->type = FILL;
					if (r->size - size > 0)
					{
						m->type = FREE;
						m->Prev = r;
						m->Next = r->Next;
						m->ptr = (char *)r->ptr + size;
						m->size = r->size - size;
						if (r->Next != NULL)
						{
							r->Next->Prev = m;
						}			
						r->Next = m;
						r->size = size;
					}
					memcpy(r->ptr, tmp->ptr, tmp->size);
					trashcleaner();
					return (char * )r->ptr + delta;
				}
			}
			else
			{
				List *m = malloc(sizeof(List));
				m->Next = tmp->Next;
				m->Prev = tmp;
				m->ptr = (char *)tmp->ptr + (tmp->size - size);
				m->size = (tmp->size - size);
				m->type = FREE;
				tmp->Next->Prev = m;
				tmp->Next = m;
				tmp->size = size;
				trashcleaner();
				return ptr;
			}
		}
		else
			tmp = tmp->Next;
	}
	return NULL;
}




void main(void)
{
	int* mas;
	char * mem;
	init();
	mas = myMalloc(sizeof(int) * 2);
	mem = myMalloc(sizeof(char) * 20);

	mas[0] = 2;
	mas[1] = 52;
	myRealloc(&mas[1], sizeof(int)* 4);
	myFree(&mas[3]);
        deinit();
}