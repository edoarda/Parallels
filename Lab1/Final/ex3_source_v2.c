#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#define	ARRAYSIZE 128

void imprime_5_primeiros(float* data, int qtd, int world_size) {
    int i, j;
    for (i=0; i < world_size; i++) {
        printf("Processo %d me mandou: ", i);
        for (j=0; j < qtd; j++) {
            if (j < 5)
                printf("%f ", data[(qtd*i) + j]);    
        }
        printf("\n");
    }
}

int main (int argc, char** argv) {
    //MPI variables
    int world_rank;
    int world_size;
    double t1, t2;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    //Program variables
    int i;      /* loop variable */
    int qtd = ARRAYSIZE / world_size;    /* qtd dos pedacinhos */
	float	data[ARRAYSIZE]; 	/* the intial array */
    float final_data[ARRAYSIZE];
    //float* final_data;
    float mini_data[qtd]; 
    float resultado, resultado_parcial = 0;

    MPI_Barrier(MPI_COMM_WORLD);
    t1 = MPI_Wtime();

    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    if (world_rank == 0) {
		printf("Starting serial array example...\n");
		printf("Using array of %d floats. Requires %ld bytes\n",ARRAYSIZE,sizeof(data));

		/* Initialize the array */
		printf("Initializing array...\n");

		for(i = 0; i < ARRAYSIZE; i++)
  			data[i] =  i * 1.0;
    }

    //tem que ser fora do if
	MPI_Scatter(data, qtd, MPI_FLOAT, &mini_data, qtd, MPI_FLOAT, 0, MPI_COMM_WORLD);

    printf("Performing computation on array elements...\n");

    //para contar com a diferença da posição entre pedaços de mini_data e do vetorzão
    for(i=0; i < qtd; i++) {
        mini_data[i] = mini_data[i] + (i + (qtd * world_rank)) * 1.0;
        resultado_parcial += mini_data[i];
    }
        
    printf("Resultado parcial de %d foi %f!\n", world_rank, resultado_parcial);

    /*if (world_rank == 0) {
        final_data = malloc(sizeof(float) * world_size);
    }*/

    MPI_Gather(&mini_data, qtd, MPI_FLOAT, &final_data, qtd, MPI_FLOAT, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        //falta imprimir os 5 primeiros q ele recebeu eu não sei como fazer, acho que são uns for bem logicos
        imprime_5_primeiros(final_data, qtd, world_size);
        for(i=0; i<ARRAYSIZE; i++)
            resultado += final_data[i];

        printf("Resultado total foi %f!\n", resultado);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    t2 = MPI_Wtime();
    MPI_Finalize();

    if (world_rank == 0){
        printf( "Elapsed time is %f\n", t2 - t1 );
        //free(final_data); 
    }
}