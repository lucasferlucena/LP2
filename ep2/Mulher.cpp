#include "Mulher.h"
#include "windows.h"

using namespace std;

Mulher::Mulher(int id):Pessoa(id){}

void Mulher::entrarBanheiro(){
     Pessoa::e.lock();

     if(Banheiro::mulherSeguido == LIMITE || Banheiro::homemBanheiro != 0 || Banheiro::mulherBanheiro == CAPACIDADE){
        Banheiro::mulherDormindo++;

        Pessoa::e.unlock();
        Pessoa::mulher.lock();
     }

     Banheiro::homemSeguido = 0;
     Banheiro::mulherBanheiro++;
     Banheiro::mulherSeguido++;

     if(Banheiro::mulherDormindo > 0 ){
        Banheiro::mulherDormindo--;
        Pessoa::mulher.unlock();
     }
     else
        Pessoa::e.unlock();

     Pessoa::m.lock();
     cout << "Mulher " << getId() << endl;
     Pessoa::m.unlock();

     Pessoa::e.lock();
     Banheiro::mulherBanheiro--;

     if(Banheiro::mulherBanheiro == 0 && Banheiro::homemDormindo > 0){
        Banheiro::homemDormindo--;
        Pessoa::homem.unlock();
     }
     else
        Pessoa::e.unlock();

}

void Mulher::passeia(){
    Sleep(1000);
}

void Mulher::run(){
    while(1){
        entrarBanheiro();
        passeia();
    }
}

