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
#include "include/Thread.h"
#include <atomic>

#define MAX_NUM_VOLTAS 50

using namespace std;

const int N = -1;
const int M = 5;
std::atomic<int> Passageiro::data = ATOMIC_VAR_INIT(N);

Passageiro::Passageiro(int id, Carro *c, Thread *t) {
	this->id = id;
	this->carro = c;
	this->t = t;
	//cout << id << endl;
}

Passageiro::~Passageiro() {
}

void Passageiro::entraNoCarro() {
   // clog << "entrou " << id << endl;
    t->lock(id);
    Sleep(1);
	if(std::atomic_fetch_add(&Passageiro::data, 1)  < Carro::CAPACIDADE - 2){
            t->unlock(id);
    }
    cout << id << endl;

    Carro::numPassageiros = data;
    cout << "Entrou";
	carro->run();
}

void Passageiro::esperaVoltaAcabar() {
	while (!carro->getV()) {Sleep(1000);}
}

void Passageiro::saiDoCarro() {
    Sleep(1000);
	std::atomic_fetch_sub(&Passageiro::data, 1);
	Carro::numPassageiros = data;
	cout<<"Terminou";
}

void Passageiro::passeiaPeloParque() {
    Sleep(10000);
}

bool Passageiro::parqueFechado() {
	if (carro->getNVoltas() < MAX_NUM_VOLTAS)
		return false;

	return true;
}

void Passageiro::run() {
	while (!parqueFechado()) {
		entraNoCarro(); // protocolo de entrada

		//esperaVoltaAcabar();

		saiDoCarro(); // protocolo de saida

		passeiaPeloParque(); // secao nao critica
	}

	Parque::numPessoas--;  // decrementa o numero de pessoas no parque
}

int Passageiro::getId(){
    return id;
}
