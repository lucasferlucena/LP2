#include "Homem.h"
#include "windows.h"

using namespace std;

Homem::Homem(int id):Pessoa(id){}

void Homem::entrarBanheiro(){
    //Entra na fila
    Pessoa::e.lock();

    //Dorme
    if(Banheiro::homemSeguido == LIMITE || Banheiro::mulherBanheiro != 0 || Banheiro::homemBanheiro == CAPACIDADE){
        Banheiro::homemDormindo++;

        Pessoa::e.unlock();
        Pessoa::homem.lock();
    }
    //atualiza os contadores
    Pessoa::m.lock();
    Banheiro::homemBanheiro++;
    Banheiro::mulherSeguido = 0;
    Banheiro::homemSeguido++;
    Pessoa::m.unlock();
    //SIGNAL
    if(Banheiro::homemDormindo > 0 && Banheiro::homemBanheiro < CAPACIDADE && Banheiro::homemSeguido != LIMITE){
        Banheiro::homemDormindo--;
        Pessoa::homem.unlock();
    }
    else
        Pessoa::e.unlock();
    //SC
    Pessoa::m.lock();
    cout << "Homem " << getId() << endl;
    Pessoa::m.unlock();
    //entra na "fila" pra sair
    Pessoa::e.lock();
    //decrementa o nº de pessoas no banheiro
    Banheiro::homemBanheiro--;
    //SIGNAL
/*
    if(Banheiro::homemSeguido >= LIMITE && Banheiro::homemBanheiro != 0)
        Pessoa::e.unlock();
    else{
        if(Banheiro::mulherDormindo > 0){
            Banheiro::mulherDormindo--;
            Pessoa::mulher.unlock();
        }
        else{
            if(Banheiro::homemDormindo > 0){
                Banheiro::homemDormindo--;
                Pessoa::homem.unlock();
            }
            else
                Pessoa::e.unlock();
        }
    }
*/
    if(Banheiro::homemBanheiro == 0){
        if(Banheiro::mulherDormindo > 0){
            Banheiro::mulherDormindo--;
            Pessoa::mulher.unlock();
        }
        else{
            Banheiro::homemBanheiro = 0;
            if(Banheiro::homemDormindo > 0){
                Banheiro::homemDormindo--;
                Pessoa::homem.unlock();
            }
            else
                Pessoa::e.unlock();
        }
    }
    else{
        if(Banheiro::homemDormindo > 0 && Banheiro::homemSeguido < LIMITE){
            Banheiro::homemDormindo--;
            Pessoa::homem.unlock();
        }
        else
            Pessoa::e.unlock();
    }
}

void Homem::passeia(){
        Sleep(1);
}

void Homem::run(){
    while(1){
        entrarBanheiro();
        passeia();
    }
}


