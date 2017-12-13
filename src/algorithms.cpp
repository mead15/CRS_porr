#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../include/algorithms.h"

using namespace std;

void initializeSampleSet(double* sampleSet[], int N, int n);
double CRS2(int n, int N, double (*f)(double*, int), bool (*check_constraints)(double))
{
    /* initialize random seed: */
    srand (time(NULL));
    double **sampleSet;
    sampleSet = new double *[N];
    initializeSampleSet(sampleSet, N, n);
    /*for(int i=0; i<N; i++){
        sampleSet[i] = new double[n];
        for(int j =0; j<n+1; j++){
            if(j<n){
                bool correct_value = false;
                do{
                  double fRand(double fMin, double fMax)
                    {
                    double f = (double)rand() / RAND_MAX;
                    return fMin + f * (fMax - fMin);
                    }
                }
                while(correct_value);
                sampleSet[i][j] = i;
            }
            else
                sampleSet[i][j] = i;//f(1.0, n);
        }
    }*/
    printArray(sampleSet, N, n+1);
    return 0.0;
}

void initializeSampleSet(double* sampleSet [], int N, int n){
    for(int i=0; i<N; i++){
        sampleSet[i] = new double[n+1];
        for(int j =0; j<n+1; j++){
            if(j<n){
               // bool correct_value = false;
                //do{
                  //double fRand(double fMin, double fMax)
                    //{
                    //double f = (double)rand() / RAND_MAX;
                    //return fMin + f * (fMax - fMin);
                    //}
                //}
                //while(correct_value);
                sampleSet[i][j] = 10*i;
            }
            else
                sampleSet[i][j] = i;//f(1.0, n);
        }
    }
}

void printArray(double **a, int rows, int cols){
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            cout << a[i][j] << '\t';
        }
        cout << endl;
    }
}
