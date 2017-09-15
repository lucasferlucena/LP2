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
#include "include/Printer.h"

using namespace std;

bool Carro::voltaAcabou = false;
const int Carro::CAPACIDADE = 5;

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
}

void Carro::daUmaVolta() {
    Carro::voltaAcabou = false;
	Sleep(1000);
	Carro::voltaAcabou = true;
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
        if(voltas != 20)
            Printer::printString("VOLTA #", voltas + 1);
        esperaEncher();
        if(Parque::numPessoas.load(std::memory_order_relaxed) <= 0)
            break;
		daUmaVolta();
        esperaEsvaziar();
		voltas++;
		Carro::voltaAcabou = false;
	}
}

bool Carro::getV(){
    return voltaAcabou;
}
