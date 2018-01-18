//#include <iostream>
//#include <ctime>
//#include "include/algorithm.h"
//
//using namespace std;
//
//static const int NUMBER_OF_THREADS[5] = {2, 4, 8, 16, 32};
//static const int N_ARRAY[5] = {2, 10, 20, 50, 100};
//static const double EPSILON[4] = {1e-2, 1e-4, 1e-6, 1e-8};
//
//int main()
//{
//    srand (time(NULL));
//
//    std::cout << "CRS2" << std::endl;
//    for (double epsilon: EPSILON) {
//
//        std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << std::endl << std::endl;
//        std::cout << "Zadanie 1 " << std::endl;
//        std::cout << "Rownolegle CRS2" << std::endl;
//        std::cout << "Epsilon: " << epsilon << std::endl;
//        for (int threadNum: NUMBER_OF_THREADS){
//            std::cout<< "Liczba watkow: " << threadNum << endl;
//            for (int n : N_ARRAY) {
//                std::cout << "n = " << n << std::endl;
//                Algorithm *CRS2_f1 = new Algorithm(n);
//                Exercise *f = new Func_1(n);
//                CRS2_f1->runCRS2(f, true, epsilon, false, threadNum);
//                delete CRS2_f1;
//                delete f;
//            }
//        }
//
//
//        std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << std::endl << std::endl;
//        std::cout << "Zadanie 1 " << std::endl;
//        std::cout << "Sekwencyjnie CRS2" << std::endl;
//        std::cout << "Epsilon: " << epsilon << std::endl;
//        for (int n : N_ARRAY) {
//            std::cout << "n = " << n << std::endl;
//            Algorithm *CRS2_f1 = new Algorithm(n);
//            Exercise *f = new Func_1(n);
//            CRS2_f1->runCRS2(f, false, epsilon, false, 1);
//            delete CRS2_f1;
//            delete f;
//        }
//
//
//        std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << std::endl << std::endl;
//        std::cout << "Zadanie 2" << std::endl;
//        std::cout << "Rownolegle CRS2" << std::endl;
//        std::cout << "Epsilon: " << epsilon << std::endl;
//        for (int threadNum: NUMBER_OF_THREADS) {
//            std::cout << "Liczba watkow: " << threadNum << endl;
//            for (int n : N_ARRAY) {
//                std::cout << "n = " << n << std::endl;
//                Algorithm *CRS2_f2 = new Algorithm(n);
//                Exercise *f = new Func_2(n);
//                CRS2_f2->runCRS2(f, true, epsilon, false, threadNum);
//                delete CRS2_f2;
//                delete f;
//            }
//        }
//
//        std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << std::endl << std::endl;
//        std::cout << "Zadanie 2" << std::endl;
//        std::cout << "Sekwencyjnie CRS2" << std::endl;
//        std::cout << "Epsilon: " << epsilon << std::endl;
//        for(int n : N_ARRAY){
//            std::cout << "n = " << n << std::endl;
//            Algorithm* CRS2_f2= new Algorithm(n);
//            Exercise* f = new Func_2(n);
//            CRS2_f2->runCRS2(f, false, epsilon, false, 1);
//            delete CRS2_f2;
//            delete f;
//        }
//
//        std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << std::endl << std::endl;
//        std::cout << "Zadanie 1" << std::endl;
//        std::cout << "Rownolegle CRS3" << std::endl;
//        std::cout << "Epsilon: " << epsilon << std::endl;
//        for (int threadNum: NUMBER_OF_THREADS) {
//            std::cout << "Liczba watkow: " << threadNum << endl;
//            for (int n : N_ARRAY) {
//                std::cout << "n = " << n << std::endl;
//                Algorithm *CRS3_f1 = new Algorithm(n);
//                Exercise *f = new Func_1(n);
//                CRS3_f1->runCRS3(f, true, epsilon, threadNum);
//                delete CRS3_f1;
//                delete f;
//            }
//        }
//
//        std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << std::endl << std::endl;
//        std::cout << "Zadanie 1" << std::endl;
//        std::cout << "Sekwencyjnie CRS3" << std::endl;
//        std::cout << "Epsilon: " << epsilon << std::endl;
//        for (int n : N_ARRAY) {
//            std::cout << "n = " << n << std::endl;
//            Algorithm *CRS3_f1 = new Algorithm(n);
//            Exercise *f = new Func_1(n);
//            CRS3_f1->runCRS3(f, false, epsilon, 1);
//            delete CRS3_f1;
//            delete f;
//        }
//
//        std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << std::endl << std::endl;
//        std::cout << "Zadanie 2" << std::endl;
//        std::cout << "Rownolegle CRS3" << std::endl;
//        std::cout << "Epsilon: " << epsilon << std::endl;
//        for (int threadNum: NUMBER_OF_THREADS) {
//            std::cout << "Liczba watkow: " << threadNum << endl;
//            for (int n : N_ARRAY) {
//                std::cout << "n = " << n << std::endl;
//                Algorithm *CRS3_f2 = new Algorithm(n);
//                Exercise *f = new Func_2(n);
//                CRS3_f2->runCRS3(f, true, epsilon, threadNum);
//                delete CRS3_f2;
//                delete f;
//            }
//        }
//
//        std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << std::endl << std::endl;
//        std::cout << "Zadanie 2" << std::endl;
//        std::cout << "Sekwencyjnie CRS3" << std::endl;
//        std::cout << "Epsilon: " << epsilon << std::endl;
//        for(int n : N_ARRAY){
//            std::cout << "n = " << n << std::endl;
//            Algorithm* CRS3_f2= new Algorithm(n);
//            Exercise* f = new Func_2(n);
//            CRS3_f2->runCRS3(f, false, epsilon, 1);
//            delete CRS3_f2;
//            delete f;
//        }
//    }
//    return 0;
//}
#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    // Print off a hello world message
    printf("Hello world from processor %s, rank %d"
                   " out of %d processors\n",
           processor_name, world_rank, world_size);

    // Finalize the MPI environment.
    MPI_Finalize();
}