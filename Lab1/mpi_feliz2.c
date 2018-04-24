#include <stdio.h>
#include "mpi.h"

int main (int argc, char** argv) {
    int world_rank;
    int world_size;
    MPI_Request	send_request,recv_request;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    
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
        MPI_Isend(&world_rank, 1, MPI_INT, destino, 0, MPI_COMM_WORLD, &send_request);
        
        //IMPRIME
        printf("Tarefa-Lorde %d enviou tarefa para %d\n", world_rank, destino);
        
        //RECEBE O RANKING
        int resposta;
        MPI_Irecv(&resposta, 1, MPI_INT, destino, 0, MPI_COMM_WORLD, &recv_request);

	printf("Tarefa-Lorde %d recebeu tarefa de %d\n", world_rank, destino);
        
	
	MPI_Finalize();    
    } else {
        int destino;
        if (world_rank < (world_size/2)) {
            destino = (world_size/2) + world_rank;
        } else {
            destino = world_rank - (world_size/2);
        }
        //ENVIA O RANKING
        MPI_Isend(&world_rank, 1, MPI_INT, destino, 0, MPI_COMM_WORLD, &send_request);
        
        //IMPRIME
        printf("Tarefa %d enviou tarefa para %d\n", world_rank, destino);
        
        //RECEBE O RANKING
        int resposta;
        MPI_Irecv(&resposta, 1, MPI_INT, destino, 0, MPI_COMM_WORLD, &recv_request);
        
        //IMPRIME
        printf("Tarefa %d recebeu tarefa de %d\n", world_rank, destino);
        
    // Finalize the MPI environment.
    MPI_Finalize();
    
    }
    
 
}

