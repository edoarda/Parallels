#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#define	ARRAYSIZE 1024

/*
 	TAG 0: para o vetor
	TAG 1: para o resultado
*/

int main (int argc, char** argv) {
    int world_rank;
    int world_size;
	
	MPI_Request &send_request
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    
	//printf("Size %d \n", world_size);
    
    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

	int i;      /* loop variable */
    int qtd = ARRAYSIZE / world_size-1;     /* qtd dos pedacinhos */
	float	data[ARRAYSIZE]; 	/* the intial array */
	float mini_data[qtd];   
    float resultado;

    if (world_rank == 0) {
		printf("Starting serial array example...\n");
		printf("Using array of %d floats. Requires %ld bytes\n",ARRAYSIZE,sizeof(data));

		/* Initialize the array */
		printf("Initializing array...\n");
		for(i=0; i<ARRAYSIZE; i++) 
  			data[i] =  i * 1.0;

		//MPI SCATTER
		MPI_Scatter(&data, qtd, MPI_FLOAT, &mini_data, qtd, MPI_FLOAT, 0, MPI_COMM_WORLD);
    }

        printf("Performing computation on array elements...\n");

        //acho que a qtd*world_rank vai contar pro offset do amiguinho e calcular de acordo com a posição certa.
        for(i=0; i < qtd; i++)
   			mini_data[i] = mini_data[i] + (qtd * world_rank) * 1.0;

		for(i = 0; i < qtd; i++)
			resultado += mini_data[i];
        
        printf("Resultado parcial de %d foi %f!", world_rank, resultado);

        if (world_rank == 0) {

            MPI_Gather(&data, qtd, MPI_FLOAT, &mini_data, qtd, MPI_FLOAT, 0, MPI_COMM_WORLD);

            //falta imprimir os 5 primeiros q ele recebeu eu não sei como fazer, acho que são uns for bem logicos

            for(i=0; i<ARRAYSIZE; i++)
                resultado += data[i];

            
        }

}