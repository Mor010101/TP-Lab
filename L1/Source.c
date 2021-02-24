#include<stdio.h>
#include<stdlib.h>
#define varname(name) #name
#define citireD(x)  printf("%s=",varname(x)); scanf("%d",&x)

int* cmp_n(const void*a, const void*b)
{
	//this works as well
	/*
	const int*ia = (const int*)a;
	const int*ib = (const int*)b;
	return(*ia-*ib);
	*/
	//simplified version
	return(*(int*)a - *(int*)b);
}

void lin_search(int *v,int n)
{
	int i,tok;
	printf("introduceti elementul cautat:");
	scanf("%d", &tok);
	for (i = 0; i < n; i++) 
		if (v[i] == tok) {
			printf("Elementul %d se afla pe pozitia %d\n", tok, i);
			i = -1;
			break;
		}
	if (i != -1)
		printf("Elementul cautat nu exista\n");
	
}

int bin_search(int*v, int l, int r, int tok)
{
	int m;
	if (r >= l) {
		m = l + (r - l) / 2;
		
		if (tok == v[m]) 
			return m;
		if (tok < v[m])
			return bin_search(v, l, m - 1, tok);
		if (tok > v[m])
			return bin_search(v, m + 1, r, tok);
	}
	return -1;

}

int interpol(int*v, int l, int r, int tok)
{
	int pos;
	//conditia asta se poate implementa si la cautarea binara pentru a o optimiza
	if (r >= l && tok>=v[l] &&tok<=v[r]) {
		//am atasat in folderul cu fisierul "Source.c" metoda prin care se ajunge la formula asta
		//pe scurt se porneste de la formula generala a unui element intr-un sir ordonat omogen (y=m*i+c)
		pos = (tok - v[l])*(r - l) / (v[r] - v[l]) + l;

		if (tok == v[pos])
			return pos;
		if (tok < v[pos])
			return bin_search(v, l, pos - 1, tok);
		if (tok > v[pos])
			return bin_search(v, pos + 1, r, tok);
	}
	return -1;

}


int main()
{
	int *v,i=0,n,opt=1,El_cautat;
	citireD(n);
	v = (int*)malloc(n*sizeof(int)+1);
	for (i = 0; i < n; i++)
		scanf("%d", &v[i]);
	
	qsort(v, n, sizeof(v), cmp_n);

	
	do {
		printf("0.Iesire\n1.Cautare liniara\n2.Cautare binara\n3.Cautare prin interpolare\n");
		citireD(opt);
		switch (opt) {
		case 0:
			free(v);
			break;
		case 1:
			lin_search(v, n);
			break;
		case 2:
			citireD(El_cautat);
			i=bin_search(v, 0, n - 1, El_cautat);
			if (i != -1)
				printf("Elementul %d se afla pe poz %d\n", El_cautat, i);
			else
				printf("Elementul %d nu exista\n", El_cautat);
			break;
		case 3:
			citireD(El_cautat);
			i = interpol(v, 0, n - 1, El_cautat);
			if (i != -1)
				printf("Elementul %d se afla pe poz %d\n", El_cautat, i);
			else
				printf("Elementul %d nu exista\n", El_cautat);
			break;

		}
	} while (opt);
	return 0;
}
