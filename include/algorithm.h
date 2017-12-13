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


class algorithm
{
    public:
        algorithm(int n);
        virtual ~algorithm();
        void runCRS2(exercise* f);
        void runCRS3(exercise* f);

    protected:

    private:
        int n, N;
        double L_f, H_f;
        std::vector<double> L, H;
        bool CRS3 = false;
        std::vector<std::pair<std::vector<double>, double> > sampleSet;
        exercise* f;
        std::vector<std::vector<double> > simplex;
        void initializeSampleSet();
        void updateLH();
        void loc();
        void sortSet(std::vector<std::pair<std::vector<double>, double> >& setToSort);
        void setSimplex();
        void getNewTrialPoint();
        void printArray(std::vector<std::pair<std::vector<double>, double> >& a);
};

#endif // ALGORITHM_H
