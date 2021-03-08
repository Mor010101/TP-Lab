/*
Pentru uint32max nu produce nici una dintre variante un raspuns in timp rezonabil, pentru numere de dimensiunea aia am atasat si o versiune
care foloseste Pthreads (B7_Pthread.c) + lib,bin,dll necesare pentru pthreads
*/


#include<stdio.h>
#include<time.h>
#include<stdint.h>
#pragma warning(disable:4996)


const uint32_t m1 = 0x55555555;
const uint32_t m2 = 0x33333333;
const uint32_t m4 = 0x0f0f0f0f;
const uint32_t m8 = 0x00ff00ff;
const uint32_t m16 = 0x0000ffff;

static uint8_t valBit[65536];//65536- in binar este 16 de 1

void afis_bin(int n)
{
	int i;
	for (i = 31; i >= 0; i--) {
		
		printf("%d", (n >> i) & 1);
		if (i % 4 == 0)
			printf(" ");
	}
	printf("\n");
}


//C nu are functie predefinita __builtin_popcount() sau cel putin nu am gasit un library care sa o contina

int popCount(int x)
{
	
	//pune nr de '1' aflati pe doi biti in acei doi biti ai numarului
	x -= (x >> 1) & m1;             
	//sunt luate doua cate doua celule de 2 biti,adunate si rezultatul este stocat pe 4 biti
	x = (x & m2) + ((x >> 2) & m2); 
	//la fel doar ca avem celule de 4 biti, nr stocat pe 8 biti
	x = (x + (x >> 4)) & m4;        
	
	//stocheaza in ultimii 8 biti ai jumatatilor de cate 16 biti, nr de biti specificat de cele doua jumatati
	//this explanation is going downhill fast
	x += x >> 8;  
	//stocheaza in ultimii 8 biti suma count-urilor de la pasul anterior(ultimii opt biti din primii 16 biti, ultimii opt biti ai lui x)
	x += x >> 16; 
	//afis_bin(x);
	//returneaza nr-ul constituit din ultimii 8 biti, unde se afla nr-ul total de biti
	return x & 0x7f;
	
}

void BitwiseTableTool(void)
{
	FILE *f;
	int i;
	f = fopen("bitTable.bin", "wb");
	for (i = 0; i < 65536; i++)
		valBit[i] = popCount(i);
	fwrite(valBit, sizeof(uint8_t), 65536, f);
	fclose(f);
}

int popCountMem(int x)
{
	//tabelul are in memorie doar nr de biti pentru nr de 16 biti, pentru nr de 32 de biti : ultimii 16 biti+primii 16 biti
	return valBit[x & 0xffff] + valBit[x >> 16];
}

int main()
{
	
	unsigned int n = -1, i=-1, bit;
	uint64_t sum = 0;//echivalent cu unsigned long long
	clock_t time;
	FILE*f;

	printf("Valoarea maxima a unsigned int= %u (ordinul miliardelor)\n",n);
	printf("n=");
	scanf("%d", &n);


	//BitwiseTableTool();
	//bitTable.bin a fost generat folosind functia de mai sus, acum trebuie doar citita din memorie
	f = fopen("bitTable.bin", "rb");
	while (f == NULL) {
		printf("Generating bin values\n");
		BitwiseTableTool();
		f = fopen("bitTable.bin", "rb");
		i = 0;
	}
	if(i==0)
		printf("Done!\n");
	fread(valBit, sizeof(uint8_t), 65536, f);
	
	time = clock();
	//varianta neoptimizata, e ok pentru n ~< 10 000 000 
	
	for (i = 1; i <= n; i++) {
		for (bit = 0; bit <= 31; bit++) {
			sum += (i >> bit) & 1;
			
		}
		
	}
	time = clock() - time;
	printf("TIMP: %g\n", (double)time/CLOCKS_PER_SEC);
	printf("Suma bitilor=%llu\n", sum);
	
	
	
	
	//prima varianta optimizata, tot destul de ineficienta pentru valori > 1 000 000 000
	printf("\nVarianta optimizata 1:\n");
	sum = 0;
	time = clock();
	
	for (i = 1; i <= n; i++) 
	    	sum += popCount(i);

	time = clock() - time;
	printf("TIMP: %g\n", (double)time / CLOCKS_PER_SEC);
	printf("Suma bitilor=%llu\n", sum);
	
	

	//ultima optimizare(ocupa mai multa memorie dar este mai rapida), pentru valori mai mari de 10 000 000 000 tot dureaza foarte mult timp
	
	printf("\nVarianta optimizata 2:\n");
	sum = 0;
	time = clock();
	for (i = 1; i <= n; i++)
		sum += popCountMem(i);

	time = clock() - time;
	printf("TIMP: %g\n", (double)time / CLOCKS_PER_SEC);
	printf("Suma bitilor=%llu\n", sum);
	return 0;
}