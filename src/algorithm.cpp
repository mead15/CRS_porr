#include "../include/algorithm.h"
#include <chrono>
#include <fstream>
#include <mpi.h>

using namespace std;

Algorithm::Algorithm(int n, Exercise* f)
{
    this->n = n;
    this->N = 10*(n+1);
    this->f = f;
}

Algorithm::~Algorithm()
{
}

void Algorithm::runCRS2(Exercise* f, bool parallel, double epsilon, bool crs3, int numOfThreads)
{
    using namespace std::chrono;
    high_resolution_clock::time_point start = high_resolution_clock::now();
    this->f = f;
    initializeSampleSet();
    sortSet(sampleSet);
    updateLH();
    int i = N/10;
    MPI_Init(NULL, NULL);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    srand (time(NULL));
    int counter = 0;

    do {
        /* **********************************************************************
         * PARALLEL Ustawianie w pliku include/constants.h
         */
        if (parallel) {
            double localSampleSet[(n+1)*N];
            double candidatesBuffer[world_size*(n+1)];
            for(int j=0; j<N; j++){
                localSampleSet[j*(n+1)] = sampleSet.at(j).second;
                vector<double> vec = sampleSet.at(j).first;
                for(int i=0; i<n; i++){
                    localSampleSet[j*(n+1)+ i+1] = vec.at(i);
                }
            }
            MPI_Bcast(localSampleSet, N*(n+1), MPI_DOUBLE, 0, MPI_COMM_WORLD );
            MPI_Barrier(MPI_COMM_WORLD);
            pair<vector<double>, double> newCandidate = getNewTrialPoint(setSampleSet(localSampleSet));
            double candidate[n+1];
            candidate[0] = newCandidate.second;
            for (int i=0; i<n; i++){
                candidate[i+1] = newCandidate.first.at(i);
            }
            MPI_Barrier(MPI_COMM_WORLD);
            MPI_Gather(candidate, n+1, MPI_DOUBLE, candidatesBuffer, n+1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
            MPI_Barrier(MPI_COMM_WORLD);
            if (world_rank == 0) {
                vector<pair<vector<double>, double>> candidates;
                for (int z = 0; z < world_size * (n + 1); z += n + 1) {
                    pair<vector<double>, double> newCandidatePoint;
                    newCandidatePoint.second = candidatesBuffer[z];
                    for (int i = 0; i < n; i++) {
                        newCandidatePoint.first.push_back(candidatesBuffer[z + i + 1]);
                    }
                    candidates.push_back(newCandidatePoint);
                }
//                if (counter > 100){
//                    return;
//                }
//                for (pair<vector<double>, double> pair1: sampleSet){
//                    for (double value: pair1.first){
//                        cout << value << ", ";
//                    }
//                    cout << endl;
//
//                }
//                cout << endl;cout << endl;cout << endl;
                sampleSet.insert(sampleSet.end(), candidates.begin(), candidates.end());
                sortSet(sampleSet);
                sampleSet.resize(N);

                if (crs3) {
                    for (int index = 0; index < candidates.size(); index++) {
                        if (candidates[index].second <= sampleSet.at(i - 1).second) {
                            loc();
                        }
                    }
                }
                updateLH();
                counter += world_size;
            }
            MPI_Barrier(MPI_COMM_WORLD);

        }
        /* ***********************************************************************
         * END OF PARALLEL
         */

        /* **********************************************************************
         * SEQUENCE
         */
        else {

            pair<vector<double>, double> candidate = getNewTrialPoint(sampleSet);
            sampleSet.at(N - 1).first = candidate.first;
            sampleSet.at(N - 1).second = candidate.second;
            sortSet(sampleSet);
            if (crs3) {
                if (candidate.second <= sampleSet.at(i - 1).second) {
                    loc();
                }
            }
            updateLH();
            counter++;
        }
        /* ***********************************************************************
         * END OF SEQUENCE
         */
    }
    while(!stop_criterion(epsilon));
    high_resolution_clock::time_point end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>( end - start ).count()/ 1000;
    printArray(sampleSet);

    cout << "Liczba krokow: " << counter << endl << "Czas trwania: " << duration << "ms" << endl;
    cout << "*********************************************************" << endl;

}

void Algorithm::runCRS3(Exercise* f, bool parallel, double epsilon, int numOfThreads)
{
    this->CRS3 = true;
    runCRS2(f, parallel, epsilon, true, numOfThreads);
}

bool Algorithm::stop_criterion(double epsilon){
    return( (H_f - L_f) < epsilon);
}

void Algorithm::initializeSampleSet(){
    sampleSet.clear();
    vector<double> point;
    for(int i=0; i<N; i++){
        point = f->generatePoint();
        double value = f->calculate(point);
        sampleSet.push_back(make_pair(point, value));
    }
}

void Algorithm::sortSet(vector<pair<vector<double>, double> >& setToSort){
    int changes = 0;
    pair<vector<double>, double> smaller;
    do{
        changes = 0;
        unsigned long long int len = setToSort.size();
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



vector<vector<double>> Algorithm::generateSimplex(vector<pair<vector<double>, double>> localSampleSet){
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 1000);
    vector<vector<double>> simplex;
    vector<int> simplex_indexes;
    vector<double> loc_L = localSampleSet.at(0).first;

    for(int i = 0; i<n; i++){
        int newIndex;
        bool nodups = false;
        while(!nodups){
//            for(int k=0; k<i; k++){
//                simplex_indexes.push_back(0);
//            }
            nodups = true;
            newIndex = dist(mt) % (N-1) +1;
            for(int k=0; k<i; k++){
                if(simplex_indexes.at(k) == newIndex){
                    nodups = false;
                    break;
                }
            }
        }
        simplex_indexes.push_back(newIndex);
    }
    simplex.push_back(loc_L);
    for(int i=1; i<n+1; i++){
        simplex.push_back(localSampleSet.at(simplex_indexes.at(i-1)).first);
    }
    return simplex;
}

pair<vector<double>, double> Algorithm::getNewTrialPoint(vector<pair<vector<double>, double> > sampleSet){
    vector<vector<double> > simplex = generateSimplex(sampleSet);
    vector<double> centroid, newTrial, sum;
    double loc_H_f = sampleSet.at(N-1).second;
    for(int i=0; i<n; i++)
        sum.push_back(0.0);
    double newTrialValue = 0.0;

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++)
            sum.at(i) += simplex.at(j).at(i);
        centroid.push_back(sum.at(i)/n);
        newTrial.push_back(2*centroid.at(i)-simplex.at(n).at(i));
    }



//    vector< vector<double> >::iterator row;
//    vector<double>::iterator col;
//    int outer_counter=0, inner_counter = 0;
//    for (row = simplex.begin(); row != simplex.end(); row++) {
//        for (col = row->begin(); col != row->end(); col++) {
//            sum.at(inner_counter) += *col;
//            inner_counter++;
//        }
//        outer_counter++;
//        inner_counter = 0;
//    }
//
//
//    for(int i=0; i<n; i++){
//        centroid.push_back(sum.at(i)/n);
//        newTrial.push_back(2*centroid.at(i)-simplex.at(n).at(i));
//    }

    newTrialValue = f->calculate(newTrial);
    if(!f->checkConstraints(newTrial) || newTrialValue>loc_H_f){
        return getNewTrialPoint(sampleSet);
    }
    else{
        pair<vector<double>, double> para;
        para.first = newTrial;
        para.second = newTrialValue;
        return para;

    }
}

