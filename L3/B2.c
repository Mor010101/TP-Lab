//P2

#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)


int main()
{
	int n, i = 1, k = 0, *p = (int*)malloc(sizeof(int)), msb = 1 << (8 * sizeof(int) - 1);
	int *temp;//not a new pointer, temporary mem address 
	printf("n=");
	scanf("%d", &n);
	for (i = 0; i < 32; i++)
		if ((n << i) & msb)
			printf("1");
		else
			printf("0");
	i = 0;
	printf("\n");
	for (i = 0; i < 32; i++) {
		if ((n << i)  & msb || k != 0) {

			//realocare spatiu
			temp = (int*)realloc(p, (k + 1) * sizeof(int));
			if (temp == NULL) {
				free(p);//should omit this if we want to keep data, for this application it wouldn't make sense
				printf("eroare la alocarea spatiului");
				exit(1);
			}
			else
				p = temp;

			//setare valoare 
			if ((n << i) & msb)
				*(p + k) = 1;
			else
				*(p + k) = 0;
			k++;

		}


	}
	printf("k=%d\n", k);
	for (i = 0; i < k; i++)
		printf("%d", *(p + i));
	free(p);
	/*Din cate stiu, realocarea de memorie pentru fiecare iteratie este ineficienta din punct de vedere al timpului
	  O varianta mai buna si mai simpla ar fi: (dezavantajul este ca functioneaza cu maxim 100 de elem, ocupa spatiu inutil)

		*p=(int*)malloc(100*sizeof(int));

		 //do stuff

		 temp =(int*)realloc(p, (k+1) * sizeof(int));//k=number of elements
			if (temp == NULL) {
				free(p);
				printf("eroare la alocarea spatiului");
				exit(1);
			}
			else
				p = temp;
	*/
	return 0;
}


