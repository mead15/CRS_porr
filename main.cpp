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
    ofstream myfile;
    myfile.open ("results1.log", ios::app);
    int threadNum = 2;
    double epsilon = EPSILON[1];
//    for (int n : N_ARRAY) {
    int n = N_ARRAY[0];
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

//                myfile << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"
//                          << std::endl << std::endl;
//                myfile << "Zadanie 1" << std::endl;
//                myfile << "Rownolegle CRS3" << std::endl;
//                myfile << "Epsilon: " << epsilon << std::endl;
//                myfile << "Liczba watkow: " << threadNum << endl;
//                myfile << "n = " << n << std::endl;
//                if(1)
//                {
//                    Algorithm *CRS3_f1 = new Algorithm(n);
//                    Exercise *f = new Func_1(n);
//                    CRS3_f1->runCRS3(f, true, epsilon, threadNum);
//                    delete CRS3_f1;
//                    delete f;
//                }

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

//    }
    myfile.close();
    return 0;
}
