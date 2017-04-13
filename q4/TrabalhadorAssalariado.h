#ifndef TRABALHADORASSALARIADO_H
#define TRABALHADORASSALARIADO_H
#include "Trabalhador.h"
#include <iostream>

class TrabalhadorAssalariado:public Trabalhador{
public:
	TrabalhadorAssalariado();
	~TrabalhadorAssalariado();

	void calcularPagamento(int h);
};

#endif