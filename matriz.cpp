#include <iostream>
#include <ostream>
#include <thread>
#define NUM 8 //tamanho da matriz
#define N NUM*NUM

using namespace std;


int a[NUM][NUM] = {{5, -1, 5, 2, 3, -5, -6, -8}, {1, 47, 5, 0, 3, -8, 5, 6}, {0, 1, 4, -6, 2, 4, 3, -23}, {-8, 4, 5, 6, 2, 8, 3, 4}, {-7, 9, 3, 7, 8, 6, 12, 7}, {12, 3, 4, 6, 8, 9, 1, 2}, {3, 8, 6, 1, 4, 7, 5, 3}, {2, 5, 5, -5, -5, -6, -7, -8}};
int b[NUM][NUM] = {{6, 3, 41, 2, 87, -5, -6, -8}, {6, 8, 1, 4, 3, -8, 5, 6}, {6, 8, 2, 3, 4, 4, 3, -23}, {7, 5, 9, 2, -6, 8, 3, 4}, {-8, -5, -6, -7, -2, 6, 12, 7}, {12, 3, 4, 6, 8, 9, 1, 2}, {3, 8, 6, 1, 4, 7, 5, 3}, {2, 5, 5, -5, -5, -6, -7, -8}};
int res[NUM][NUM] = {0};

void operacao_1(int i, int j){
        for(int k = 0; k < NUM; k++){
                res[i][j] += a[i][k]*b[k][j];
        }
}

int main(){
    int i, j, n = 0;
    bool t = false;

    if(t)//com thread
    {
        thread threads[N];

        for(i = 0; i < NUM; i++){
            for(j = 0; j < NUM; j++){
                threads[n] = thread(operacao_1, i, j);
                n++;
            }
        }
        for(n = 0; n < N; n++){
            threads[n].detach();
        }
        for(i = 0; i < NUM; i++){
            for(j = 0; j < NUM; j++){
                cout << res[i][j] << "\t";
            }
            cout << endl;
        }
        return 0;

    }
    if(!t)//sem thread
    {
        for(i = 0; i < NUM; i++){
            for(j = 0; j < NUM; j++){
                operacao_1(i, j);
            }
        }

        for(i = 0; i < NUM; i++){
            for(j = 0; j < NUM; j++){
                cout << res[i][j] << "\t";
            }
            cout << endl;
        }
        return 1;

    }
}






