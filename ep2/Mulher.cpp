#include "Mulher.h"
#include "windows.h"

using namespace std;

Mulher::Mulher(int id):Pessoa(id){}

void Mulher::entrarBanheiro(){
    //entra na fila
    Pessoa::e.lock();
    //dorme
    if(Banheiro::mulherSeguido == LIMITE || Banheiro::homemBanheiro != 0 || Banheiro::mulherBanheiro == CAPACIDADE){
        Banheiro::mulherDormindo++;

        Pessoa::e.unlock();
        Pessoa::mulher.lock();
    }
    //atualiza os contadores
    Pessoa::m.lock();
    Banheiro::mulherBanheiro++;
    Banheiro::homemSeguido = 0;
    Banheiro::mulherSeguido++;
    Pessoa::m.unlock();
    //signal
    if(Banheiro::mulherDormindo > 0 ){
        Banheiro::mulherDormindo--;
        Pessoa::mulher.unlock();
    }
    else
        Pessoa::e.unlock();
    //sc
    Pessoa::m.lock();
    cout << "Mulher " << getId() << endl;
    Pessoa::m.unlock();
    //entra na fila pra sair
    Pessoa::e.lock();
    //decrementa o nº de pessoas no banheiro
    Banheiro::mulherBanheiro--;
    //signal

/*    if(Banheiro::mulherBanheiro == 0 && Banheiro::homemDormindo > 0){
        Banheiro::homemDormindo--;
        Pessoa::homem.unlock();
    }
    else
        Pessoa::e.unlock();
*/

    if(Banheiro::mulherBanheiro == 0){
        if(Banheiro::homemDormindo > 0){
            Banheiro::homemDormindo--;
            Pessoa::homem.unlock();
        }
        else{
            Banheiro::mulherBanheiro = 0;
            if(Banheiro::mulherDormindo > 0){
                Banheiro::mulherDormindo--;
                Pessoa::mulher.unlock();
            }
            else
                Pessoa::e.unlock();
        }
    }
    else{
        if(Banheiro::mulherDormindo > 0 && Banheiro::mulherSeguido < LIMITE){
            Banheiro::mulherDormindo--;
            Pessoa::mulher.unlock();
        }
        else
            Pessoa::e.unlock();
    }
}

void Mulher::passeia(){
    Sleep(1);
}

void Mulher::run(){
    while(1){
        entrarBanheiro();
        passeia();
    }
}

