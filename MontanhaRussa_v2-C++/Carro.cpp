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
	while (Carro::numPassageiros != Carro::CAPACIDADE) {
            if(Parque::numPessoas.load(std::memory_order_relaxed) == 0){
                break;
            }
            Sleep(250);
    }
    Carro::voltaAcabou = false;
}

void Carro::daUmaVolta() {
	Sleep(5000);
	Carro::voltaAcabou = true;
	//cout<<"VoltaAcabou"<<Carro::voltaAcabou;
}

bool Carro::esperaEsvaziar() {
	while (Carro::numPassageiros > 0){
        Sleep(250);
    }
}

int Carro::getNVoltas() {
	return voltas;
}

void Carro::run() {
	while (Parque::numPessoas.load(std::memory_order_relaxed) > 0) {
        //Printer::printString("Entrou");
        esperaEncher();
        if(Parque::numPessoas.load(std::memory_order_relaxed) <= 0){break;}
        //Printer::printString("Encheu");
		daUmaVolta();

        //Printer::printString("Volta Acabou");

        esperaEsvaziar();

       // Printer::printString("Esvaziou");
		voltas++;
		Carro::voltaAcabou = false;
	}
}

bool Carro::getV(){
    return voltaAcabou;
}
