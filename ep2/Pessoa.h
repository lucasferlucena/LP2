#ifndef PESSOA_H
#define PESSOA_H

#include <mutex>
#include "Banheiro.h"
#include <iostream>

#define CAPACIDADE 2
#define LIMITE 4

using namespace std;

class Pessoa{
private:
    int id;
public:
    Pessoa(int);
    ~Pessoa(){};
    int getId();

    static mutex e;
    static mutex homem;
    static mutex mulher;
    static mutex m;

    virtual void entrarBanheiro(){};
    virtual void sairBanheiro(){};
    virtual void passeia(){};
    virtual void run(){};
};
#endif // PESSOA_H
