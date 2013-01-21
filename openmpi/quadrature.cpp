#include <cstdlib>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "mpi.h"

using namespace std;

int main ( int argc, char *argv[] );
double f ( double x );

int main(int argc, char *argv[]) {
    double a;
    double b;
    double my_a;
    double my_b;
    double error;
    double exact;
    double total;
    double x;
    int n;
    int my_n;
    double my_total;
    int i;
    int q;
    int processor_id;
    int number_of_processors;
    int tag;
    int target;
    int source;
    double wtime;

    MPI::Status status;

    n = 10000000;
    total = 0.0;
    a = 0.0;
    b = 10.0;
    exact = 0.49936338107645674464;
    
    // Initialize MPI.
    MPI::Init(argc, argv);

    // Get this processor's ID.
    processor_id = MPI::COMM_WORLD.Get_rank();

    // Get the number of processors.
    number_of_processors = MPI::COMM_WORLD.Get_size();
    
    if (processor_id == 0) {
        my_n = n / (number_of_processors - 1);
        n = my_n * (number_of_processors - 1);
        wtime = MPI::Wtime();
    }
    
    source = 0;
    MPI::COMM_WORLD.Bcast(&my_n, 1, MPI::INT, source);

    if (processor_id == 0) {
        //
        // Assign to each process a subinterval of [a, b].
        //
        for (q = 1; q <= number_of_processors - 1; q++) {
            // Set target to the qth process.
            target = q;
            
            // Compute the endpoints for this subinterval.
            my_a = ((double)(number_of_processors - q) * a + (double)(q - 1) * b) / (double)(number_of_processors - 1);
            my_b = ((double)(number_of_processors - q - 1) * a + (double)(q    ) * b) / (double)(number_of_processors - 1);           
            
            tag = 1;
            MPI::COMM_WORLD.Send(&my_a, 1, MPI::DOUBLE, target, tag);
            
            tag = 2;
            MPI::COMM_WORLD.Send(&my_b, 1, MPI::DOUBLE, target, tag);

        }

        total = 0.0;
        my_total = 0.0;

    } else {
        //
        // Each process recieves their subinterval and evaluates that part of the interval.
        //
        
        source = 0;

        tag = 1;
        MPI::COMM_WORLD.Recv(&my_a, 1, MPI::DOUBLE, source, tag, status);
        tag = 2;
        MPI::COMM_WORLD.Recv(&my_b, 1, MPI::DOUBLE, source, tag, status);

        for (i = 1; i < my_n; i++) {
            x = ((double)(my_n - 1) * my_a + ((double)(i - 1) * my_b)) / (double)(my_n - 1);
            my_total += f(x);
        }
        my_total = (my_b - my_a) * my_total / (double)(my_n);
    }

    //
    // Have each process send its computed value to the master process.
    //
    MPI::COMM_WORLD.Reduce(&my_total, &total, 1, MPI::DOUBLE, MPI::SUM, 0);
    
    if (processor_id == 0) {
        error = fabs(total - exact);
        wtime = MPI::Wtime() - wtime;

        cout << "\n";
        cout << "  Estimate = " << setw(24) << setprecision(16) << total << "\n";
        cout << "  Error = " << error << "\n";
        cout << "  Time = " << wtime << "\n";
    }
    
    //
    // Destory MPI.
    //
    MPI::Finalize();

    return 0;
}

double f(double x) {
    double pi;
    double value;

    pi = 3.141592653589793;
    value = 50.0 / ( pi * ( 2500.0 * x * x + 1.0 ) );
    return value;
}

