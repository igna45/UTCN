#include <stdio.h>
#include "Profiler.h"

Profiler pp("quick");

#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NR_TEST 5

int partition(int v[], int p, int r, Operation opComp, Operation opAttr)
{
	int x = v[p];
	int i = p - 1;
	int j = r + 1;
	int aux;

	while (i <= j)
	{
		do
			j--;
		while (v[j] > x);
		do
			i++;
		while (v[i] < x);
		opComp.count();
		if (i < j)
		{
			opAttr.count(3);
			aux = v[i];
			v[i] = v[j];
			v[j] = aux;
		}
		else
			return j;
	}
}

void quick_sort(int v[], int p, int r, Operation opComp, Operation opAttr)
{

	int x = v[p];
	int i = p - 1;
	int j = r + 1;

	if (p < r)
	{
		int q = partition(v, p, r, opComp, opAttr);
		quick_sort(v, p, q, opComp, opAttr);
		quick_sort(v, q + 1, r, opComp, opAttr);
	}
}


void print(int v[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", v[i]);
}

void perf()
{
	int p = 1, r = 0, test = 0;
	int j = r + 1;
	int v[MAX_SIZE];
	Operation opAttr = pp.createOperation("attr", r);
	Operation opComp = pp.createOperation("comp", r);

	for (j = STEP_SIZE - 1; j <= MAX_SIZE; j += STEP_SIZE)
	{
		for (test = 0; test <= NR_TEST; test++)
		{
			FillRandomArray(v, j);
			quick_sort(v, 0, j, opComp, opAttr);
		}
	}

	pp.divideValues("comp", NR_TEST);
	pp.divideValues("attr", NR_TEST);

	pp.addSeries("quick", "comp", "attr");
	pp.showReport();
}

void demo()
{
	int v[] = { 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 };
	int n = sizeof(v) / sizeof(v[0]);
	Operation opAttr = pp.createOperation("attr", n);
	Operation opComp = pp.createOperation("comp", n);
	quick_sort(v, 0, n - 1, opComp, opAttr);
	printf("Dupa quicksort, sirul va fi: ");
	print(v, n);
}

int main()
{
	demo();
	//perf();
	return 0;
}