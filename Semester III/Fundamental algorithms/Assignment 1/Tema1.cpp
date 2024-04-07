#include <stdio.h>
#include "Profiler.h"

Profiler p("select");

#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NR_TEST 5

void selection_sort(int v[], int n)
{
	Operation opComp = p.createOperation("comp-sel", n);
	Operation opAttr = p.createOperation("attr-sel", n); 

	int p_min = 0, i, j, aux;
	for (i = 0; i < n; i++)
	{
		p_min = i;
		for (j = i + 1; j < n; j++)
		{ 	opComp.count();
			if (v[j] < v[p_min])
				p_min = j;
		}
		opComp.count();
			if (p_min != i)
			{
				opAttr.count();
				aux = v[i];
				opAttr.count();
				v[i] = v[p_min];
				opAttr.count();
				v[p_min] = aux;
			}
	}
}

//demo

void demo()
{
	int v[] = { 7, 2, 2, 7, 8, 5, 9, 9, 1, 6 };
	int n = sizeof(v) / sizeof(v[0]);

	selection_sort(v, n);
	for (int i = 0; i < n; i++)
		printf("%d ", v[i]);
}

void perf()
{
	int v[MAX_SIZE];
	int n;
	for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
	{
		for (int test = 0; test < NR_TEST; test++)
		{
			FillRandomArray(v, n);
			selection_sort(v, n);
		}
	}

	p.divideValues("comp-sel", NR_TEST);
	p.divideValues("attr-sel", NR_TEST);

	p.createGroup("atr", "attr-sel");
	p.createGroup("comp", "comp-sel");
	p.createGroup("efort total", "comp-sel", "attr-sel");

	p.showReport();
}

int main()
{
	demo();
	//perf();
	return 0;
}