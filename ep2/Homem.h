#ifndef HOMEM_H
#define HOMEM_H

#include "Pessoa.h"

using namespace std;

class Homem: public Pessoa{
private:
public:
    Homem(int);

    static mutex homem;

    void entrarBanheiro();
    //void sairBanheiro();
    void passeia();
    void run();

};
#endif // HOMEM_H
