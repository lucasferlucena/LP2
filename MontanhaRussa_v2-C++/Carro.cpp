/*
 * Carro.cpp
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */
#include <iostream>
#include <ostream>
#include "include/Carro.h"
#include "include/Parque.h"
#include "windows.h"
#include "atomic"
#include "include/Pinter.h"

using namespace std;

bool Carro::voltaAcabou = false;
const int Carro::CAPACIDADE = 5;
//std::atomic<int> Carro::numPassageiros;

Carro::Carro() {
	this->voltas = 0;
}

Carro::~Carro() {
}

void Carro::esperaEncher() {
	while (Carro::numPassageiros < Carro::CAPACIDADE) { Sleep(500);}
	Carro::voltaAcabou = false;
}

void Carro::daUmaVolta() {
	Sleep(10000);
	Carro::voltaAcabou = true;
	//cout<<"VoltaAcabou"<<Carro::voltaAcabou;
}

void Carro::esperaEsvaziar() {
	while (Carro::numPassageiros > 0) {Sleep(5000); }

}

int Carro::getNVoltas() {
	return voltas;
}

void Carro::run() {
	while (Parque::numPessoas > 0) {
        esperaEncher();

		daUmaVolta();

		esperaEsvaziar();

		voltas++;
	}
}

bool Carro::getV(){
    return voltaAcabou;
}
