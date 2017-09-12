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

using namespace std;

const int Carro::CAPACIDADE = 5;
int Carro::numPassageiros = 0;

Carro::Carro() {
	this->voltas = 0;
}

Carro::~Carro() {
}

void Carro::esperaEncher() {
	while (Carro::numPassageiros != 4) { Sleep(500);}
}

void Carro::daUmaVolta() {
    voltaAcabou = false;
	Sleep(3000);
	voltaAcabou = true;
	cout<<"Volta";
}

void Carro::esperaEsvaziar() {
	while (Carro::numPassageiros > 0) { Sleep(2); }

}

int Carro::getNVoltas() {
	return voltas;
}

void Carro::run() {
	//while (Parque::numPessoas > 0) {

		esperaEncher();

		daUmaVolta();

		//esperaEsvaziar();

		voltas++;
	//}
}

bool Carro::getV(){
    return voltaAcabou;
}
