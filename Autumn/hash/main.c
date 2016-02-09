#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int key;
	struct Node *next;    // ��������� �������               
} Node;

Node **hashTable;

int hash(int key) {
	return (key % 101);
}

// ������� ������ ��� ����� ���� � ��������� ��� � �������
Node *insertNode(int key) {
	Node *p=NULL, *p0=NULL;
	int bucket;
	// ������� ������� � ������ ������
	bucket = hash(key);
	if ((p = (Node*) malloc(sizeof(Node))) == 0)
	{
		printf("������ (insertNode)\n");
		return NULL;
	}
	p0 = hashTable[bucket];
	hashTable[bucket] = p;
	p->next = p0;
	p->key = key;
	free(p0);
	return p;
}

//������� �������� ������� �� �������
Node *deleteNode(int key) {
	Node *p = NULL, *p0 = NULL;
	int bucket;
	//�����
	p0 = 0;
	bucket = hash(key);
	p = hashTable[bucket];
	while (p && !((p->key) == key)) {
		p0 = p;
		p = p->next;
	}
	if (!p) return;

	if (p0)
		p0->next = p->next;
	else
		hashTable[bucket] = p->next;

	free(p);
	return 1;
}



// �����
	Node *findNode(int key) {
		Node *p = NULL;
	p = hashTable[hash(key)];
	if ((p->key) == key)
	{
		p = p->next;
	return p; 
	}
	else  //���� ���� �� ������
 	{
		return NULL;
	}
}

int main() 
{
	int i, *a, maxnum;
	printf("%s\n", "������� ���������� ���������"); 
	scanf("%d", &maxnum);

	//a = new int[maxnum];
	if ((a = malloc(maxnum * sizeof(*a))) == 0)
	{
		printf("������  (a)\n");
		return NULL;
	}

	if ((hashTable = malloc(101 * sizeof(Node *))) == 0)
	{
		printf("������  (hashTable)\n");
		return NULL;
	}

	for (i = 0; i < 101; i++)
		hashTable[i] = NULL;

	// ��������� �������
	for (i = 0; i < maxnum; i++)
	{
		a[i] = rand();
	}

	// ���������� ���-������� ���������� �������
	for (i = 0; i < maxnum; i++) 
	{
		insertNode(i);
	}

	// ����� ��������� ������� �� ���-�������
	printf("%s\n", "������� �����");
	scanf("%d", &i);
	printf("%d\n",  findNode(a[i]));

	printf("%s\n", "������� ��������");
	scanf("%d", &i);
	deleteNode(a[i]);
	maxnum--;

	return 0;
}
