#include "Homem.h"
#include "windows.h"

using namespace std;

Homem::Homem(int id):Pessoa(id){}

void Homem::entrarBanheiro(){
     Pessoa::e.lock();

     if(Banheiro::homemSeguido == LIMITE || Banheiro::mulherBanheiro != 0 || Banheiro::homemBanheiro == CAPACIDADE){
        Banheiro::homemDormindo++;

        Pessoa::e.unlock();
        Pessoa::homem.lock();
     }

     Banheiro::mulherSeguido = 0;
     Banheiro::homemBanheiro++;
     Banheiro::homemSeguido++;

     if(Banheiro::homemDormindo > 0){
        Banheiro::homemDormindo--;
        Pessoa::homem.unlock();
     }
     else
        Pessoa::e.unlock();

     Pessoa::m.lock();

     cout << "Homem " << getId() << endl;

     Pessoa::m.unlock();

     Pessoa::e.lock();

     Banheiro::homemBanheiro--;

     if(Banheiro::homemBanheiro == 0 && Banheiro::mulherDormindo > 0){
        Banheiro::mulherDormindo--;
        Pessoa::mulher.unlock();
     }
     else
        Pessoa::e.unlock();
}

void Homem::passeia(){
    Sleep(1000);
}

void Homem::run(){
    while(1){
        entrarBanheiro();
        passeia();
    }
}


