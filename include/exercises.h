#ifndef EXERCISES_H
#define EXERCISES_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Exercise{
    public:
        Exercise(int n);
        virtual ~Exercise();
        static constexpr double min_x = -40;
        static constexpr double max_x = 40;
        bool checkConstraints(vector<double> x);
        virtual double calculate(vector<double> x)=0;
        vector<double> generatePoint();
    protected:
        int n;
};

class Func_1: public Exercise{
    public:
        Func_1(int n):Exercise(n){}
        double calculate(vector<double> x);
};

class Func_2: public Exercise{
    public:
        Func_2(int n):Exercise(n){}
        double calculate(vector<double> x);
};



#endif
