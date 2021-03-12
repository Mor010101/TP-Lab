//P3

#include<stdio.h>
#include<stdlib.h>
#pragma warning (disable:4996)

void sum(int*rez, int a, int b)
{
	*rez = a + b;
}

int main()
{
	int v[5] = { 11,22,33,44,55 };
	int *a = &v[0] ,i ,b,c ,*rez=(int*)malloc(sizeof(int));
	printf("Vectorul: ");
	for (i = 0; i < 5; i++)
		printf("%d ", v[i]);

	printf("\nIncrementarea valorii pointerului: ");
	printf("p+10=%d\n", *a + 10);
	printf("Dectrementarea valorii pointerului: ");
	printf("p-10=%d\n", *a - 10);
	printf("\nIncrementarea pointerului\n");

	printf("Inainte de incrementare: val=%d, adresa=%x\nDupa incrementare: val=%d, adresa=%x\n", *a, a,*(a+1),a+1 );
	//resetam valoarea pointerului
	a -= 1;
	printf("\nDecrementarea pointerului\n");
	//va returna valori random, am iesit din zona de memorie alocata vectorului
	printf("Inainte de decrementare: val=%d, adresa=%x\nDupa decrementare: val=%d, adresa=%x\n", *a, a, *(a -1), a - 1);

	//am banuit ca "metoda returneaza pointer" inseamna ca functia returneaza valoarea printr-un pointer
	//nu as intelege sensul ca functia in sine sa returneze un pointer
	printf("\nSuma a doua numere:\n");
	printf("a="); scanf("%d", &b);
	printf("b="); scanf("%d", &c);
	sum(rez, b, c);
	printf("Suma=%d", *rez);
	return 0;

}


