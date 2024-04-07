#include <stdio.h>
#include <stdlib.h>

typedef struct nodeR2 {
	int key;
	int count;
	struct nodeR2* children[10];
}nodeR2;

nodeR2* rootR2 = NULL;
nodeR2* nodesR2[11];

int parrentArray[11] = { 0, 2, 7, 5, 2, 7, 7, -1, 5, 2 };
int dim = 10;
void arbore_multicai(int* parent_array, int n) 
{
	int i, j;
	for (i = 1; i <= n; i++) 
	{
		nodesR2[i] = (nodeR2*)malloc(sizeof(nodeR2));
		nodesR2[i]->key = i;
		nodesR2[i]->count = 0;
		for (j = 0; j < dim; j++) 
			nodesR2[i]->children[j] = NULL;
	}

	for (i = 1; i < n; i++) 
	{
		if (parent_array[i] == -1) 
			rootR2 = nodesR2[i];
		else 
		{
			nodeR2* child = nodesR2[i];
			nodeR2* parent = nodesR2[parent_array[i]];
			parent->children[parent->count++] = child;//adauga copil in vectorul parinti 
		}
	}
}

void pretty_print_r1(const int* tree, int size, int parent, int level)
{
	for (int i = 0; i != size; ++i)
	{
		if (tree[i] == parent) 
		{
			for (int i = 0; i < level; ++i) 
				printf("\t");
			printf("%d\n", i + 1);
			pretty_print_r1(tree, size, i + 1, level + 1);
		}
	}
}

void pretty_print_r2(nodeR2* root, int level) 
{
	int i;
	if (root != NULL) {
		for (i = 1; i <= level; i++)
			printf("\t");
		printf("%d\n", root->key);
		for (i = 0; i < root->count; i++)
			pretty_print_r2(root->children[i], level + 1);
	}
}

void demo()
{
	int parinti[] = { 2, 7, 5, 2, 7, 7, -1, 5, 2 };
	printf("PARENT REPRESENTATION:\n");
	pretty_print_r1(parinti, 9, -1, 0);
	printf("\n");
	printf("MULTI-WAY REPRESENTATION:\n");
	arbore_multicai(parrentArray, 10);
	pretty_print_r2(rootR2, 0);
	printf("\n\n");
}

int main()
{
	demo();
	return 0;
}