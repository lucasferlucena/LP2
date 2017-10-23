#include "Pessoa.h"

int maiorB = 3000;  // para thread random
int menorB = 1000;
int aleatorioB = rand()%maiorB + menorB;

int maiorP = 8000;  // para thread random
int menorP = 3000;
int aleatorioP = rand()%maiorP + menorB;

mutex Pessoa::e;
mutex Pessoa::homem;
mutex Pessoa::mulher;
mutex Pessoa::m;

auto now = high_resolution_clock::now();
auto nanos = (int)duration_cast<nanoseconds>(now.time_since_epoch()).count();
srand(nanos);//randomiza a seed
int a = (rand()%8000)+1000;

using namespace std;
using namespace std::chrono;

Pessoa::Pessoa(int id, char sexo){
    this->id = id;
    this->sexo = sexo;
}

char Pessoa::getSexo(){
    return sexo;
}

int Pessoa::getId(){
    return id;
}

void Pessoa::entrarBanheiro(){
    //Entra na fila
    if(getSexo() == 'M'){
        Pessoa::m.lock();
        cout << "HOMEM[" << getId() << "] CHEGOU" << endl;
        Pessoa::m.unlock();

        Pessoa::e.lock();
        //Dorme
        if((Banheiro::mulherBanheiro > 0) || (Banheiro::homemBanheiro == CAPACIDADE || (Banheiro::homemSeguido >= LIMITE)) && (Banheiro::mulherDormindo > 0)){
            Banheiro::homemDormindo++;

            Pessoa::m.lock();
            cout << "HOMEM[" << getId() << "] ENTROU NA FILA" << endl;
            Pessoa::m.unlock();

            Pessoa::e.unlock();
            Pessoa::homem.lock();
        }
        //atualiza os contadores
        Banheiro::homemBanheiro++;
        Banheiro::mulherSeguido = 0;
        Banheiro::homemSeguido++;

        Pessoa::m.lock();
        cout << "HOMEM SEGUIDO "<< Banheiro::homemSeguido << endl;
        Pessoa::m.unlock();
        //SIGNAL
        if(Banheiro::homemBanheiro < CAPACIDADE && Banheiro::homemSeguido < LIMITE && Banheiro::homemDormindo > 0){
                Banheiro::homemDormindo--;
                Pessoa::homem.unlock();
        }
        else
            Pessoa::e.unlock();
    }

    if(getSexo() == 'F'){
        Pessoa::m.lock();
        cout << "MULHER[" << getId() << "] CHEGOU" << endl;
        Pessoa::m.unlock();

        Pessoa::e.lock();
        //dorme
        if((Banheiro::homemBanheiro > 0) || (Banheiro::mulherBanheiro == CAPACIDADE) || (Banheiro::mulherSeguido >= LIMITE) && (Banheiro::homemDormindo > 0)){
            Banheiro::mulherDormindo++;

            Pessoa::m.lock();
            cout << "MULHER[" << getId() << "] ENTROU NA FILA" << endl;
            Pessoa::m.unlock();

            Pessoa::e.unlock();
            Pessoa::mulher.lock();
        }
        //atualiza os contadores
        Banheiro::mulherBanheiro++;
        Banheiro::homemSeguido = 0;
        Banheiro::mulherSeguido++;

        Pessoa::m.lock();
        cout << "MULHER SEGUIDA "<< Banheiro::mulherSeguido << endl;
        Pessoa::m.unlock();

        //signal
        if(Banheiro::mulherBanheiro < CAPACIDADE && Banheiro::mulherSeguido < LIMITE && Banheiro::mulherDormindo > 0){
                Banheiro::mulherDormindo--;
                Pessoa::mulher.unlock();
            }
        else
            Pessoa::e.unlock();
    }
}

void Pessoa::usarBanheiro(){
    if(getSexo() == 'M'){
        Pessoa::m.lock();
        cout << "HOMEM[" << getId() << "] ENTROU NO BANHEIRO"<< a << endl;
        Pessoa::m.unlock();

        this_thread::sleep_for(std::chrono::milliseconds(a));
    }

    if(getSexo() ==  'F'){
        Pessoa::m.lock();
        cout << "MULHER[" << getId() << "] ENTROU NO BANHEIRO"<< a << endl;
        Pessoa::m.unlock();

        this_thread::sleep_for(std::chrono::milliseconds(a));
    }
}

void Pessoa::sairBanheiro(){
    if(getSexo() == 'M'){
        Pessoa::e.lock();

        Banheiro::homemBanheiro--;

        Pessoa::m.lock();
        cout << "HOMEM[" << getId() << "] SAIU DO BANHEIRO" << endl;
        Pessoa::m.unlock();

        //SIGNAL
        if(Banheiro::mulherDormindo > 0 && Banheiro::homemBanheiro == 0){
                Banheiro::mulherDormindo--;
                Pessoa::mulher.unlock();
        }
        else {
            if(Banheiro::homemDormindo > 0 && Banheiro::homemSeguido < LIMITE){
                Banheiro::homemDormindo--;
                Pessoa::homem.unlock();
            }
            else
                Pessoa::e.unlock();
        }
    }

    if(getSexo() == 'F'){
        Pessoa::e.lock();

        Pessoa::m.lock();
        cout << "MULHER[" << getId() << "] SAIU DO BANHEIRO" << endl;
        Pessoa::m.unlock();

        Banheiro::mulherBanheiro--;

        if(Banheiro::mulherBanheiro == 0 && Banheiro::homemDormindo > 0){
                Banheiro::homemDormindo--;
                Pessoa::homem.unlock();
            }
        else {
            if(Banheiro::mulherDormindo > 0 && Banheiro::mulherSeguido < LIMITE){
                Banheiro::mulherDormindo--;
                Pessoa::mulher.unlock();
            }
            else
                Pessoa::e.unlock();
        }
    }
}

void Pessoa::passeia(){
    this_thread::sleep_for(std::chrono::milliseconds(a + 2000));
}

void Pessoa::run(){
    while(1){
        entrarBanheiro();
        usarBanheiro();
        sairBanheiro();
        passeia();
    }
}



