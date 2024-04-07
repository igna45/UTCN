#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

//reprezinta un nod din lista de adiacenta, contine un intreg si pointer la next nod din lista
typedef struct adj_list_node {
    int node;
    struct adj_list_node* next;
} adj_list_node;

//lista de adiacenta si contine un pointer al primului nod din lista
typedef struct adj_list {
    adj_list_node* head;
} adj_list;

//repr un graf, contine un vector de liste de adiacenta, unul pt fiecare nod, si un int pt a stoca nr de noduri din graf
typedef struct graph {
    adj_list adj_lists[MAX_VERTICES];
    int num_nodes;
} graph;


adj_list_node* create_node(int v)
{
    adj_list_node* new_node = (adj_list_node*)malloc(sizeof(adj_list_node));
    new_node->node = v;
    new_node->next = NULL;
    return new_node;
}

void add_edge(graph* g, int src, int dest)
{
    /* add an edge from src to dest */
    adj_list_node* new_node = create_node(dest);
    new_node->next = g->adj_lists[src].head;
    g->adj_lists[src].head = new_node;

    /* add an edge from dest to src */
    new_node = create_node(src);
    new_node->next = g->adj_lists[dest].head;
    g->adj_lists[dest].head = new_node;
    //pt un graf neorientat, am atasat nodul sursa de nodul destinatar, si invers, pt a creea ambele directii pt muchie
}

/* initialize the graph */
void init_graph(graph* g, int num_nodes)
{
    //ini?ializeaz? graficul setând num?rul de vârfuri ?i ini?ialând capul fiec?rei liste de adiacen?? la NULL.
    int i;

    g->num_nodes = num_nodes;

    for (i = 0; i < num_nodes; i++) {
        g->adj_lists[i].head = NULL;
    }
}

/* depth first search */
void dfs(graph* g, int node, int* visited)
{
    adj_list_node* adj_list_ptr = g->adj_lists[node].head;
    visited[node] = 1;
    printf("%d ", node);

    while (adj_list_ptr != NULL) {
        int v = adj_list_ptr->node;
        if (!visited[v]) {
            dfs(g, v, visited);
        }
        adj_list_ptr = adj_list_ptr->next;
    }
}

int main(void)
{
    graph g;
    int num_vertices = 4;

    init_graph(&g, num_vertices);

    add_edge(&g, 0, 1);
    add_edge(&g, 0, 2);
    add_edge(&g, 1, 2);
    add_edge(&g, 2, 0);
    add_edge(&g, 2, 3);
    add_edge(&g, 3, 3);
    int visited[MAX_VERTICES] = { 0 };

    dfs(&g, 2, visited);

    return 0;
}