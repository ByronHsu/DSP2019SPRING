#include "hmm.h"
#include <math.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdlib.h> 

using namespace std;

// global variable: frequently used in functions    
vector< vector<int> > data;
HMM model;
const int state_num = 6;
const int time_num = 50;
const int observation_num = 6;

void train_sample(vector<int> &seq, double *sigma_gamma_0, double sigma_epsilon[][state_num], double *sigma_gamma, double sigma_gamma_eqo[][observation_num]){
    // Calculate alpha(dim: state x time = 6 x 50)
    double alpha[time_num][state_num];
    for(int t = 0; t < time_num; t++){
        int o = seq[t];
        for(int i = 0; i < state_num; i++){
            if(t == 0){
                alpha[t][i] = model.initial[i] * model.observation[o][i];
            }else{
                // now is at alpha[t][i]
                // alpha[t][i] = sigma(alpha[t-1][j] * trans[j][i]) * b[ot][i]
                double sum = 0;
                for(int j = 0; j < state_num; j++){
                    sum += model.transition[j][i] * alpha[t - 1][j];
                }
                alpha[t][i] = sum * model.observation[o][i];
            }
            // printf("alpha[%d][%d] = %f\n", t, i, alpha[t][i]);
        }
    }
    // Calculate beta(dim: state x time)
    double beta[time_num][state_num];
    for(int t = time_num - 1; t >= 0; t--){
        for(int i = 0; i < state_num; i++){
            if(t == time_num - 1){
                beta[t][i] = 1;
            }else{
                int o_next = seq[t + 1];
                // now is at beta[t][i]
                // beta[t][i] = sigma(trans[i][j]) * beta[t + 1][j] * b[o_t+1][j])
                double sum = 0;
                for(int j = 0; j < state_num; j++){
                    sum += model.transition[i][j] * beta[t + 1][j] * model.observation[o_next][j];
                }
                beta[t][i] = sum;
            }
            // printf("beta[%d][%d] = %f\n", t, i, beta[t][i]);
        }
    }
    // Check whether sigma(alpha[t][i] * beta[t][i]) is the same with model.transition fixed t
    /* DEBUG
    for(int t = 0; t < time_num; t++){
        double total_sum = 0;
        for(int i = 0; i < state_num; i++){
            total_sum += alpha[t][i] * beta[t][i];
        }
        cout << "at time = " << t << " probability is " << total_sum << endl;
    }
    */
    // Calculate gamma(dim: state x time)
    double gamma[time_num][state_num];
    for(int t = 0; t < time_num; t++){
        double total_sum = 0;
        for(int i = 0; i < state_num; i++){
            total_sum += alpha[t][i] * beta[t][i];
        }
        for(int i = 0; i < state_num; i++){
            gamma[t][i] = alpha[t][i] * beta[t][i] / total_sum;
            // printf("gamma[%d][%d] = %f\n", t, i, gamma[t][i]);
        }
    }
    // Calculate epsilon(dim: time - 1 x state x state)
    double epsilon[time_num - 1][state_num][state_num];
    for(int t = 0; t < time_num - 1; t++){
        double sum = 0;
        int o_next = seq[t + 1];
        for(int i = 0; i < state_num; i++){
            for(int j = 0; j < state_num; j++){
                sum += alpha[t][i] * model.transition[i][j] * model.observation[o_next][j] * beta[t + 1][j];
            }
        }
        for(int i = 0; i < state_num; i++){
            for(int j = 0; j < state_num; j++){
                epsilon[t][i][j] = alpha[t][i] * model.transition[i][j] * model.observation[o_next][j] * beta[t + 1][j] / sum;
                // printf("epsilon[%d][%d][%d] = %f\n", t, i, j, epsilon[t][i][j]);
            }
        }
    }
    // update sigma_gamma_0
    for(int i = 0; i < state_num; i++){
        sigma_gamma_0[i] += gamma[0][i];
    }
    
    // update sigma_epsilon
    for(int i = 0; i < state_num; i++){
        for(int j = 0; j < state_num; j++){
            for(int t = 0; t < time_num - 1; t++){
                sigma_epsilon[i][j] += epsilon[t][i][j];
            }
        }
    }
    // update sigma_gamma
    for(int i = 0; i < state_num; i++){
        for(int t = 0; t < time_num - 1; t++){
            sigma_gamma[i] += gamma[t][i];
        }
    } 
    
    // update sigma_gamma_eqo
    for(int k = 0; k < observation_num; k++){
        for(int i = 0; i < state_num; i++){
            for(int t = 0; t < time_num - 1; t++){
                if(seq[t] == k)
                    sigma_gamma_eqo[k][i] += gamma[t][i];
            }
        }
    }
}

void train_epoch(){
    // TODO: initialize as zero
    double sigma_gamma_0[state_num] = {0};
    double sigma_epsilon[state_num][state_num] = {0};
    double sigma_gamma[state_num] = {0};
    double sigma_gamma_eqo[observation_num][state_num] = {0}; // state equals to observation
    for(int i = 0; i < data.size(); i++){
        train_sample(data[i], sigma_gamma_0, sigma_epsilon, sigma_gamma, sigma_gamma_eqo);
    }

    printf("PI\n");
    double sum = 0;
    for(int i = 0; i < state_num; i++){
        model.initial[i] = sigma_gamma_0[i] / data.size(); // data size equals to sample numbers
        sum += model.initial[i];
        printf("%f ", model.initial[i]);
    }
    printf("sum = %f", sum);
    printf("\n");
    
    printf("A\n");
    for(int i = 0; i < state_num; i++){
        double sum = 0;
        for(int j = 0; j < state_num; j++){
            model.transition[i][j] = sigma_epsilon[i][j] / sigma_gamma[i];
            sum += model.transition[i][j];
            printf("%f ", model.transition[i][j]);
        }
        printf("sum = %f", sum);
        printf("\n");
    }

    printf("B\n");
    
    for(int k = 0; k < observation_num; k++){
        for(int i = 0; i < state_num; i++){
            model.observation[k][i] = sigma_gamma_eqo[k][i] / sigma_gamma[i];
            printf("%f ", model.observation[k][i]);
        }
        printf("\n");
    }

    // CHECK COLUMN SUM = 1
    for(int i = 0; i < state_num; i++){
        double sum = 0;
        for(int k = 0; k < observation_num; k++){
            sum += model.observation[k][i];
        }
        printf("%f ", sum);
    }
    printf("\n");
}

void train(int iter){
    for(int i = 0; i < iter; i++)
        train_epoch();
}
/*
Execution format:
 ./train $iter model_init.txt seq_model_01.txt model_01.txt
*/
int main(int argc, char *argv[])
{
    /* Read init model */
    loadHMM( &model, argv[2] );
    
    /* Read training data */
    ifstream seq_model(argv[3]);
    string s;
    int i = 0;
    while(seq_model >> s){
        vector<int> seq;
        for(int i = 0; i < s.length(); i++){
            seq.push_back(s[i] - 'A');
        }
        data.push_back(seq);
    }

    /* Train */
    train(atoi(argv[1]));

    /* Save model */
    FILE *saved_path = open_or_die( argv[4], "w" );
    dumpHMM(saved_path, &model);
}

