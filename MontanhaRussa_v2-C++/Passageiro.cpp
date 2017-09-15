/*
 * Passageiro.cpp
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */
#include <iostream>
#include <ostream>
#include "include/Passageiro.h"
#include "include/Carro.h"
#include "include/Parque.h"
#include "windows.h"
#include <atomic>
#include "include/Pinter.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

#define MAX_NUM_VOLTAS 50

using namespace std;

const int N = 0;
std::atomic<int> Carro::numPassageiros = ATOMIC_VAR_INIT(N);
std::atomic<int> Passageiro::data = ATOMIC_VAR_INIT(N);



Passageiro::Passageiro(int id, Carro *c, Parque *t) {
	this->id = id;
	this->carro = c;
	this->parque = t;
}

Passageiro::~Passageiro() {
}

void Passageiro::entraNoCarro() {
    int maior = 0;
    turn = 1;

    for(auto &p : parque->getPassageiros()){
        if(p->getTurn() > maior)
            maior = p->getTurn();
    }

    turn = maior + 1;

    for(auto &p : parque->getPassageiros()){
        if(this->id == p->getId())
            continue;
        while(p->getTurn() != 0 && (p->getTurn() < this->turn || (p->getTurn() == this->turn  && p->getId() < this->id)) || (Carro::numPassageiros == Carro::CAPACIDADE) || (carro->voltaAcabou)){
        }
    }

    if(!parqueFechado())
        std::atomic_fetch_add(&Carro::numPassageiros, 1);
    Printer::printStringE("Entrou", id, Carro::numPassageiros);

    this->turn = 0;
}

void Passageiro::esperaVoltaAcabar() {

	while (!Carro::voltaAcabou) {Sleep(500);}

}

void Passageiro::saiDoCarro() {
	std::atomic_fetch_sub(&Carro::numPassageiros, 1);
	Printer::printStringE("Saiu", id, Carro::numPassageiros);
}

void Passageiro::passeiaPeloParque() {
    while(true){
        srand((unsigned)time(0));
        if((rand()%10) != 0)
            break;
    }
    std::atomic_fetch_add(&Passageiro::data, 1);
   // Printer::printInt(Passageiro::data);
    Sleep((rand()%10)*Passageiro::data*50);
    std::atomic_fetch_sub(&Passageiro::data, 1);
}

bool Passageiro::parqueFechado() {
	if (carro->getNVoltas() < MAX_NUM_VOLTAS)
		return false;

    return true;
}

void Passageiro::run() {
	while (!parqueFechado()) {
		entraNoCarro(); // protocolo de entrada
        //Printer::printString("entrou", id, Carro::numPassageiros);
        if(parqueFechado()){break;}
		esperaVoltaAcabar();
        //Printer::printString("esperou", id);
		saiDoCarro(); // protocolo de saida
        //Printer::printString("saiu", id);
        //Printer::printString("passeando", id);
        passeiaPeloParque(); // secao nao critica

	}

	std::atomic_fetch_sub(&Parque::numPessoas, 1);  // decrementa o numero de pessoas no parque
}

int Passageiro::getId(){
    return id;
}

int Passageiro::getTurn(){
    return turn;
}
