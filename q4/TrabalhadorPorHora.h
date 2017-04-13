#ifndef TRABALHADORPORHORA_H
#define TRABALHADORPORHORA_H
#include "Trabalhador.h"
#include <iostream>

class TrabalhadorPorHora:public Trabalhador{
public:
	TrabalhadorPorHora();
	~TrabalhadorPorHora();

	void calcularPagamento(int h);
};

#endif