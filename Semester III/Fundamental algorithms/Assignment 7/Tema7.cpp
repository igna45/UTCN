#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct Node
{
	int key;
	Node* left;
	Node* right;
	int size;
};

Node* create_node(int value, int dim)
{
	Node* p = (Node*)malloc(sizeof(Node));
	p->key = value;
	p->right = NULL;
	p->left = NULL;
	p->size = dim;
	return p;
}

Node* inserare(Node* t, Node* root)
{
	if (root == NULL)
		return t;
	else {
		if (root->key > t->key)
			root->left = inserare(t, root->left);
		if (root->key < t->key)
			root->right = inserare(t, root->right);
		return root;
	}
}

void afisare_pretty(Node* node, int level)
{
	if (node == NULL)
		return;
	afisare_pretty(node->right, level + 1);
	for (int i = 0; i < level; i++)
		printf("\t");
	printf("(%d | %d)\n\n", node->key, node->size);
	afisare_pretty(node->left, level + 1);
}

Node* OS_Select(struct Node* root, int i)
{
	if (root != NULL)
	{
		int r;
		if (root->left != NULL)
			r = root->left->size + 1;
		else 
			r = 1;
		if (i == r) 
			return root;
		else
		{
			if (i < r) 
				return OS_Select(root->left, i);
			else 
				return OS_Select(root->right, i - r);
		}
	}
}

void demo()
{
	Node* root2 = NULL;
	//NodeT* a= create_node(50);
	root2 = inserare(create_node(6, 11), root2);
	root2 = inserare(create_node(9, 5), root2);
	root2 = inserare(create_node(3, 5), root2);
	root2 = inserare(create_node(1, 2), root2);
	root2 = inserare(create_node(4, 2), root2);
	root2 = inserare(create_node(7, 2), root2);
	root2 = inserare(create_node(10, 2), root2);
	root2 = inserare(create_node(2, 1), root2);
	root2 = inserare(create_node(5, 1), root2);
	root2 = inserare(create_node(8, 1), root2);
	root2 = inserare(create_node(11, 1), root2);

	afisare_pretty(root2, 0);
	printf("\n");
	int b = 4;
	OS_Select(root2, b);
	printf("Al %d lea cel mai mic nod al arborelui este: %d\n", b, OS_Select(root2, b)->key);
	printf("\n");
	int c = 6;
	OS_Select(root2, c);
	printf("Al %d lea cel mai mic nod al arborelui este: %d\n", c, OS_Select(root2, c)->key);

	printf("\n\n\n\n");
}


int main()
{
	demo();
	return 0;
}