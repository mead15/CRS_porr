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
        std::vector<double> L, H;
        bool CRS3 = false;
        bool stop_criterion();
        std::vector<std::pair<std::vector<double>, double> > sampleSet;
        Exercise* f;
        std::vector<std::vector<double> > simplex;
        std::vector<std::pair<std::vector<double>, double> > simplex_CRS3;
        void initializeSampleSet();
        void updateLH();
        void loc();
        void sortSet(std::vector<std::pair<std::vector<double>, double> >& setToSort);
        void setSimplex();
        void getNewTrialPoint();
        void printArray(std::vector<std::pair<std::vector<double>, double> >& a);
};

#endif // ALGORITHM_H
