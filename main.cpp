#include <iostream>
#include <ctime>
#include "include/algorithm.h"

using namespace std;

int main()
{
    int n_array[1] = {2};//, 10, 20, 50, 100};
    srand (time(NULL));

    std::cout << "CRS2" << std::endl;
    for(int n : n_array){
        std::cout << "n = " << n << std::endl;
        std::cout << "Zadanie 1" << std::endl;
        Algorithm* CRS2_f1 = new Algorithm(n);
        Exercise* f = new Func_1(n);
        CRS2_f1->runCRS2(f);
        delete CRS2_f1;
        delete f;
    }

    for(int n : n_array){
        std::cout << "n = " << n << std::endl;
        std::cout << "Zadanie 2" << std::endl;
        Algorithm* CRS2_f2= new Algorithm(n);
        Exercise* f = new Func_2(n);
        CRS2_f2->runCRS2(f);
        delete CRS2_f2;
        delete f;
    }

    std::cout << "CRS3" << std::endl;
    for(int n : n_array){
        std::cout << "n = " << n << std::endl;
        std::cout << "Zadanie 1" << std::endl;
        Algorithm* CRS3_f1 = new Algorithm(n);
        Exercise* f = new Func_1(n);
        CRS3_f1->runCRS3(f);
        delete CRS3_f1;
        delete f;
    }

    for(int n : n_array){
        std::cout << "n = " << n << std::endl;
        std::cout << "Zadanie 2" << std::endl;
        Algorithm* CRS3_f2= new Algorithm(n);
        Exercise* f = new Func_2(n);
        CRS3_f2->runCRS3(f);
        delete CRS3_f2;
        delete f;
    }
    
    return 0;
}
