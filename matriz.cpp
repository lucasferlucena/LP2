#include <iostream>
#include <ostream>
#include <thread>

using namespace std;

#define NUM 2

int a[NUM][NUM] = {{1, 2}, {3, 4}};
int b[NUM][NUM] = {{-1,3}, {4,2}};

int res[NUM][NUM] = {{0,0},{0,0}};

void operacao_1(int n){

    if(n == 0){
        for(int k = 0; k < NUM; k++){
                res[0][0] += a[0][k]*b[k][0];
        }
    }
    if(n == 1){
        for(int k = 0; k < NUM; k++){
            res[0][1] += a[0][k]*b[k][1];
        }
    }
    if(n == 2){
        for(int k = 0; k < NUM; k++){
            res[1][0] += a[1][k]*b[k][0];
        }
    }
    if(n == 3){
        for(int k = 0; k < NUM; k++){
            res[1][1] += a[1][k]*b[k][1];
        }
    }

}



int main(){
    int i, j, n = 0;



    thread threads[4];

    for(i = 0; i < NUM; i++){
        for(j = 0; j < NUM; j++){
            //operacao_1(n);
            threads[n] = thread(operacao_1, n);
            threads[n].join();
            n++;
        }
    }
n=0;
    for(i = 0; i < NUM; i++){
        for(j = 0; j < NUM; j++){
            cout << res[i][j] << "\t";
        }
        cout << endl;
    }

    return 0;
}



