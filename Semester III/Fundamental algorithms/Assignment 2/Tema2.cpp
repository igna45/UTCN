#include <iostream>

using namespace std;

void heapify(int v[], int n, int i)
{
    int largest, left, right, aux;
    left = 2 * i +1;
    right = 2 * i + 2;
    if (left < n && v[left] > v[i])
        largest = left;
    else
        largest = i;
    if (right < n && v[right] > v[largest])
        largest = right;
    if (largest != i) {
        aux = v[i];
        v[i] = v[largest];
        v[largest] = aux;
        heapify(v, n, largest);
    }
}

void heap_sort(int v[], int n)
{
    int aux;
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(v, n, i);//build heap
    for (int i = n - 1; i >= 0; i--)
    {
        aux = v[0];
        v[0] = v[i];
        v[i] = aux;
        heapify(v, i, 0);
    }
}

void bottom_up_build(int v[], int n)
{
    int i, j;
    j = (n / 2) - 1;
    for (i = j; i >= 0; i--)
    {
        heapify(v, n, i);
    }
}

void print(int v[], int n)
{
    for (int i = 0; i < n; i++)
        cout << v[i] << " ";
}

//demo
void demo()
{
    int v1[] = { 4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    int n = sizeof(v1) / sizeof(v1[0]);   
    int v2[50]{};
    for (int i = 0; i < n; i++) {
        v2[i] = v1[i];
    }
    bottom_up_build(v1, n);
    cout << "Dupa bottom-up build, sirul va fi: ";
    print(v1, n);
    cout << "\n";
    cout << endl;
    heap_sort(v2, n);
    cout << "Dupa heap_sort, sirul va fi: ";
    print(v2, n);
    cout << endl;
}

int main()
{
    demo();
    return 0;
}