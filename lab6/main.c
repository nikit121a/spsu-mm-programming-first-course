#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 101
#define FACTOR 7

typedef struct _KeyValue
{
	char *key;
	int value;
} KeyValue;

typedef struct _ListNode
{
	struct _ListNode *next;
	KeyValue data;
} ListNode;

typedef struct _List
{
	ListNode *head;
} List;

typedef struct _HastTable
{
	List *array;
	int arraySize;
	int elementsCount;
} HashTable;


HashTable *createHashTable()
{
	HashTable *table = (HashTable *)malloc(sizeof(HashTable));
	table->array = (List *)malloc(sizeof(List) * SIZE);

	table->elementsCount = 0;
	for (int i = 0; i < SIZE; i++)
	{
		table->array[i].head = NULL;
	}
	table->arraySize = SIZE;
}

int getHash(const char *key, int module)
{
	int length = strlen(key);
	int hash = 0;
	int currentFactor = 1;
	for (int i = 0; i < length; i++)
	{
		hash = (hash + ((FACTOR * currentFactor) % module) * (key[i] % module) % module) % module;
		currentFactor = (FACTOR * currentFactor) % module;
	}
	return hash;
}

void addToArray(List *array, int arraySize, const char *key, int value)
{
	int hash = getHash(key, arraySize);

	ListNode *node = (ListNode*)malloc(sizeof(ListNode));
	node->next = NULL;

	char *newKey = (char*)malloc(sizeof(char) * (strlen(key) + 1));
	strcpy(newKey, key);
	node->data.key = newKey;
	node->data.value = value;

	ListNode *next = array[hash].head;
	array[hash].head = node;
	node->next = next;
}

void removeNode(ListNode *node)
{
	free(node->data.key);
	free(node);
}

void recreateHashTable(HashTable *table)
{
	int newSize = table->arraySize + SIZE;
	List *newArray = (List *)malloc(sizeof(List) * newSize);
	for (int i = 0; i < newSize; i++)
	{
		newArray[i].head = NULL;
	}
	for (int i = 0; i < table->arraySize; i++)
	{
		if (table->array[i].head)
		{
			ListNode *currentNode = table->array[i].head;
			while (currentNode)
			{
				ListNode *next = currentNode->next;
				addToArray(newArray, newSize, currentNode->data.key, currentNode->data.value);
				removeNode(currentNode);
				currentNode = next;
			}
		}
	}

	free(table->array);
	table->array = newArray;
	table->arraySize = newSize;
}

int set(HashTable *table, const char *key, int value)
{
	int hash = getHash(key, table->arraySize);

	ListNode *currentNode = table->array[hash].head;
	if (currentNode)
	{
		while (currentNode)
		{
			if (!strcmp(key, currentNode->data.key))
			{
				currentNode->data.value = value;
				return 1;
			}
			currentNode = currentNode->next;
		}
	}

	table->elementsCount++;
	addToArray(table->array, table->arraySize, key, value);
	if ((double)table->elementsCount / table->arraySize > 0.8)
	{
		recreateHashTable(table);
	}
	return 1;
}


int get(HashTable *table, const char *key, int *result)
{
	int hash = getHash(key, table->arraySize);
	ListNode *currentNode = table->array[hash].head;
	while (currentNode)
	{
		if (!strcmp(key, currentNode->data.key))
		{
			*result = currentNode->data.value;
			return 1;
		}
		currentNode = currentNode->next;
	}
	return 0;
}

int removeItem(HashTable *table, const char *key)
{
	int hash = getHash(key, table->arraySize);
	ListNode *currentNode = table->array[hash].head;
	ListNode *previousNode = table->array[hash].head;


	while (currentNode)
	{
		if (!strcmp(key, currentNode->data.key))
		{
			ListNode *next = currentNode->next;
			removeNode(currentNode);
			previousNode->next = next;
			table->elementsCount--;
			return 1;
		}
		previousNode = currentNode;
		currentNode = currentNode->next;
	}
	return 0;
}

void destroyHashTable(HashTable *table)
{
	for (int i = 0; i < table->arraySize; i++)
	{
		ListNode *currentNode = table->array[i].head;

		while (currentNode)
		{
			ListNode *next = currentNode->next;
			removeNode(currentNode);
			currentNode = next;
		}
	}
	free(table->array);
	free(table);
}

int main()
{
	HashTable *map = createHashTable();
	set(map, "Fluttershy", 2);
	set(map, "Rainbow_Dash", 3);
	set(map, "Twilight_Sparkle", 4);
	set(map, "Applejack", 5);
	set(map, "Rarity", 6);
	set(map, "Pinkie_Pie", 7);
	set(map, "Pony", 100);
	int result;
	int temp = get(map, "Pony", &result);
	printf("%d", result);
	destroyHashTable(map);
	return 0;
}