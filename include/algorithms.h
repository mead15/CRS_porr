#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <iostream>
#include <cstdlib>
#include <ctime>

double CRS2(int n, int N, double (*f)(double*, int), bool (*check_constraints)(double), double min_x, double max_x);
void printArray(double **a, int rows, int cols);

#endif // ALGORITHMS_H
