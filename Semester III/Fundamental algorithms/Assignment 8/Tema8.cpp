#include<stdlib.h>
#include<stdio.h>


typedef struct node {

	int value;
	struct node* right;
	struct node* left;
}NodeT;

NodeT* create_node(int value)
{
	NodeT* p = (NodeT*)malloc(sizeof(NodeT));
	p->value = value;
	p->right = NULL;
	p->left = NULL;
	return p;
}

int cnt;

NodeT* inserare(NodeT* t, NodeT* root)
{
	if (root == NULL)
		return t;
	else {
		if (root->value > t->value)

			root->left = inserare(t, root->left);

		if (root->value < t->value)

			root->right = inserare(t, root->right);

		return root;


	}
}
/*
void afisare_postordine(NodeT* r)
{
	if (r == NULL)
		return;

	afisare_postordine(r->left);
	afisare_postordine(r->right);
	printf("%d ", r->value);
}

void afisare_inordine(NodeT* r)
{
	if (r == NULL)
		return;
	afisare_inordine(r->left);
	printf("%d ", r->value);
	afisare_inordine(r->right);
}
*/
void afisare_preordine(struct node* r)
{
	if (r == NULL)
		return;
	printf("%d ", r->value);
	afisare_preordine(r->left);
	afisare_preordine(r->right);
}

void cautare_preordine(NodeT* r, int key)
{
	if (r == NULL)
	{
		printf("pe pozitia %d nu s a gasit nod cu valoarea %d\n", cnt, key);
		cnt++;
		return;
	}
	if (r->value == key)
		printf("%d", r->value);
	else {
		cautare_preordine(r->left, key);
		cautare_preordine(r->right, key);
	}
}

void afisare_pretty(NodeT* node, int level)
{
	if (node == NULL)
		return;
	afisare_pretty(node->right, level + 1);
	for (int i = 0; i < level; i++)
		printf("\t");
	printf("%d\n", node->value);
	afisare_pretty(node->left, level + 1);
}


int main()
{
	NodeT* root = NULL;

	root = inserare(create_node(50), root);
	root = inserare(create_node(40), root);
	root = inserare(create_node(60), root);
	root = inserare(create_node(30), root);
	root = inserare(create_node(45), root);
	root = inserare(create_node(65), root);
	root = inserare(create_node(20), root);

	afisare_preordine(root);
	printf("\n\n");
	afisare_pretty(root, 0);

	cautare_preordine(root, 60);

	return 0;
}
