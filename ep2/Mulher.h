#ifndef MULHER_H
#define MULHER_H

#include "Pessoa.h"
#include <mutex>

using namespace std;

class Mulher: public Pessoa{
private:
public:
    Mulher(int);
    ~Mulher(){};
    static mutex mulherDormindo;

    void entrarBanheiro();
    //void sairBanheiro();
    void passeia();
    void run();

};
#endif // MULHER_H
