#include <stdio.h>
#include "mpi.h"

int main (int argc, char** argv) {
    int world_rank;
    int world_size;
    double t1, t2;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    
    MPI_Barrier(MPI_COMM_WORLD);
    t1 = MPI_Wtime();
    
	//printf("Size %d \n", world_size);
    //checa se eu posso rodar esse amiguineo
    if ((world_size%2) != 0) {
        MPI_Finalize(); //Talvez MPI_Abort(comm,errorcode)
        return 0;
    }
    
    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);
    
    if (world_rank == 0) {
	int destino;
        if (world_rank < (world_size/2)) {
            destino = (world_size/2) + world_rank;
        } else {
            destino = world_rank - (world_size/2);
        }
        //ENVIA O RANKING
        MPI_Send(&world_rank, 1, MPI_INT, destino, 0, MPI_COMM_WORLD);
        
        //IMPRIME
        printf("Tarefa-Lorde %d enviou tarefa para %d\n", world_rank, destino);
        
        //RECEBE O RANKING
        int resposta;
        MPI_Recv(&resposta, 1, MPI_INT, destino, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

	printf("Tarefa-Lorde %d recebeu tarefa de %d\n", world_rank, destino);
           
    } else {
        int destino;
        if (world_rank < (world_size/2)) {
            destino = (world_size/2) + world_rank;
        } else {
            destino = world_rank - (world_size/2);
        }
        //ENVIA O RANKING
        MPI_Send(&world_rank, 1, MPI_INT, destino, 0, MPI_COMM_WORLD);
        
        //IMPRIME
        printf("Tarefa %d enviou tarefa para %d\n", world_rank, destino);
        
        //RECEBE O RANKING
        int resposta;
        MPI_Recv(&resposta, 1, MPI_INT, destino, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        //IMPRIME
        printf("Tarefa %d recebeu tarefa de %d\n", world_rank, destino);
        
    // Finalize the MPI environment.
    }
    MPI_Barrier(MPI_COMM_WORLD);
    t2 = MPI_Wtime();
    MPI_Finalize(); 
    if (world_rank == 0)
        printf( "Elapsed time is %f\n", t2 - t1 ); 
   
}

