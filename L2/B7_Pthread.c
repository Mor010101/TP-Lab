/* In case of TIMESPEC REDEFINITON ERROR - add HAVE_STRUCT_TIMESPEC to the Preprocessor Definitions (Project Properties > C/C++ > Preprocessor)
   In case of "pthreadVC2.dll not found" - copy dll file to project folder (next to Source.c)

   HOW TO ADD PTHREAD LIBRARIES
   Add the 3 .h files (pthread.h, sched.h, sempahore.h) to the include folder under \VC 
   (mine is C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC). Add the pthreadVC2.lib to the lib folder

   la visual studio community sunt in C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.16.27023
*/




#include<stdio.h>
#include<pthread.h>
#include<time.h>
#include<stdint.h>

const uint32_t m1 = 0x55555555;
const uint32_t m2 = 0x33333333;
const uint32_t m4 = 0x0f0f0f0f;
const uint32_t m8 = 0x00ff00ff;
const uint32_t m16 = 0x0000ffff;

static uint8_t valBit[65536];//65536- in binar este 16 de 1

typedef struct t_data {
	unsigned int n, i;
	
}t_info;

void *ethread(void*arg); //definition for startup function

int popCount(int x)
{
	x -= (x >> 1) & m1;
	x = (x & m2) + ((x >> 2) & m2);
	x = (x + (x >> 4)) & m4;
	x += x >> 8;
	x += x >> 16;	
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
	pthread_t tid[16];//thread id's
	t_info tdata[16];//for passing data to threads
	unsigned int i=-1, r,n=1000;
	void*status[16];//for recieving data
	uint64_t sum = 0;
	FILE *f;
	clock_t time;

	//generating popcount of evry nr < 65536 if saved bin file isn't found
	f = fopen("bitTable.bin", "rb");
	while (f == NULL) {
		printf("Generating bin values\n");
		BitwiseTableTool();
		f = fopen("bitTable.bin", "rb");
		i = 0;
	}
	if (i == 0)
		printf("Done!\n");
	fread(valBit, sizeof(uint8_t), 65536, f);
	
	printf("uint32max= %u\n", i);
	printf("n=");
	scanf("%d", &n);
	time = clock();
	//creating 16 threads
	int thread_no[16];
		for (i = 0; i < 16; i++) {
			tdata[i].i = i;
			tdata[i].n = n;
			if ((r = pthread_create(&tid[i], NULL, ethread, (void*)&tdata[i])) != 0) {
				printf("ERROR creating thread\n");
				return 1;
			}
		}
	//wait for threads to return values
		for (i = 0; i < 16; i++) {
			if ((r = pthread_join(tid[i],&status[i])) != 0) {
				return 1;
			}		
		}
		time = clock() - time;
		for (i = 0; i < 16; i++)
			sum += (int)status[i];
		printf("Suma biti=%llu\n", sum);
		printf("TIMP: %g\n", (double)time / CLOCKS_PER_SEC);
		return 0;
}

void *ethread(void*arg)
{
	t_info *data = (t_info*)arg;
	int i=data->i,min,max;
	uint32_t rez=0;

	//code to split task in 16 almost equal subtasks 
	if (i != 15) {
		min = data->n / 16 * i+1;
		max = data->n / 16 * (i + 1);
	}
	else {
		min = data->n / 16 * i+1;
		max = data->n;
	}
	
	for (i = min; i <= max; i++)
		rez += popCountMem(i);


	pthread_exit(rez);
}