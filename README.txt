Kompilacja z poziomu projektu:
mpic++ main.cpp src/algorithm.cpp src/exercises.cpp -std=c++11 -o crs.out
uruchomienie dla N wątków:
mpiexec -n N crs.out