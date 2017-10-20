#include <iostream>
#include "Pessoa.h"

using namespace std;

mutex Pessoa::e;
mutex Pessoa::mulher;
mutex Pessoa::homem;
mutex Pessoa::m;

Pessoa::Pessoa(int id){
    this->id = id;
}

int Pessoa::getId(){
    return id;
}


