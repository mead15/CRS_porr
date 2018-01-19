#include "../include/algorithm.h"
#include <chrono>
#include <fstream>
#include <mpi.h>

using namespace std;

ofstream myfile;

Algorithm::Algorithm(int n)
{
    cout << "Algorithm" << endl;
    this->n = n;
    this->N = 10*(n+1);
    myfile.open ("results1.log", ios::app);

}

Algorithm::~Algorithm()
{
    myfile.close();
}

void Algorithm::runCRS2(Exercise* f, bool parallel, double epsilon, bool crs3, int numOfThreads)
{
    myfile<<"1";
    using namespace std::chrono;
    high_resolution_clock::time_point start = high_resolution_clock::now();
    myfile<<"2";
    this->f = f;
    int counter = 0;
    myfile<<"3";
    initializeSampleSet();
    myfile<<"4";
    sortSet(sampleSet);
    myfile<<"5";
    updateLH();
    myfile<<"1";
    int i = N/10;
    do {
        /* **********************************************************************
         * PARALLEL Ustawianie w pliku include/constants.h
         */
        if (parallel) {
            int received = 0;
            int world_size;
            MPI_Comm_size(MPI_COMM_WORLD, &world_size);
            int threadsNum = world_size-1;
            vector<pair<vector<double>, double>> candidates(threadsNum);
            for (int z=1; z< world_size; z++){
                myfile << "TESTEES" << &getSampleSet()[0][0];
                MPI_Send(&getSampleSet()[0][0] ,N*(n+1), MPI_DOUBLE, z, 0, MPI_COMM_WORLD);
            }
            for(int z=1; z< world_size; z++) {
                double *candidate;
                MPI_Recv(&candidate, (n + 1), MPI_DOUBLE, z, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                pair<vector<double>, double> newCandidate;
                newCandidate.second = candidate[0];
                for (int i = 0; i < n; i++) {
                    newCandidate.first.push_back(candidate[i + 1]);
                }
                candidates.push_back(newCandidate);
                received++;
            }
            while(received < threadsNum){

            }

            sampleSet.insert(sampleSet.end(), candidates.begin(), candidates.end());
            sortSet(sampleSet);
            sampleSet.resize(N);
            if (crs3){

                for (int index = 0; index< candidates.size(); index++){
                    if(candidates[index].second <= sampleSet.at(i-1).second){
                        loc();
                    }
                }
            }
            updateLH();
            counter+=numOfThreads;
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
    myfile << "Liczba krokow: " << counter << endl << "Czas trwania: " << duration << "ms" << endl;
    myfile << "*********************************************************" << endl;
}

void Algorithm::runCRS3(Exercise* f, bool parallel, double epsilon, int numOfThreads)
{
//    this->CRS3 = true;
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
    std::cout<<"generateSimplex" << std::endl;
    vector<vector<double> > simplex;
    vector<int> simplex_indexes;
    for(int i = 0; i<n; i++){
        int newIndex;
        bool nodups = false;
        while(!nodups){
            for(int k=0; k<i; k++){
                simplex_indexes.push_back(0);
            }
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
    std::cout<<"generateSimplex push_back" << localSampleSet.size() << std::endl;
    for(int i=1; i<n+1; i++){
        simplex.push_back(localSampleSet.at(simplex_indexes.at(i-1)).first);
    }
    std::cout<<"generateSimplex end" << std::endl;
    return simplex;
}

pair<vector<double>, double> Algorithm::getNewTrialPoint(vector<pair<vector<double>, double> > sampleSet){
    std::cout << "getNewTrialPoint init" << std::endl;
    vector<vector<double> > simplex = generateSimplex(sampleSet);
    std::cout << "getNewTrialPoint simplex" << simplex.size() << std::endl;
    vector<double> centroid, newTrial, sum;
    for(int i=0; i<n; i++)
        sum.push_back(0.0);
    double newTrialValue = 0.0;
    std::cout << "getNewTrialPoint newTrialValue" << std::endl;
    for (int z=0; z<simplex.size();z++){
        for (vector<double>::const_iterator i = simplex.at(z).begin(); i != simplex.at(z).end(); ++i){
            std::cout << *i << ", ";
        }
        std::cout << "\n";
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++) {
            sum.at(i) += simplex.at(j).at(i);
        }
        centroid.push_back(sum.at(i)/n);
        newTrial.push_back(2*centroid.at(i)-simplex.at(n).at(i));
    }
    std::cout << "getNewTrialPoint after fors" << std::endl;
    newTrialValue = f->calculate(newTrial);
    std::cout << "getNewTrialPoint2" << std::endl;
    if(!f->checkConstraints(newTrial) || newTrialValue>H_f){
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
    myfile  << "x_min = [";
    for(int i=0; i<n; i++)
        myfile << L.at(i) << ", ";
    myfile << "\b\b]" << '\t' << "f_min = " << L_f << endl;
    myfile << "Roznica pomiedzy najlepszym i najgorszym  wynikiem w zbiorze P: " << H_f-L_f << endl;
}


double **Algorithm::getSampleSet(){
    std::cout << "getSampleSet" << std::endl;
    double *data = (double *)malloc(N*(n+1)*sizeof(double));
    double **array= (double **)malloc(N*sizeof(double*));
    for(int i=0; i<N; i++){
        array[i] = &(data[(n+1)*i]);
        array[i][0] = sampleSet.at(i).second;
        for(int j=0; j<n; j++){
            array[i][j+1] = sampleSet.at(i).first.at(j);
        }
    }
    return array;
}

vector<pair<vector<double>, double>> Algorithm::setSampleSet(double **localSampleSet){
    std::cout << "setSampleSet" << std::endl;
    vector<pair<vector<double>, double>> toRet;
    for(int i=0; i<N; i++){
        double value = localSampleSet[i][0];
        vector<double> point;
        for(int j=0; j<n; j++){
            point.push_back(localSampleSet[i][j+1]);
        }
        toRet.push_back(make_pair(point, value));
    }
    std::cout << "end setSampleSet" << std::endl;
    return toRet;
};