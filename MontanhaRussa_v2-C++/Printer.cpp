#include <iostream>
#include <atomic>
#include "include/Pinter.h"

using namespace std;

atomic_flag Printer::lock = ATOMIC_FLAG_INIT;

void Printer::printInt(int i, string x){
    while(lock.test_and_set()){}
    cout << i << " " << x << endl;
    lock.clear();
}

void Printer::printString(string x, int i){
    while(lock.test_and_set()){}
    cout << x << " " << i << endl;
    lock.clear();
}
