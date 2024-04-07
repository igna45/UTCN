#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct table
{
    int* v;
    int n;
}table;

int DELETED;

table* create_table(int n)
{
    table* t = (table*)malloc(sizeof(table));
    t->n = n;
    t->v = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < t->n; i++)
        t->v[i] = -1;
    return t;
}

void afisare(table* t)
{
    printf("\n");
    for (int i = 0; i < t->n; i++)
        printf("%d %d\n", i, t->v[i]);
}


int verificare_patratica(int i, int k, int m)
{
    return ((k + 10)+ (2 * i) + (i * i)) % m;
}

int insert_table(table* t, int key)
{
    int i = 0;
    do
    {
        int j = verificare_patratica(i, key, t->n);
        if (t->v[j] == -1)
        {
            t->v[j] = key;
            return j;
        }
        else i++;
    } while (i != t->n);
    return -1;
}

int search_table(table* t, int key)
{
    int i = 0, j;
    do {
        j = verificare_patratica(i, key, t->n);
        if (t->v[j] == key)
            return j;//slot ce contine key k
        i++;
    } while (t->v[j] != -1 && i != t->n);
    return -1;
}

int delete_table(table* t, int key)
{
    int i = 0, j;
    do {
        j = verificare_patratica(i, key, t->n);
        if (t->v[j] == key)
        {
            t->v[j] = -1;//slot ce contine key k
            return j;
        }
         i++;
    } while (t->v[j] != -1 && i != t->n);
    return -1;
}


void demo()
{
    table* t = create_table(30);
    printf("Tabela inainte de inserare:\n");
    afisare(t);
    insert_table(t, 19);
    insert_table(t, 36);
    insert_table(t, 5);
    insert_table(t, 21);
    insert_table(t, 4);
    insert_table(t, 26);
    insert_table(t, 14);
    insert_table(t, 10);
    insert_table(t, 34);
    insert_table(t, 56);
    insert_table(t, 43);
    insert_table(t, 12);
    insert_table(t, 65);
    insert_table(t, 37);
    insert_table(t, 29);
    insert_table(t, 50);
    insert_table(t, 16);
    insert_table(t, 41);
    insert_table(t, 9);
    insert_table(t, 7);
    insert_table(t, 6);
    insert_table(t, 2);
    insert_table(t, 94);
    insert_table(t, 21);
    insert_table(t, 87);
    insert_table(t, 92);
    insert_table(t, 20);
    insert_table(t, 28);
    insert_table(t, 76);
    insert_table(t, 89);
    printf("\nTabela dupa inserare:\n");
    afisare(t);
    printf("\n");
    int a = search_table(t, 43);
    printf("Valoarea key 43 se afla pe pozitia %d\n", a);

    delete_table(t, 43);
    printf("\nTabela dupa stergerea unei valori:\n");
    afisare(t);
    a = search_table(t, 43);
    if (a != -1)
        printf("\nValoarea key 43 se afla pe pozitia %d\n", a);
    else
        printf("\nValoarea 43 nu exista in tabela de dispersie\n");
    insert_table(t, 44);
    afisare(t);
}

int main()
{
    demo();
    return 0;
}