void Algorithm::loc(){
    vector<double> W, G, S, P, Q, R, sum, newTrial;
    double S_f, P_f, Q_f, R_f, newTrialValue;
    vector<pair<vector<double>, double> > simplex_CRS3;
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
            }
        }
        if(refreshSimplex) {
            hasChanged = true;
            simplex_CRS3.at(sim_size - 1).first = newTrial;
            simplex_CRS3.at(sim_size - 1).second = newTrialValue;
            sortSet(simplex_CRS3);
        }
    } while(refreshSimplex);

    if(hasChanged) {
        for (int i = 0; i < sim_size; i++) {
            sampleSet.at(i).first = simplex_CRS3.at(i).first;
            sampleSet.at(i).second = simplex_CRS3.at(i).second;
        }
    }
    simplex_CRS3.clear();
}

void Algorithm::printArray(vector<pair<vector<double>, double> >& a){
/*    int len = a.size();
    if(n<50){
        for(int i=0; i<len; i++){
            for(int j=0; j<n; j++){
                cout << setw(8) << a.at(i).first.at(j) << '\t';
            }
            cout << setw(12) << a.at(i).second;
            cout << endl;
        }
    }*/
    cout  << "x_min = [";
    for(int i=0; i<n; i++)
        cout << L.at(i) << ", ";
    cout << "\b\b]" << '\t' << "f_min = " << L_f << endl;
    cout << "Roznica pomiedzy najlepszym i najgorszym  wynikiem w zbiorze P: " << H_f-L_f << endl;
}

vector<pair<vector<double>, double>> Algorithm::setSampleSet(double localSampleSet[]){
    vector<pair<vector<double>, double>> toRet;
    for(int i=0; i<N; i++){
        double value = localSampleSet[i*(n+1)];
        vector<double> point(n);
        for(int j=0; j<n; j++){
            point.at(j) = localSampleSet[i*(n+1)+j+1];
        }
        toRet.push_back(make_pair(point, value));
    }
    return toRet;
};