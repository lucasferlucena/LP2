#ifndef PESSOA_H
#define PESSOA_H

#include <mutex>
#include "Banheiro.h"
#include <iostream>
#include "windows.h"
#include <random>
#include <thread>

#define CAPACIDADE 2
#define LIMITE 4
#define TEMPO_MINIMO_WC 1
#define TEMPO_MAXIMO_WC 20
#define TEMPO_MINIMO_MOSCANDO 5
#define TEMPO_MAXIMO_MOSCANDO 20

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

