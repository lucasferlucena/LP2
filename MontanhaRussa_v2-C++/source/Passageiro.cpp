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

#define MAX_NUM_VOLTAS 50

using namespace std;

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
	cout << "saiu " << id << endl;
    data.fetch_add(1, std::memory_order_seq_cst);
    Carro::numPassageiros = data;

	carro->run();
}

void Passageiro::esperaVoltaAcabar() {
	while (!carro->getV()) {Sleep(10);}
}

void Passageiro::saiDoCarro() {
    cout << "data" << endl;
	t->unlock(id);
	data.fetch_add(-1, std::memory_order_seq_cst);
	Carro::numPassageiros = data;
}

void Passageiro::passeiaPeloParque() {
    Sleep(15);
}

bool Passageiro::parqueFechado() {
	if (carro->getNVoltas() < MAX_NUM_VOLTAS)
		return false;

	return true;
}

void Passageiro::run() {
	while (!parqueFechado()) {
		entraNoCarro(); // protocolo de entrada

		esperaVoltaAcabar();

		saiDoCarro(); // protocolo de saida

		passeiaPeloParque(); // secao nao critica
	}

	Parque::numPessoas--;  // decrementa o numero de pessoas no parque
}

int Passageiro::getId(){
    return id;
}
