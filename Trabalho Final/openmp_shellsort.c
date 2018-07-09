#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>


void InsertionSort(int N, int *A)
{
  int i, j, v;
  for (i = 1; i < N; i++) {
    v = A[i]; 
    j = i;
    while (A[j-1] > v) {
      A[j] = A[j-1]; 
      j--;
      if (j <= 0) break;
    }
    A[j] = v;
  }
}

int parallel_shellsort(int *A, int N)
{
  int k, h;
  h = 1; while (h < N) h = 2*h + 1;
  h /= 2;
#pragma omp parallel firstprivate(h)
 {
  while (h != 1) {
	#pragma omp for
    for (k = 0; k < h; k++) {
      int i, j, v;
      for (i = k; i < N; i+=h) {
        v = A[i]; 
        j = i;
        while (A[j-h] > v) {
        	A[j] = A[j-h]; 
        	j = j - h;
		if (j <= h) break;
        }
        A[j] = v;
      } // for i
    }  // for k
    h /= 2;
  } //  end while 
 }  // end parallel region
  InsertionSort(N,A);  // clean up
}

void copia(int *destino, int origem[],int tamanho){
	int i;
	for(i=0;i<tamanho;i++){
		destino[i]=origem[i];
	}
}

int main(int argc, char **argv) {
	if (argc < 2) {
		printf("USAGE: %s tamanho do vetor (valores do vetor no programa)\n", argv[0]);
		return 1;
	}
	int tamDoVetor= atoi(argv[1]);

	
	//gera valores pro vetor
	srand(time(0));
	int vetor[tamDoVetor];

	for(int i = 0; i<tamDoVetor; i++)
		vetor[i]=(rand());
	//fim geração
	
	//time stuff
	struct timeval start, end;
 	gettimeofday(&start, NULL);
	/*
	int i;
	
	printf("# # # # VETOR ORIGINAL # # # #\n");
	for(i=0; i<tamDoVetor; i++){
		printf("%d, ",vetor[i]);
	}
	printf("\n# # # # # # # # # # # # # # # #\n");
	printf("\n");*/

	parallel_shellsort(vetor, tamDoVetor);
	/*
	printf("# # # # VETOR ORDENADO # # # #\n");
	for(i=0; i<tamDoVetor; i++){
		printf("%d ",vetor[i]);
	}
	printf("\n# # # # # # # # # # # # # # # #\n");
	printf("\n");*/

  gettimeofday(&end, NULL);
  printf("Tempo Decorrido: %ld milissegundos!\n", ((end.tv_sec * 1000000 + end.tv_usec)
          - (start.tv_sec * 1000000 + start.tv_usec)));
}
/*int main(){

	int temp[7] = {1093, 364, 121, 40, 13, 4, 1};

	

	parallel_shellsort(7, temp);
	

	int i;
	for(i=0; i<7; i++){
		printf("%d ",temp[i]);
	}
	printf("\n");
}*/