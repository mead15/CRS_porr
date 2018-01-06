#include <iostream>
#include <ctime>
#include "include/algorithm.h"

using namespace std;

static const int NUMBER_OF_THREADS[5] = {2, 4, 8, 16, 32};
static const int N_ARRAY[5] = {2, 10, 20, 50, 100};
static const double EPSILON[4] = {1e-2, 1e-4, 1e-6, 1e-8};

int main()
{
    srand (time(NULL));

    std::cout << "CRS2" << std::endl;
    for (double epsilon: EPSILON) {

        std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << std::endl << std::endl;
        std::cout << "Zadanie 1 " << std::endl;
        std::cout << "Rownolegle CRS2" << std::endl;
        std::cout << "Epsilon: " << epsilon << std::endl;
        for (int threadNum: NUMBER_OF_THREADS){
            std::cout<< "Liczba watkow: " << threadNum << endl;
            for (int n : N_ARRAY) {
                std::cout << "n = " << n << std::endl;
                Algorithm *CRS2_f1 = new Algorithm(n);
                Exercise *f = new Func_1(n);
                CRS2_f1->runCRS2(f, true, epsilon, false, threadNum);
                delete CRS2_f1;
                delete f;
            }
        }


        std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << std::endl << std::endl;
        std::cout << "Zadanie 1 " << std::endl;
        std::cout << "Sekwencyjnie CRS2" << std::endl;
        std::cout << "Epsilon: " << epsilon << std::endl;
        for (int n : N_ARRAY) {
            std::cout << "n = " << n << std::endl;
            Algorithm *CRS2_f1 = new Algorithm(n);
            Exercise *f = new Func_1(n);
            CRS2_f1->runCRS2(f, false, epsilon, false, 1);
            delete CRS2_f1;
            delete f;
        }


        std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << std::endl << std::endl;
        std::cout << "Zadanie 2" << std::endl;
        std::cout << "Rownolegle CRS2" << std::endl;
        std::cout << "Epsilon: " << epsilon << std::endl;
        for (int threadNum: NUMBER_OF_THREADS) {
            std::cout << "Liczba watkow: " << threadNum << endl;
            for (int n : N_ARRAY) {
                std::cout << "n = " << n << std::endl;
                Algorithm *CRS2_f2 = new Algorithm(n);
                Exercise *f = new Func_2(n);
                CRS2_f2->runCRS2(f, true, epsilon, false, threadNum);
                delete CRS2_f2;
                delete f;
            }
        }

        std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << std::endl << std::endl;
        std::cout << "Zadanie 2" << std::endl;
        std::cout << "Sekwencyjnie CRS2" << std::endl;
        std::cout << "Epsilon: " << epsilon << std::endl;
        for(int n : N_ARRAY){
            std::cout << "n = " << n << std::endl;
            Algorithm* CRS2_f2= new Algorithm(n);
            Exercise* f = new Func_2(n);
            CRS2_f2->runCRS2(f, false, epsilon, false, 1);
            delete CRS2_f2;
            delete f;
        }

        std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << std::endl << std::endl;
        std::cout << "Zadanie 1" << std::endl;
        std::cout << "Rownolegle CRS3" << std::endl;
        std::cout << "Epsilon: " << epsilon << std::endl;
        for (int threadNum: NUMBER_OF_THREADS) {
            std::cout << "Liczba watkow: " << threadNum << endl;
            for (int n : N_ARRAY) {
                std::cout << "n = " << n << std::endl;
                Algorithm *CRS3_f1 = new Algorithm(n);
                Exercise *f = new Func_1(n);
                CRS3_f1->runCRS3(f, true, epsilon, threadNum);
                delete CRS3_f1;
                delete f;
            }
        }

        std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << std::endl << std::endl;
        std::cout << "Zadanie 1" << std::endl;
        std::cout << "Sekwencyjnie CRS3" << std::endl;
        std::cout << "Epsilon: " << epsilon << std::endl;
        for (int n : N_ARRAY) {
            std::cout << "n = " << n << std::endl;
            Algorithm *CRS3_f1 = new Algorithm(n);
            Exercise *f = new Func_1(n);
            CRS3_f1->runCRS3(f, false, epsilon, 1);
            delete CRS3_f1;
            delete f;
        }

        std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << std::endl << std::endl;
        std::cout << "Zadanie 2" << std::endl;
        std::cout << "Rownolegle CRS3" << std::endl;
        std::cout << "Epsilon: " << epsilon << std::endl;
        for (int threadNum: NUMBER_OF_THREADS) {
            std::cout << "Liczba watkow: " << threadNum << endl;
            for (int n : N_ARRAY) {
                std::cout << "n = " << n << std::endl;
                Algorithm *CRS3_f2 = new Algorithm(n);
                Exercise *f = new Func_2(n);
                CRS3_f2->runCRS3(f, true, epsilon, threadNum);
                delete CRS3_f2;
                delete f;
            }
        }

        std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << std::endl << std::endl;
        std::cout << "Zadanie 2" << std::endl;
        std::cout << "Sekwencyjnie CRS3" << std::endl;
        std::cout << "Epsilon: " << epsilon << std::endl;
        for(int n : N_ARRAY){
            std::cout << "n = " << n << std::endl;
            Algorithm* CRS3_f2= new Algorithm(n);
            Exercise* f = new Func_2(n);
            CRS3_f2->runCRS3(f, false, epsilon, 1);
            delete CRS3_f2;
            delete f;
        }
    }
    return 0;
}
