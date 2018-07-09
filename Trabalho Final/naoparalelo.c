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

void ShellShort(int *A, int n) {
  int i, j;
  int incr = n/2;
  while (incr > 0) {
    for (int i=incr+1; i<n; i++) {
      j=i-incr;
      while (j > 0)
        if(A[j] > A[j+incr]) {
          //swap
          int temp = A[j];
          A[j] = A[j+incr];
          A[j+incr] = temp;
          //end swap
          j = j - incr;          
        }
        else j = 0;
    }
    incr = incr/2;
  }
  InsertionSort(n,A);
}


int main(int argc, char **argv) {
	if (argc < 2) {
		printf("USAGE: %s tamanho do vetor (valores do vetor gerados aleatoriamente)\n", argv[0]);
		return 1;
	}
	int tamDoVetor= atoi(argv[1]);

	

	//gera valores pro vetor
	srand(time(0));
	int vetor[tamDoVetor];

	for(int i = 0; i<tamDoVetor; i++)
		vetor[i]=rand();
	//fim geração
	
	//time stuff
	struct timeval start, end;
 	gettimeofday(&start, NULL);

	/*
	int i;
	
	printf("# # # # VETOR ORIGINAL # # # #\n");
	for(i=0; i<tamDoVetor; i++){
		printf("%d ",vetor[i]);
	}
	printf("\n# # # # # # # # # # # # # # # #\n");
	printf("\n");
	*/

	ShellShort(vetor, tamDoVetor);
	/*
	printf("# # # # VETOR ORDENADO # # # #\n");
	for(i=0; i<tamDoVetor; i++){
		printf("%d ",vetor[i]);
	}
	printf("\n# # # # # # # # # # # # # # # #\n");
	printf("\n");
	*/
  gettimeofday(&end, NULL);
  printf("Tempo Decorrido: %ld milissegundos!\n", ((end.tv_sec * 1000000 + end.tv_usec)
          - (start.tv_sec * 1000000 + start.tv_usec)));
}


void ShellShort(int *A, int n) {
  int incr = n/2;
  while (incr > 0) {
    for (int i=incr+1; i<n; i++) {
      j=i-incr;
      while (j > 0)
        if(A[j] > A[j+incr]) {
          //swap
          int temp = A[j];
          A[j] = A[j+incr];
          a[j+incr] = temp;
          //end swap
          j = j - incr;          
        }
        else j = 0;
    }
    incr = incr/2;
  }
  InsertionSort(N,A);
}

int main(){
	printf("oi");
	int temp[11] = {2,5,9,7,1,6,8,3,4,5,-666};
	int *a = malloc(11 *sizeof(int));
	a=temp;
	
	printf("oi");
	ShellShort(a, 11);
	printf("oi");
	int i;
	for(i=0; i<11; i++){
		printf("%d ",a[i]);
	}
	printf("\n");
	//free(a);
}
