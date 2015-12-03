
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>


struct nlist
{
	struct nlist *next;				//указатель на след элемент
	char *name;						//определяемое имя
	char *defn;
};

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE];
struct nlist *Head = hashtab;

//получает код по стрингу
unsigned hash(char *s)
{
	unsigned hashval;
	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}

//ищет s
struct nlist *lookup(char *s)
{
	struct nlist *np;
	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np;					//если нашли
	return NULL;						//если не нашли
}

//заносит (name,defn) в таблицу
int install(char *name, char *defn)
{
	struct nlist *np;
	unsigned hashval;
	np = (struct nlist *)malloc(sizeof(*np));				//выделяем память под новый элемент
	if (np == NULL || (np->name = _strdup(name)) == NULL || (np->defn = _strdup(defn)) == NULL)	//проверяем, выделилась ли память
		return NULL;
	hashval = hash(name);				//индекс массива
	np->next = hashtab[hashval];		//устанавливаем значение в таблицу: сохраняем таблицу, как 
	hashtab[hashval] = np;				//след элемент нашего списка, а новый элемент заносим вперёд.
	return 1;
}

bool deleteVal(char *s)
{
	struct nlist *np;
	struct nlist *save = hashtab[hash(s)];
	np = lookup(s);
	if (np == NULL)			//если не нашлись такого ключа 
	{
		return false;
	}
	else
	{
		if (np == save)							//если ключ первый элемент
		{
			hashtab[hash(s)] = np->next;		//сдвигаем указатель на первый элемент таблицы вперед
		}
		else
		{
			while (save->next != np)			//пока указатель на след элемент не нашёл нужный указатель
			{
				save = save->next;
			}
			save->next = np->next;				//сдвигаем таблицу(её элементы) так, чтобы она забыла про ненужный указатель
		}
		free (np);
		return true;
	}
}

int main()
{
	char s[30];
	int number;
	char value[20];
	printf_s("Enter your string:\n");
	scanf_s("%s", s, 30);
	while (s[0] != '0')
	{
		printf_s("1-install, 2-delete, 3-find\n");
		scanf_s("%i", &number);
		switch (number)
		{
		case 1:
			printf_s("Enter your value:\n");
			scanf_s("%s", value);
			if (install(s, value) == NULL)
			{
				printf_s("This value can not install\n");
			}
			else
			{
				printf_s("This value was install\n");
			}
			break;
		case 2:
			if (deleteVal(s))
			{
				printf_s("succesful\n");
			}
			else
			{
				printf_s("element not found\n");
			}
			break;
		case 3:
			if (lookup(s) != NULL)
			{
				printf_s("%s", lookup(s)->defn);
			}
			else
			{
				printf_s("Key not found\n");
			}
			break;
		}
		while (getchar() != '\n')
		{
			continue;
		}
		printf_s("Enter your string:\n");
		scanf_s("%s", s, 30);
	}
	_getch();
}