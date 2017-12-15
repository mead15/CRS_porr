#include "../include/algorithm.h"
#include <chrono>

Algorithm::Algorithm(int n)
{
    this->n = n;
    this->N = 10*(n+1);

}

Algorithm::~Algorithm()
{
}

void Algorithm::runCRS2(Exercise* f)
{
    using namespace std::chrono;
    high_resolution_clock::time_point start = high_resolution_clock::now();
    this->f = f;
    int counter = 0;
    initializeSampleSet();
    sortSet(sampleSet);
    updateLH();
    printArray(sampleSet);
    do{
        getNewTrialPoint();
        counter++;
        updateLH();
    }
    while(!stop_criterion());
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<microseconds>( end - start ).count()/ 1000;
    printArray(sampleSet);
    std::cout << "Liczba krokow: " << counter << std::endl << "Czas trwania: " << duration << "ms" << std::endl;
}

void Algorithm::runCRS3(Exercise* f)
{
    this->CRS3 = true;
    runCRS2(f);
}

bool Algorithm::stop_criterion(){
    return( (H_f - L_f) < 1e-6);
}

void Algorithm::initializeSampleSet(){
    sampleSet.clear();
    std::vector<double> point;
    for(int i=0; i<N; i++){
        point = f->generatePoint();
        double value = f->calculate(point);
        sampleSet.push_back(std::make_pair(point, value));
    }
}

void Algorithm::sortSet(std::vector<std::pair<std::vector<double>, double> >& setToSort){
    int changes = 0;
    std::pair<std::vector<double>, double> smaller;
    do{
        changes = 0;
        int len = setToSort.size();
        for (int i=0; i<len-1; i++) {
            if(setToSort.at(i).second > setToSort.at(i+1).second){
                smaller = setToSort.at(i+1);
                setToSort.at(i+1) = setToSort.at(i);
                setToSort.at(i) = smaller;
                changes += 1;
            }
        }
    }
    while(changes != 0);
}

void Algorithm::updateLH(){
    L = sampleSet.at(0).first;
    H = sampleSet.at(N-1).first;
    L_f = sampleSet.at(0).second;
    H_f = sampleSet.at(N-1).second;
}

void Algorithm::setSimplex(){
    simplex.clear();
    std::vector<int> simplex_indexes;
    for(int i = 0; i<n; i++){
        int newIndex;
        bool nodups = false;
        while(!nodups){
            nodups = true;
            newIndex = rand() % (N-1) +1;
            for(int k=0; k<i; k++){
                if(simplex_indexes.at(k) == newIndex){
                    nodups = false;
                    break;
                }
            }
        }
        simplex_indexes.push_back(newIndex);
    }
    simplex.push_back(L);
    for(int i=1; i<n+1; i++){
        simplex.push_back(sampleSet.at(simplex_indexes.at(i-1)).first);
    }
}

void Algorithm::getNewTrialPoint(){
    setSimplex();
    std::vector<double> centroid, newTrial, sum;
    for(int i=0; i<n; i++)
        sum.push_back(0.0);
    double newTrialValue = 0.0;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++)
            sum.at(i) += simplex.at(j).at(i);
        centroid.push_back(sum.at(i)/n);
        newTrial.push_back(2*centroid.at(i)-simplex.at(n).at(i));
    }
    newTrialValue = f->calculate(newTrial);

    if(!f->checkConstraints(newTrial) || newTrialValue>H_f){
        newTrial.clear();
        getNewTrialPoint();
    }
    else{
        sampleSet.at(N-1).first = newTrial;
        sampleSet.at(N-1).second = newTrialValue;
        sortSet(sampleSet);
        if (CRS3){
            int i = N/10;
            if(newTrialValue <= sampleSet.at(i-1).second){
                loc();
            }
        }
    }
}

void Algorithm::loc(){
    std::vector<double> W, G, S, P, Q, R, sum, newTrial;
    double S_f, P_f, Q_f, R_f, newTrialValue;

    bool refreshSimplex, hasChanged=false;
    int sim_size = N/10;

    for(int i=0; i<sim_size; i++){
        simplex_CRS3.push_back(sampleSet.at(i));
    }

    do {
        refreshSimplex = false;
        W = simplex_CRS3.at(sim_size - 1).first;
        S = simplex_CRS3.at(sim_size - 2).first;
        S_f = simplex_CRS3.at(sim_size - 2).second;

        for (int i = 0; i < n; i++)
            sum.push_back(0.0);
        for (int i = 0; i < sim_size - 1; i++) {
            for (int j = 0; j < n; j++)
                sum.at(i) += simplex_CRS3.at(j).first.at(i);
            G.push_back(sum.at(i) / n);
        }
        for (int i = 0; i < n; i++) {
            P.push_back(2 * G.at(i) - W.at(i));
            Q.push_back((G.at(i) + W.at(i)) / 2);
            R.push_back(4 * G.at(i) - 3 * W.at(i));
        }

        if (f->checkConstraints(P)) {
            P_f = f->calculate(P);
            if (P_f < S_f) {
                if (f->checkConstraints(R)) {
                    R_f = f->calculate(R);
                    if (R_f < S_f) {
                        newTrial = R;
                        newTrialValue = R_f;
                        refreshSimplex = true;
                    }
                    else {
                        newTrial = P;
                        newTrialValue = P_f;
                        refreshSimplex = true;
                    }
                }
                else {
                    newTrial = P;
                    newTrialValue = P_f;
                    refreshSimplex = true;
                }
            }
            else {
                if (f->checkConstraints(Q)) {
                    Q_f = f->calculate(Q);
                    if (Q_f < S_f) {
                        newTrial = Q;
                        newTrialValue = Q_f;
                        refreshSimplex = true;
                    }
                    else {
                        //stop
                    }
                }
                else {
                    //stop
                }
            }
        }
        else {
            if (f->checkConstraints(Q)) {
                Q_f = f->calculate(Q);
                if (Q_f < S_f) {
                    newTrial = Q;
                    newTrialValue = Q_f;
                    refreshSimplex = true;
                }
                else {
                    //stop
                }
            }
            else {
                //stop
            }
        }
        if(refreshSimplex) {
            hasChanged = true;
            simplex_CRS3.at(sim_size - 1).first = newTrial;
            simplex_CRS3.at(sim_size - 1).second = newTrialValue;
            sortSet(simplex_CRS3);
        }
    } while(refreshSimplex);

    if(hasChanged){
        for(int i=0; i<sim_size; i++)
            sampleSet.at(i)=simplex_CRS3.at(i);
    }
    simplex_CRS3.clear();
}

void Algorithm::printArray(std::vector<std::pair<std::vector<double>, double> >& a){
    int len = a.size();
/*    if(n<50){
        for(int i=0; i<len; i++){
            for(int j=0; j<n; j++){
                std::cout << std::setw(8) << a.at(i).first.at(j) << '\t';
            }
            std::cout << std::setw(12) << a.at(i).second;
            std::cout << std::endl;
        }
    }*/
    std::cout << std::endl;
    for(int i=0; i<n; i++)
        std::cout  << L.at(i) << '\t';
    std::cout << std::endl << H_f-L_f << '\t' << L_f << std::endl <<std::endl;
}
