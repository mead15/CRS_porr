#ifndef EXERCISES_H
#define EXERCISES_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>

class Exercise{
    public:
        Exercise(int n);
        virtual ~Exercise();
        static constexpr double min_x = -40;
        static constexpr double max_x = 40;
        virtual bool checkConstraints(std::vector<double> x)=0;
        virtual double calculate(std::vector<double> x)=0;
        virtual std::vector<double> generatePoint() = 0;
    protected:
        int n;
};

class Func_1: public Exercise{
    public:
        Func_1(int n):Exercise(n){}
        double calculate(std::vector<double> x);
        bool checkConstraints(std::vector<double> x);
        std::vector<double> generatePoint();
};

class Func_2: public Exercise{
    public:
        Func_2(int n):Exercise(n){}
        double calculate(std::vector<double> x);
        bool checkConstraints(std::vector<double> x);
        std::vector<double> generatePoint();
        double findMax(int i, double sum);
        double findMin(int i, double sum);
};



#endif
