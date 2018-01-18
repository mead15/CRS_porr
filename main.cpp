#include <iostream>
#include <ctime>
#include "include/algorithm.h"
#include <mpi.h>

using namespace std;

static const int N_ARRAY[5] = {2, 10, 20, 50, 100};
static const double EPSILON[4] = {1e-2, 1e-4, 1e-6, 1e-8};


double **alloc_2d(int rows, int cols) {
    double *data = (double *)malloc(rows*cols*sizeof(double));
    double **array= (double **)malloc(rows*sizeof(double*));
    for (int i=0; i<rows; i++)
        array[i] = &(data[cols*i]);

    return array;
}


int main(int argc, char** argv)
{
    srand (time(NULL));

    int threadNum = 2;
    MPI_Init(NULL, NULL);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    for (int n : N_ARRAY) {

        if (world_rank == 0) {

            for (double epsilon: EPSILON) {

                std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"
                          << std::endl << std::endl;
                std::cout << "Zadanie 1 " << std::endl;
                std::cout << "Rownolegle CRS2" << std::endl;
                std::cout << "Epsilon: " << epsilon << std::endl;
                std::cout << "Liczba watkow: " << threadNum << endl;
                std::cout << "n = " << n << std::endl;
                {
                    std::cout << "a1" << std::endl;
                    Algorithm *CRS2_f1 = new Algorithm(n);
                    std::cout << "a2" << std::endl;

                    Exercise *f = new Func_1(n);
                    std::cout << "a3" << std::endl;

                    CRS2_f1->runCRS2(f, true, epsilon, false, threadNum);
                    std::cout << "a4" << std::endl;

                    delete CRS2_f1;
                    delete f;
                }

//                std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"
//                          << std::endl << std::endl;
//                std::cout << "Zadanie 2" << std::endl;
//                std::cout << "Rownolegle CRS2" << std::endl;
//                std::cout << "Epsilon: " << epsilon << std::endl;
//                std::cout << "Liczba watkow: " << threadNum << endl;
//                std::cout << "n = " << n << std::endl;
//                {
//                    Algorithm *CRS2_f2 = new Algorithm(n);
//                    Exercise *f = new Func_2(n);
//                    CRS2_f2->runCRS2(f, true, epsilon, false, threadNum);
//                    delete CRS2_f2;
//                    delete f;
//                }

                std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"
                          << std::endl << std::endl;
                std::cout << "Zadanie 1" << std::endl;
                std::cout << "Rownolegle CRS3" << std::endl;
                std::cout << "Epsilon: " << epsilon << std::endl;
                std::cout << "Liczba watkow: " << threadNum << endl;
                std::cout << "n = " << n << std::endl;
                {
                    Algorithm *CRS3_f1 = new Algorithm(n);
                    Exercise *f = new Func_1(n);
                    CRS3_f1->runCRS3(f, true, epsilon, threadNum);
                    delete CRS3_f1;
                    delete f;
                }

//                std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"
//                          << std::endl << std::endl;
//                std::cout << "Zadanie 2" << std::endl;
//                std::cout << "Rownolegle CRS3" << std::endl;
//                std::cout << "Epsilon: " << epsilon << std::endl;
//                std::cout << "Liczba watkow: " << threadNum << endl;
//                std::cout << "n = " << n << std::endl;
//                {
//                    Algorithm *CRS3_f2 = new Algorithm(n);
//                    Exercise *f = new Func_2(n);
//                    CRS3_f2->runCRS3(f, true, epsilon, threadNum);
//                    delete CRS3_f2;
//                    delete f;
//                }
            }
        } else {
            while (1) {
                double **sampleSet = alloc_2d(10*(n+1), n+1);
                std::cout << "adasdadada";
//                MPI_Recv(&sampleSet[0][0], 10*(n+1)*(n+1), MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                if(sampleSet[0][0]==0){
                    break;
                }
                Algorithm *CRS3_f1 = new Algorithm(n);
                pair<vector<double>, double> newCandidate = CRS3_f1->getNewTrialPoint(CRS3_f1->setSampleSet(sampleSet));
                double *candidate = (double *)malloc((n+1)*sizeof(double));
                candidate[0] = newCandidate.second;
                for (int i=0; i<n; i++){
                    candidate[i+1] = newCandidate.first.at(i);
                }
                MPI_Send(&candidate[0], (n+1), MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
            }
        }
    }

    MPI_Finalize();

    return 0;
}
