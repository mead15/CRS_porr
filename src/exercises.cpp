#include "../include/exercises.h"
#include <cmath>


exercise::exercise(int n){
    this->n = n;
}

exercise::~exercise() {
}

double f1::calculate(std::vector<double> x)
{
	double sum = 0.0;
	double product = 1.0;
	for (int i = 0; i < n; i++)
	{
		sum += x.at(i) * x.at(i);
		product *= cos(x.at(i) / (i+1));
	}
	double result = sum / 40 + 1 - product;
 	return result;
}

bool f1::checkConstraints(std::vector<double> x){
    bool satisfied = true;
    for(int i=0; i<n; i++){
        satisfied = (x.at(i) >= -40) && (x.at(i) <= 40);
        if(!satisfied)
            break;
    }
    return satisfied;
}

std::vector<double> f1::generatePoint(){
    bool correct_point = true;
    std::vector<double> newPoint;
    do{
        newPoint.clear();
        for(int i =0; i<n; i++){
            double random = (double)rand() / RAND_MAX;
            newPoint.push_back(min_x + random * (max_x - min_x));
        }
        correct_point = checkConstraints(newPoint) ;
    }
    while(!correct_point);
    return newPoint;
}

double f2::calculate(std::vector<double> x)
{
	double sum = 0.0;
	for (int i = 0; i < n-1; i++)
	{
		sum += (100*pow((x.at(i+1) - x.at(i)*x.at(i)), 2.0) + pow((1-x.at(i)), 2.0));
	}
	double result = sum;
 	return result;
}

bool f2::checkConstraints(std::vector<double> x){
    bool satisfied = true, cond1 = true, cond2 = true;
    double sum= 0.0;
    for(int i=0; i<n; i++){
        cond1 = (x.at(i) >= -40) && (x.at(i)<= 40);
        sum += pow((x.at(i)-i+1),2);
        cond2 = (sum <= 10*n);
        if(!cond1 || !cond2)
            break;
    }
    satisfied = cond1 && cond2;
    return satisfied;
}

std::vector<double> f2::generatePoint(){
    bool correct_point = true;
    std::vector<double> newPoint;
    double max_value=max_x, min_value=min_x;
    do{
        newPoint.clear();
        for(int i =0; i<n; i++){
            max_value = findMax(i+1);
            min_value = findMin(i+1);
            double random = (double)rand() / RAND_MAX;
            newPoint.push_back(min_value + random * (max_value - min_value));
        }
        correct_point = checkConstraints(newPoint);
    }
    while(!correct_point);
    return newPoint;
}

double f2::findMax(int i){
    double maxCons2 = sqrt(n*10) + i;
    if(maxCons2<max_x)
        return maxCons2;
    else
        return max_x;
}

double f2::findMin(int i){
    double minCons2 = -sqrt(n*10) + i;
    if(minCons2<min_x)
        return min_x;
    else
        return minCons2;
}
