#include "mpi.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    int process_id;
    int ierr;
    int number_of_processes;
    
    // Initialize MPI.
    ierr = MPI_Init(&argc, &argv);
    
    // Determine the number of processes.
    ierr = MPI_Comm_size(MPI_COMM_WORLD, &number_of_processes);

    // Get the individual process ID.
    ierr = MPI_Comm_rank(MPI_COMM_WORLD, &process_id);

    printf("Hello world from process %d of %d\n", process_id, number_of_processes);

    // Finalize MPI.
    ierr = MPI_Finalize();
    
    return 0;
}

    
