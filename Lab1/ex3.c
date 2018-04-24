#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#define	ARRAYSIZE 1024

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
    
    if (world_rank == 0) {
		int     i; 			/* loop variable */
		float	data[ARRAYSIZE]; 	/* the intial array */

		printf("Starting serial array example...\n");
		printf("Using array of %d floats. Requires %ld bytes\n",ARRAYSIZE,sizeof(data));

		/* Initialize the array */
		printf("Initializing array...\n");
		for(i=0; i<ARRAYSIZE; i++) 
  			data[i] =  i * 1.0;

		/*// Do a simple value assignment to each of the array elements
		printf("Performing computation on array elements...\n");
		for(i=1; i < ARRAYSIZE; i++)
   			data[i] = data[i] + i * 1.0;*/

		int qtd_a_enviar = ARRAYSIZE / world_size-1;
		printf("Vou enviar %d elementos à %d amiguinhos...\n", qtd_a_enviar, world_size-1);
		
		
		data = data + qtd_a_enviar;

		//MPI SCATTER
		//MPI_Scatter(&data, qtd_a_enviar, MPI_FLOAT, buffer_receber, qtd_receber, MPI_COMM_WORLD);
		for(i = 1; i < world_size; i++) {
			MPI_Isend(&data, qtd_a_enviar, MPI_FLOAT, i, 0, MPI_COMM_WORLD, &send_request);
			data = data + qtd_a_enviar;
		}
        

		// pega meu pedaço

		printf("Performing computation on array elements...\n");
		for(i=1; i < qtd_a_enviar; i++)
   			data[i] = data[i] + i * 1.0;
		
		float resultado;        
		for(i = 0; i < qtd_a_enviar; i++)
			resultado += data[i];
		
		//		
		
		
		//MPI_Finalize();    
    } else {
		int qtd_a_receber = ARRAYSIZE / world_size-1;
        MPI_Recv(&resposta, qtd_a_receber, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		
		/* Do a simple value assignment to each of the array elements */
		printf("Performing computation on array elements...\n");
		for(i=1; i < qtd_a_receber; i++)
   			data[i] = data[i] + i * 1.0;

		float resultado;        
		for(i = 0; i < qtd_a_receber; i++)
			resultado += data[i];
        
		//ideia: tag soma e tag vetor e ele recebe as tags e faz os paranaue tudo
		//usar MPI_Reduce		
		//esquece a ideia duas a cima mas deixa ai pq e legal
		
        
    // Finalize the MPI environment.
    MPI_Finalize();
    
    }
    
 
}

/*
	Pointer arithmetic in C implicitly accounts for the size of the elements, so adding 1 will actually add 1 * sizeof(int)
	from: https://stackoverflow.com/questions/38548759/pass-in-part-of-an-array-as-function-argument
*/

