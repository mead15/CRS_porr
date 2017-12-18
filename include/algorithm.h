#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <utility>
#include <vector>
#include "exercises.h"

using namespace std;
class Algorithm
{
    public:
        Algorithm(int n);
        virtual ~Algorithm();
        void runCRS2(Exercise* f, bool parallel, double epsilon, bool crs3, int numOfThreads);
        void runCRS3(Exercise* f, bool parallel, double epsilon, int numOfThreads);

    protected:

    private:
        int n, N;
        double L_f, H_f;
        vector<double> L, H;
        bool CRS3 = false;
        bool stop_criterion(double i);
        vector<pair<vector<double>, double>> sampleSet;
        Exercise* f;
        vector<vector<double> > simplex;
        void initializeSampleSet();
        void updateLH();
        void loc();
        void sortSet(vector<pair<vector<double>, double> >& setToSort);
        vector<vector<double>> generateSimplex();
        pair<vector<double>, double> getNewTrialPoint(vector<pair<vector<double>, double> > localSampleSet);
        void printArray(vector<pair<vector<double>, double> >& a);
};

#endif // ALGORITHM_H
