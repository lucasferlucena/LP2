#include <iostream>
#include <atomic>
#include "include/Pinter.h"
#include <string>
#include <sstream>

using namespace std;
string Printer::txt;
string Printer::txts;
atomic_flag Printer::lock = ATOMIC_FLAG_INIT;

void Printer::printInt(int i, string x){
    while(lock.test_and_set()){}
    cout << i << " " << x << endl;
    lock.clear();
}

void Printer::printStringE(string x, int i, int n){
    while(lock.test_and_set()){}

    std::ostringstream ss;
    ss << i;
    ss.str();

    Printer::txt = Printer::txt + x + " " + ss.str() + "\n";

    if(n == 5){
        cout << Printer::txt << endl;
        Printer::txt = "";
    }
    lock.clear();
}

void Printer::printStringS(string x, int i, int n){
    while(lock.test_and_set()){}

    std::ostringstream ss;
    ss << i;
    ss.str();

    Printer::txts = Printer::txts + x + " " + ss.str() + "\n";

    if(n == 0){
        cout << Printer::txt << endl;
        Printer::txts = "";
    }
    lock.clear();
}

void Printer::printString(string x){
    while(lock.test_and_set()){}
    cout << x << endl;
    lock.clear();
}
void Printer::printInt(int i){
    while(lock.test_and_set()){}
    cout << i << endl;
    lock.clear();
}
