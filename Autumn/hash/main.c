#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	char key;
	char value;
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

void *inserthash(hashTable *h, int *key, int *value);

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


void *findhash(hashTable *h, int key)
{
	node *p;
	int bucket = hash(key);
	p = h->table[bucket];
	while (p != NULL)
	{
		if ((p->key) == key) return p;
		else p = p->next;
	}
	return -1;
}

// отводит память под новый узел и вставляет его в таблицу
void *inserthash(hashTable *h, int *key, int *value)
{
	int bucket = hash(key);
	h->table[bucket]->value = value;
	h->table[bucket]->next = NULL;
	h->table[bucket]->key = key;
	h->length[bucket]++;
	if (h->length[bucket] > 5)
	{
		h->size++;
		newhash(h);
		return;
	} 
	return h->table[bucket];
}

//функция удаления вершины из таблицы
void *deletehash(hashTable *h, int key)
{
	int bucket = hash(key);
	h->table[bucket]->key = NULL;
	h->table[bucket]->next = NULL;
	h->table[bucket]->value = NULL;
	h->length[bucket]--;
	return h->table[bucket];
}

void deletehashtable(hashTable *h)
{
	for (int i = 0; i < h->size; i++)
		free(h->table[i]);
	free(h->table);
	free(h->length);
	return;
}


int main()
{
	hashTable hash;
	int size = 6;
	init(&hash, size);
	node *p = inserthash(&hash, 5, 6);
	printf("insert key %d and value %d \n", p->key, p->value);
	p = findhash(&hash, 5);
	printf("find for key 5 value %d \n", p->value);
	p = deletehash(&hash, 5);
	printf("delete for key 5. Now key %d and value  %d \n",  p->key, p->value);
	deletehashtable(&hash);
	printf("delete all");

	return 0;
}
