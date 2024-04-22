// Online C++ compiler to run C++ program online
#include <iostream>
#include <cmath>
void bt_update(float* p, float* score, int teams_ct)
{
    /*
    (score[i][j] * p[j])/(p[i] + p[j])
    ----------------------------------
    (score[j][i] * p[j])/(p[i] + p[j])
    */

    float pnum = 0, pden = 0, mul = 1;

    for (int i = 0; i < teams_ct; ++i) {
        pnum = 0;
        pden = 0;

        for (int j = 0; j < teams_ct; ++j) {
            if (i != j) {
                pnum += (score[i * teams_ct + j] * p[j])/(p[i] + p[j]);
                pden += (score[j * teams_ct + i])/(p[i] + p[j]);
            }
        }

        float pv = pnum / pden;
        p[i] = pv;
        mul *= pv;
    }

    mul = pow(mul, float(1)/float(teams_ct));

    for (int i = 0; i < teams_ct; ++i)
        p[i] /= mul;
}

int main() {
    // Example taken from wikipedia
    // https://en.wikipedia.org/wiki/Bradley%E2%80%93Terry_model#Worked_Example_of_Iterated_Procedure
    // Suppose there are 4 teams who have played a total of 21 games among themselves.
    // Each teams wins are given in the rows of the table below and the opponents are given as the columns.
    // For example:
    //  - Team A has beat Team B two times
    //  - Team A lost to team B three times;
    //  - Team A has not played team C at all
    //  - Team A won once and lost four times against team D. 
    // Initialize the probabilities to 1 for all the teams
    //p = [1]*len(scores)
    int teams_ct = 4;
    
    float score[teams_ct * teams_ct] = {
        0, 2, 0, 1,
        3, 0, 5, 0,
        0, 3, 0, 1,
        4, 0, 3, 0
    };
    
    float p[teams_ct];

    for (int i = 0; i < teams_ct; ++i)
        p[i] = 1;

    for (int i = 0; i < 10; ++i) {
        bt_update(p, score, teams_ct);
        
        for (int j = 0; j < teams_ct; ++j) {
            printf("%f ", p[j]);
        }
        puts("");
    }
    
    return 0;
}