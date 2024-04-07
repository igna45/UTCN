#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

struct Node
{
	Node* parent;
	int rank;
	int key;
};

Node* create_node(int value)
{
	Node* p = (Node*)malloc(sizeof(Node));
	p->key = value;
	p->rank = 0;
	p->parent = NULL;
	return p;
}

void make_set(Node* x)
{
	x->parent = x;
	x->rank = 0;
}

void link(Node* x, Node* y)
{
	if (x->rank > y->rank)
		y->parent = x;
	else 
		x->parent = y;
	if (x->rank == y->rank)
		y->rank++;
}

Node* find_set(Node* x)
{
	if (x != x->parent)
		x->parent = find_set(x->parent);
	return x->parent;
}

void union_set(Node* x, Node* y)
{
	link(find_set(x), find_set(y));
}

void same_components(Node* u, Node* v)
{
	if (find_set(u) == find_set(v))
		printf("egale");
	else printf("diferite");
}

void demo()
{
	Node* v[20];
	for (int i = 1; i <= 16; i++)
	{
		v[i] = create_node(rand() % 100 + 1);
		make_set(v[i]);
	}
	for (int i = 1; i <= 16; i++)
	{
		printf("%d cu rank %d si parinte %d\n", v[i]->key, v[i]->rank, v[i]->parent->key);
	}
	printf("\n\n");
	
	for (int i = 1; i <= 15; i = i + 4)
	{
		union_set(v[i], v[i + 2]);
	}
	
	//printf("\nbariera\n");
	for (int i = 1; i <= 16; i++)
	{
		printf("%d cu rank %d si parinte %d\n", v[i]->key, v[i]->rank, v[i]->parent->key);
	}
	printf("\n");
	same_components(v[5], v[7]);
	printf("\n");
	same_components(v[1], v[2]);
	printf("\n");
}

int main()
{
	demo();
	return 0;
}