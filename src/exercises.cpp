#include "../include/exercises.h"
#include <cmath>

using namespace std;

Exercise::Exercise(int n){
    this->n = n;
}

Exercise::~Exercise() {
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

bool Func_1::checkConstraints(vector<double> x){
    bool satisfied = true;
    for(int i=0; i<n; i++){
        satisfied = (x.at(i) >= -40) && (x.at(i) <= 40);
        if(!satisfied)
            break;
    }
    return satisfied;
}

vector<double> Func_1::generatePoint(){
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

bool Func_2::checkConstraints(vector<double> x){
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

vector<double> Func_2::generatePoint(){
    bool correct_point = true;
    vector<double> newPoint;
    double max_value, min_value, currentSum, newCoordinate;
    do{
        newPoint.clear();
        currentSum = 0.0;
        for(int i = n; i>0; i--){
            max_value = findMax(i, currentSum);
            min_value = findMin(i, currentSum);
            double random = (double)rand() / RAND_MAX;
            newCoordinate = min_value + random * (max_value - min_value);
            currentSum += pow((newCoordinate - i),2);
            newPoint.insert(newPoint.begin(), newCoordinate);
            //newPoint.push_back(newCoordinate);
        }
        correct_point = checkConstraints(newPoint);
    }
    while(!correct_point);
    return newPoint;
}

double Func_2::findMax(int i, double sum){
    double maxCons2 = sqrt(n*10-sum) + i;
    if(maxCons2<max_x)
        return maxCons2;
    else
        return max_x;
}

double Func_2::findMin(int i, double sum){
    double minCons2 = -sqrt(n*10-sum) + i;
    if(minCons2<min_x)
        return min_x;
    else
        return minCons2;
}
