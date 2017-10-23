#ifndef PESSOA_H
#define PESSOA_H

#include <mutex>
#include "Banheiro.h"
#include <iostream>
#include <random>
#include <thread>
#include <vector>
#include <chrono>
#include <time.h>
#include "windows.h"

#define CAPACIDADE 2
#define LIMITE 4

using namespace std;

class Pessoa{
private:
    int id;
    char sexo;
public:
    Pessoa(int, char);
    ~Pessoa(){};

    int getId();
    char getSexo();

    static mutex e;
    static mutex homem;
    static mutex mulher;
    static mutex m;

    void entrarBanheiro();
    void usarBanheiro();
    void sairBanheiro();
    void passeia();
    void run();
};
#endif // PESSOA_H

