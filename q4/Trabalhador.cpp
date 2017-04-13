#include <iostream>
#include <string>
#include "Trabalhador.h"

using namespace std;

Trabalhador::Trabalhador(void){}

Trabalhador::~Trabalhador(void){}

std::string Trabalhador::getNome(void){
	return nome;
}

float Trabalhador::getSalarioM(void){
	return salarioM;
}

void Trabalhador::setNome(std::string n){
	nome = n;
}

void Trabalhador::setSalarioM(float s){
	salarioM = s;
}

