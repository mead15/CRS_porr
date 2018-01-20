#include <iostream>
#include <ctime>
#include "include/algorithm.h"
#include <fstream>

using namespace std;

static const int N_ARRAY[5] = {2, 10, 20, 50, 100};
static const double EPSILON[4] = {1e-2, 1e-4, 1e-6, 1e-8};


int main(int argc, char** argv)
{
    srand (time(NULL));
    int threadNum = 2;
    double epsilon = EPSILON[1];
//    for (int n : N_ARRAY) {
    int n = N_ARRAY[0];
    cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"
              << std::endl << std::endl;
    cout << "Zadanie 1 " << std::endl;
    cout << "Rownolegle CRS2" << std::endl;
    cout << "Epsilon: " << epsilon << std::endl;
    cout << "Liczba watkow: " << threadNum << endl;
    cout << "n = " << n << std::endl;
    if(1)
    {
        cout << "a1" << std::endl;
        Algorithm *CRS2_f1 = new Algorithm(n);
        cout << "a2" << std::endl;

        Exercise *f = new Func_1(n);
        cout << "a3" << std::endl;

        CRS2_f1->runCRS2(f, true, epsilon, false, threadNum);
        cout << "a4" << std::endl;

        delete CRS2_f1;
        delete f;
    }
//                cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"
//                          << std::endl << std::endl;
//                cout << "Zadanie 2" << std::endl;
//                cout << "Rownolegle CRS2" << std::endl;
//                cout << "Epsilon: " << epsilon << std::endl;
//                cout << "Liczba watkow: " << threadNum << endl;
//                cout << "n = " << n << std::endl;
//                {
//                    Algorithm *CRS2_f2 = new Algorithm(n);
//                    Exercise *f = new Func_2(n);
//                    CRS2_f2->runCRS2(f, true, epsilon, false, threadNum);
//                    delete CRS2_f2;
//                    delete f;
//                }

//                cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"
//                          << std::endl << std::endl;
//                cout << "Zadanie 1" << std::endl;
//                cout << "Rownolegle CRS3" << std::endl;
//                cout << "Epsilon: " << epsilon << std::endl;
//                cout << "Liczba watkow: " << threadNum << endl;
//                cout << "n = " << n << std::endl;
//                if(1)
//                {
//                    Algorithm *CRS3_f1 = new Algorithm(n);
//                    Exercise *f = new Func_1(n);
//                    CRS3_f1->runCRS3(f, true, epsilon, threadNum);
//                    delete CRS3_f1;
//                    delete f;
//                }

//                cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"
//                          << std::endl << std::endl;
//                cout << "Zadanie 2" << std::endl;
//                cout << "Rownolegle CRS3" << std::endl;
//                cout << "Epsilon: " << epsilon << std::endl;
//                cout << "Liczba watkow: " << threadNum << endl;
//                cout << "n = " << n << std::endl;
//                {
//                    Algorithm *CRS3_f2 = new Algorithm(n);
//                    Exercise *f = new Func_2(n);
//                    CRS3_f2->runCRS3(f, true, epsilon, threadNum);
//                    delete CRS3_f2;
//                    delete f;
//                }

//    }
    return 0;
}
