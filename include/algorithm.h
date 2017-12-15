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
        void runCRS2(Exercise* f);
        void runCRS3(Exercise* f);

    protected:

    private:
        int n, N;
        double L_f, H_f;
        vector<double> L, H;
        bool CRS3 = false;
        bool stop_criterion();
        vector<pair<vector<double>, double> > sampleSet;
        Exercise* f;
        vector<vector<double> > simplex;
        vector<pair<vector<double>, double> > simplex_CRS3;
        void initializeSampleSet();
        void updateLH();
        void loc();
        void sortSet(vector<pair<vector<double>, double> >& setToSort);
        vector<vector<double>> generateSimplex();
        pair<vector<double>, double> getNewTrialPoint(vector<pair<vector<double>, double> > localSampleSet);
        void printArray(vector<pair<vector<double>, double> >& a);
};

#endif // ALGORITHM_H
