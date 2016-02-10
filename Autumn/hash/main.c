#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	char key[10];
	char value[10];
	struct Node *next;
} node;

typedef struct HashTable
{
	node **table;
	int key;
	int val;
	int size;
	int *length;
	struct Node *next;    // следующая вершина               
} hashTable;

void init(hashTable *h, int size)
{
	h->size = size;
	h->table = (node**)malloc(sizeof(node*) * h->size);
	h->length = (int*)malloc(sizeof(int) * h->size);
	for (int i = 0; i < size; i++)
		h->table[i] = (node*)malloc(sizeof(node));
}

int hash(int key)
{
	return (key % 101);
}

void inserthash(hashTable *h, int *key, int *value);
newhash(hashTable *h)
{
	hashTable nh;
	init(&nh, h->size);
	for (int i = 0; i < h->size; i++)
	{
		inserthash(&nh, h->table[i]->key, h->table[i]->value);
	}
	h = &nh;
	return;
}


void *findhash(hashTable *h, int *key)
{
		node *p;
		p = h->table[hash(key)];
		do {
			if ((p->key) == key) return p;
			else p = p->next;
		} while (p != NULL);
	return -1;
}

// отводит память под новый узел и вставляет его в таблицу
void inserthash(hashTable *h, int *key, int *value)
{
	hashTable *p;
	int bucket = hash(key);
	p = (hashTable*)malloc(sizeof(hashTable));
	p->key = key;
	p->val = value;
	p->next = NULL;
	h->table[bucket] = p;
	h->length[bucket]++;
	if (h->length[bucket] > 5)
	{
		newhash(h);
		return;
	}
}

//функция удаления вершины из таблицы
void deletehash(hashTable *h, int key)
{
	hashTable *p;
	if (findhash(key, &p))
	{
		int bucket = hash(key);
		h->table[bucket] = p->next;
		free(p);
	}
}



int main()
{
	hashTable hash;
	int size = 6;
	init(&hash, size);
	inserthash(&hash, 5, 6);
	findhash(&hash, 6);
	deletehash(&hash, 5);
	
	return 0;
}
