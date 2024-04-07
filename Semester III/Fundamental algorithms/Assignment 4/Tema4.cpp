#include <stdio.h>
#include <stdlib.h>
#include "Profiler.h";


struct Node
{
    int key;
    struct Node* next;
    struct Node* prev;
};

typedef struct List
{
    Node* head;
    Node* tail;
    int count;
} List;


struct Node* list[500];
struct Node* w;
int v[500];


void afisare_vector(int v[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
}

void afisare_lista(struct Node* node)
{
    while (node != NULL) {
        printf("%d ", node->key);
        node = node->next;
    }
    printf("\n");
}

void insert_last(struct Node** head, int x)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    struct Node* last = *head;
    new_node->key = x;
    new_node->next = NULL;
    if (*head == NULL) {
        new_node->prev = NULL;
        *head = new_node;
        return;
    }
    while (last->next != NULL)
        last = last->next;
    last->next = new_node;
    new_node->prev = last;
    return;
}

void generate(int k, int n)
{
    struct Node* head = NULL;
    int i, j, a;
    int x[500];
    for (i = 0; i < n; i++)
    {
        j = rand() % k;
        v[rand() % k]++;
    }
    printf("Dimensiunile listelor:\n");
    afisare_vector(v, k);
    for (int i = 0; i < n; i++)
    {
        list[i] = NULL;
        FillRandomArray(x, v[i], 5, 100, false, 1);
        for (a = 0; a < v[i]; a++)
        {
            insert_last(&list[i], x[a]);
        }//FillRandomArray()
    }
}

void interclasare(struct Node* node1, struct Node* node2, int n1, int n2)
{
    int i = 0, j = 0;
    while (i < n1 && j < n2)
    {
        if (node1->key < node2->key)
        {
            insert_last(&w, node1->key);
            node1 = node1->next;
            i++;
        }
        else
        {
            insert_last(&w, node2->key);
            node2 = node2->next;
            j++;
        }
    }
    while (i < n1)
    {
        insert_last(&w, node1->key);
        node1 = node1->next;
        i++;
    }
    while (j < n2)
    {
        insert_last(&w, node2->key);
        node2 = node2->next;
        j++;
    }
}

void min_heapify(Node *v[], int n, int i)
{
    int smallest, left, right;
    Node *aux;
    left = 2 * i + 1;
    right = 2 * i + 2;
    smallest = i;
    if (left < n && v[left] < v[i])
        smallest = left;
    if (right < n && v[right] < v[smallest])
        smallest = right;
    if (smallest != i) {
        aux = v[i];
        v[i] = v[smallest];
        v[smallest] = aux;
        min_heapify(v, n, smallest);
    }
}

void heap_sort(Node *v[], int n)
{
    Node *aux;
    for (int i = n / 2 - 1; i >= 0; i--)
        min_heapify(v, n, i);//build heap
    for (int i = n - 1; i >= 0; i--)
    {
        aux = v[0];
        v[0] = v[i];
        v[i] = aux;
        min_heapify(v, i, 0);
    }
}

void build_heap(Node *v[], int n)
{
    int i, j;
    j = (n / 2) - 1;
    for (i = j; i >= 0; i--)
    {
        min_heapify(v, n, i);
    }
}

void KwayMerge(Node *v[], int k)
{
    List* Lout = (List*)malloc(sizeof(List));
    build_heap(v, k);
    //heapsize = k
    while (k > 0)
    {
        if (Lout->tail != NULL)
            Lout->tail->next = v[1];
        else
            Lout->head = v[1];
        Lout->tail = v[1];
        v[1] = v[1]->next;
        if (v[1] == NULL)
        {
            v[1] = v[k];
            k--;
        }
        min_heapify(v, k, 1);
    }
}

void demo()
{
    int k = 4, n = 20, i = 0;
    srand(time(0));//pentru generare random de fiecare data
    printf("Generarea a %d liste ordonate cu %d elemente in total\n", k, n);
    printf("\n");
    generate(k, n);
    for (int i = 0; i < k; i++)
    {
        printf("Lista %d: ", i + 1);
        afisare_lista(list[i]);
    }
    printf("\n");
    printf("Interclasarea a doua liste: \n");
    interclasare(list[0], list[1], v[0], v[1]);
    afisare_lista(w);
   // struct Node *w = 0;
    printf("\n");
    
   // afisare_lista(w);
}

int main()
{
    demo();
    return 0;
}