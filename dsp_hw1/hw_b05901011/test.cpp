#include "hmm.h"
#include <math.h>
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;
const int state_num = 6;
const int time_num = 50;
const int observation_num = 6;

double viterbi(string s, HMM model){
    double delta[time_num][state_num];
    int o = s[0] - 'A';
    for(int i = 0; i < state_num; i++){
        delta[0][i] = model.initial[i] * model.observation[o][i];
        // printf("delta[%d][%d] = %f\n", 0, i, delta[0][i]);
    }
    double max_p = 0;
    for(int t = 1; t < time_num; t++){
        int o = s[t] - 'A';
        for(int i = 0; i < state_num; i++){
            delta[t][i] = 0;
            for(int j = 0; j < state_num; j++){
                delta[t][i] = max(delta[t][i], delta[t - 1][j] * model.transition[j][i]);
            }
            delta[t][i] *= model.observation[o][i];
            // printf("delta[%d][%d] = %e\n", t, i, delta[t][i]);
            if(t == time_num - 1){
                max_p = max(max_p, delta[t][i]);
            }
        }
    }
    return max_p;
}
//  ./test modellist.txt ../testing_data2.txt result2.txt
int main(int argc, char *argv[])
{
	HMM hmms[5];
	load_models(argv[1], hmms, 5);
    ifstream data(argv[2]);
    ofstream result(argv[3]);
    string s;
    while(data >> s){
        double max_p = 0;
        int max_index = 0;
        for(int i = 0; i < 5; i++){
            double p = viterbi(s, hmms[i]);
            if(p > max_p){
                max_index = i;
                max_p = p;
            }
        }
        result << "model_0" << max_index + 1<< ".txt " << max_p << endl;
    }
	return 0;
}
