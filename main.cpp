#include <iostream>
#include <ctime>
#include "include/algorithm.h"
#include <mpi.h>
#include <fstream>

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
    ofstream myfile;
    myfile.open ("results1.log", ios::app);
    int threadNum = 2;
    MPI_Init(NULL, NULL);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    for (int n : N_ARRAY) {

        if (world_rank == 0) {

            for (double epsilon: EPSILON) {

                myfile << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"
                          << std::endl << std::endl;
                myfile << "Zadanie 1 " << std::endl;
                myfile << "Rownolegle CRS2" << std::endl;
                myfile << "Epsilon: " << epsilon << std::endl;
                myfile << "Liczba watkow: " << threadNum << endl;
                myfile << "n = " << n << std::endl;
                if(1)
                {
                    myfile << "a1" << std::endl;
                    Algorithm *CRS2_f1 = new Algorithm(n);
                    myfile << "a2" << std::endl;

                    Exercise *f = new Func_1(n);
                    myfile << "a3" << std::endl;

                    CRS2_f1->runCRS2(f, true, epsilon, false, threadNum);
                    myfile << "a4" << std::endl;

                    delete CRS2_f1;
                    delete f;
                }

//                myfile << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"
//                          << std::endl << std::endl;
//                myfile << "Zadanie 2" << std::endl;
//                myfile << "Rownolegle CRS2" << std::endl;
//                myfile << "Epsilon: " << epsilon << std::endl;
//                myfile << "Liczba watkow: " << threadNum << endl;
//                myfile << "n = " << n << std::endl;
//                {
//                    Algorithm *CRS2_f2 = new Algorithm(n);
//                    Exercise *f = new Func_2(n);
//                    CRS2_f2->runCRS2(f, true, epsilon, false, threadNum);
//                    delete CRS2_f2;
//                    delete f;
//                }

                myfile << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"
                          << std::endl << std::endl;
                myfile << "Zadanie 1" << std::endl;
                myfile << "Rownolegle CRS3" << std::endl;
                myfile << "Epsilon: " << epsilon << std::endl;
                myfile << "Liczba watkow: " << threadNum << endl;
                myfile << "n = " << n << std::endl;
                if(1)
                {
                    Algorithm *CRS3_f1 = new Algorithm(n);
                    Exercise *f = new Func_1(n);
                    CRS3_f1->runCRS3(f, true, epsilon, threadNum);
                    delete CRS3_f1;
                    delete f;
                }

//                myfile << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"
//                          << std::endl << std::endl;
//                myfile << "Zadanie 2" << std::endl;
//                myfile << "Rownolegle CRS3" << std::endl;
//                myfile << "Epsilon: " << epsilon << std::endl;
//                myfile << "Liczba watkow: " << threadNum << endl;
//                myfile << "n = " << n << std::endl;
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
                myfile << "adasdadada";
                MPI_Recv(&sampleSet[0][0], 10*(n+1)*(n+1), MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                if(sampleSet[0][0]==0){
                    break;
                }
                Algorithm *CRS3_f1 = new Algorithm(n);
                std::cout << " before newCandidate" << std::endl;
                pair<vector<double>, double> newCandidate = CRS3_f1->getNewTrialPoint(CRS3_f1->setSampleSet(sampleSet));
                std::cout << "newCandidate" << std::endl;
                double *candidate = (double *)malloc((n+1)*sizeof(double));
                std::cout << "newCandidate malloc" << std::endl;
                candidate[0] = newCandidate.second;
                for (int i=0; i<n; i++){
                    candidate[i+1] = newCandidate.first.at(i);
                }
                std::cout << "newCandidate after malloc" << std::endl;
                MPI_Send(&candidate[0], (n+1), MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
            }
        }
    }

    MPI_Finalize();
    myfile.close();
    return 0;
}
