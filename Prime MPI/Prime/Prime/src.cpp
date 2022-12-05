#include<iostream>
#include<mpi.h>
#include<fstream>
using namespace std;

bool isPrime(long n) {
    if (n == 1 || n == 0)
        return false;
    else {

        for (int i = 2; i <= n / 2; ++i) {
            if (n % i == 0) {
                return false;
            }
        }
        return true;
    }
}

void main() {
    MPI_Init(NULL, NULL);
    const int x = 6;
    const long N = pow(10.0, x);
    MPI_Status st;
    int  start, end, rank, size, sum = 0, mySum = 0;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    if (rank == 0) {

        for (int i = 1; i < size; i++) {
            start = i * N / size;
            end = start + N / size;
            MPI_Send(&start, 1, MPI_INT, i, 5, MPI_COMM_WORLD);
            MPI_Send(&end, 1, MPI_INT, i, 6, MPI_COMM_WORLD);

        }
        start = rank * N / size;
        int  end = start + N / size;

        for (int i = start; i < end; i++) {
            if (isPrime(i)) {
                mySum += 1;
            }
        }

    }

    if (rank != 0)
    {

        MPI_Recv(&start, 1, MPI_INT, 0, 5, MPI_COMM_WORLD, &st);
        MPI_Recv(&end, 1, MPI_INT, 0, 6, MPI_COMM_WORLD, &st);
        for (int i = start; i < end; i++) {
            if (isPrime(i)) {
                mySum += 1;
            }
        }
    }

    MPI_Reduce(&mySum, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);


    if (rank == 0) {
        cout << sum << endl;

    }
    MPI_Finalize();

}