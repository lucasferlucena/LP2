#include "include/Thread.h"


Thread::Thread(){
}

Thread::~Thread(){
}


void Thread::lock(int id){
    int n = 10, maior = 0;

    turn[id] = 1;
    for(int i = 0; i < n; i++){
        if(turn[i]>maior)
            maior = turn[i];
    }

    turn[id] = maior + 1;


    for(int j = 0; j < n; j++){
        if(j == id)
            continue;
        while(turn[j] != 0 && (turn[j] < turn[id] || (turn[j] < turn[id] && j < id))){
        }
    }
}


bool Thread::comp(int a1, int a2, int b1, int b2){
    if(a1 == b1){
        if(a2 > b2)
            return true;
        else
            return false;
    }
    else{
        if(a1>b1)
            return true;
        else
            return false;
    }
}

void Thread::unlock(int id){
    turn[id] = 0;
}
