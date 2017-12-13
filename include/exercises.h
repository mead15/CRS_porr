#ifndef EXERCISES_H
#define EXERCISES_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>

class exercise{
    public:
        exercise(int n);
        virtual ~exercise();
        static constexpr double min_x = -40;
        static constexpr double max_x = 40;
        virtual bool checkConstraints(std::vector<double> x)=0;
        virtual double calculate(std::vector<double> x)=0;
        virtual std::vector<double> generatePoint() = 0;
    protected:
        int n;
};

class f1: public exercise{
    public:
        f1(int n):exercise(n){}
        double calculate(std::vector<double> x);
        bool checkConstraints(std::vector<double> x);
        std::vector<double> generatePoint();
};

class f2: public exercise{
    public:
        f2(int n):exercise(n){}
        double calculate(std::vector<double> x);
        bool checkConstraints(std::vector<double> x);
        std::vector<double> generatePoint();
        double findMax(int i);
        double findMin(int i);
};



#endif
