#include <iostream>
#include <atomic>
#include "include/Printer.h"
#include <string>
#include <sstream>

using namespace std;
string Printer::txt = "";
string Printer::txts = "";
atomic_flag Printer::lock = ATOMIC_FLAG_INIT;


void Printer::printStringE(string x, int i, int n){
    while(lock.test_and_set()){}

    std::ostringstream ss;
    ss << i;
    ss.str();

    Printer::txt = Printer::txt + " #" + ss.str() + x  + "\n";

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

    Printer::txts = Printer::txts + " #" + ss.str() + x  + "\n";

    if(n == 0){
        cout << Printer::txts << endl;
        Printer::txts = "";
    }
    lock.clear();
}

void Printer::printString(string x, int i){
    while(lock.test_and_set()){}
    cout << x << i << endl << endl;
    lock.clear();
}

void Printer::printString(int i, string x){
    while(lock.test_and_set()){}
    cout << " #"<< i << " " << x << endl;
    lock.clear();
}
