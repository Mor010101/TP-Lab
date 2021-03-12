//P1

#include<stdio.h>
#include<stdlib.h>
#pragma warning (disable:4996)

#define varname(name) #name
#define citireD(x) printf("%s=",varname(x)); scanf("%d",&x)

void *Vsum(int*v, int*rez)
{
	int *i = v,*n=(v+*rez);
	*rez = 0;
	while (i != n) {
		*rez += *i;
		i++;
	}

}

void interschimbare(int* a, int* b)
{
	int *aux=(int*)malloc(sizeof(int));
	*aux = *a;

	*a = *b;
	*b = *aux;
	free(aux);
}

int main()
{
	//problema nu specifica daca vectorul este alocat static sau dinamic
	int n, i, *v = (int*)malloc(sizeof(int)), *s=calloc(1,sizeof(int)),*a,*b;
	a = (int*)malloc(sizeof(int));
	b = (int*)malloc(sizeof(int));
	citireD(n);

	v = (int*)realloc(v, n * sizeof(int));
	for (i = 0; i < n; i++) {
		scanf("%d", (v + i));
		*s += *(v + i);
	}
	printf("Suma=%d\n", *s);
	*s = n;
	Vsum(v, s);

	printf("Suma prin functie=%d\n", *s);
	free(v);
	free(s);
	printf("\nInterschimbarea valorilor:\n");
	citireD(*a);
	citireD(*b);
	interschimbare(a, b);
	printf("a=%d b=%d\n", *a, *b);
	return 0;
}
