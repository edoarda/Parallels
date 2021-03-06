#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

//define NUM 24000
//original 140000

void Imprimir(int *array,int length){ //print array elements
    int i=0;
    for(i=0;i<length;i++)
        printf("%d ",array[i]);
	printf("\n");
}

int * merge(int *v1, int n1, int *v2, int n2){
	int i,j,k;
	int * result;

	result = (int *)malloc((n1+n2)*sizeof(int));

	i=0; j=0; k=0;
	while(i<n1 && j<n2)
		if(v1[i]<v2[j]){
			result[k] = v1[i];
			i++; k++;
		}
		else{
			result[k] = v2[j];
			j++; k++;
		}
	if(i==n1)
		while(j<n2){
			result[k] = v2[j];
			j++; k++;
		}
	else
		while(i<n1){
			result[k] = v1[i];
			i++; k++;
		}
	return result;
}

/*
void shellsort (int numbers[], int array_size)
{
    	int i, j, increment, temp;
	increment = 3;
	while (increment > 0)
	{
		for (i=0; i < array_size; i++)
		{
			j = i;
			temp = numbers[i];
			while ((j >= increment) && (numbers[j-increment] > temp))
			{
				numbers[j] = numbers[j - increment];
				j = j - increment;
			}
			numbers[j] = temp;
		}
		if (increment/2 != 0)
			increment = increment/2;
		else if (increment == 1)
			increment = 0;
		else
			increment = 1;
	}
}
*/

void InsertionSort(int N, int *A){
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

int main(int argc, char **argv){
	int * data;
	int * chunk;
	int * aux;
	int tamVetorFracionado,tamDoVetor;
	int world_rank,world_size;
	int tamVetorParcial;
	int i; //indice pro for
	int step;
	MPI_Status status;
	struct timeval start, end;

	if (argc < 2) {
		printf("USAGE: %s tamanho do vetor (valores do vetor no programa)\n", argv[0]);
		return 1;
	}

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&world_rank);
	MPI_Comm_size(MPI_COMM_WORLD,&world_size);
	tamDoVetor = atoi(argv[1]);


//MESTRE
	if(world_rank==0){
		//int r;
		tamVetorParcial = tamDoVetor/world_size;
		//r = tamDoVetor%world_size;
		//data = (int *)malloc((tamDoVetor+world_size-r)*sizeof(int));
		data = (int *)malloc((tamDoVetor+world_size)*sizeof(int));
		srand(time(0));
		for(i=0;i<tamDoVetor;i++)
			data[i] = (rand()%400);
		/*if(r!=0)
		{
			for(i=tamDoVetor;i<tamDoVetor+world_size-r;i++)
  			   data[i]=0;
			tamVetorParcial=tamVetorParcial+1;
		}*/
		//Imprimir(data, tamDoVetor);
		
		gettimeofday(&start, NULL);

		MPI_Bcast(&tamVetorParcial,1,MPI_INT,0,MPI_COMM_WORLD);
		chunk = (int *)malloc(tamVetorParcial*sizeof(int));
		MPI_Scatter(data,tamVetorParcial,MPI_INT,chunk,tamVetorParcial,MPI_INT,0,MPI_COMM_WORLD);
		ShellShort(chunk,tamVetorParcial);
	}


//TRABALHADORES
	else{
		MPI_Bcast(&tamVetorParcial,1,MPI_INT,0,MPI_COMM_WORLD);
		chunk = (int *)malloc(tamVetorParcial*sizeof(int));
		MPI_Scatter(data,tamVetorParcial,MPI_INT,chunk,tamVetorParcial,MPI_INT,0,MPI_COMM_WORLD);
		ShellShort(chunk,tamVetorParcial);
	}

	step = 1;
	while(step<world_size){
		if(world_rank%(2*step)==0){
			if(world_rank+step<world_size){
				MPI_Recv(&tamVetorFracionado,1,MPI_INT,world_rank+step,0,MPI_COMM_WORLD,&status);
				aux = (int *)malloc(tamVetorFracionado*sizeof(int));
				MPI_Recv(aux,tamVetorFracionado,MPI_INT,world_rank+step,0,MPI_COMM_WORLD,&status);
				chunk = merge(chunk,tamVetorParcial,aux,tamVetorFracionado);
				tamVetorParcial = tamVetorParcial+tamVetorFracionado;
			}
		}
		else{
			int near = world_rank-step;
			MPI_Send(&tamVetorParcial,1,MPI_INT,near,0,MPI_COMM_WORLD);
			MPI_Send(chunk,tamVetorParcial,MPI_INT,near,0,MPI_COMM_WORLD);
			break;
		}
		step = step*2;
	}
	if(world_rank==0){
		gettimeofday(&end, NULL);
		printf("Tempo Decorrido: %ld milissegundos!\n", ((end.tv_sec * 1000000 + end.tv_usec) 
		- (start.tv_sec * 1000000 + start.tv_usec)));
		//Imprimir(chunk,NUM);
	}
	MPI_Finalize();
}