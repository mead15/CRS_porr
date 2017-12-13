#include <iostream>
#include <cstdlib>
#include <ctime>
#include "include/algorithm.h"
#include "include/exercises.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    int n_array[5] = {2, 10, 20, 50, 100};
    srand (time(NULL));

    std::cout << "CRS2" << std::endl;
    for(int n : n_array){
        std::cout << "n = " << n << std::endl;
        std::cout << "Zadanie 1" << std::endl;
        algorithm* CRS2_f1 = new algorithm(n);
        exercise* f = new f1(n);
        CRS2_f1->runCRS2(f);
        delete CRS2_f1;
        delete f;
    }

//    for(int n : n_array){
//        std::cout << "n = " << n << std::endl;
//        std::cout << "Zadanie 2" << std::endl;
//        algorithm* CRS2_f2= new algorithm(n);
//        exercise* f = new f2(n);
//        CRS2_f2->runCRS2(f);
//        delete CRS2_f2;
//        delete f;
//    }
//
//    std::cout << "CRS3" << std::endl;
//    for(int n : n_array){
//        std::cout << "n = " << n << std::endl;
//        std::cout << "Zadanie 1" << std::endl;
//        algorithm* CRS3_f1 = new algorithm(n);
//        exercise* f = new f1(n);
//        CRS3_f1->runCRS3(f);
//        delete CRS3_f1;
//        delete f;
//    }

//    for(int n : n_array){
//        std::cout << "n = " << n << std::endl;
//        std::cout << "Zadanie 2" << std::endl;
//        algorithm* CRS3_f2= new algorithm(n);
//        exercise* f = new f2(n);
//        CRS3_f2->runCRS3(f);
//        delete CRS3_f2;
//        delete f;
//    }

    return 0;
}
