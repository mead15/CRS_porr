#include "../include/exercises.h"
#include <cmath>

using namespace std;

Exercise::Exercise(int n){
    this->n = n;
}

Exercise::~Exercise() {
}

bool Exercise::checkConstraints(vector<double> x){
    bool satisfied = true;
    for(int i=0; i<n; i++){
        satisfied = (x.at(i) >= -40) && (x.at(i) <= 40);
        if(!satisfied)
            break;
    }
    return satisfied;
}

vector<double> Exercise::generatePoint(){
    bool correct_point = true;
    vector<double> newPoint;
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

double Func_1::calculate(vector<double> x)
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

double Func_2::calculate(vector<double> x)
{
	double sum = 0.0;
	for (int i = 0; i < n-1; i++)
	{
		sum += (100*pow((x.at(i+1) - (x.at(i)*x.at(i))), 2.0) + pow((1-x.at(i)), 2.0));
	}
	double result = sum;
 	return result;
}