#include <iostream>
#include <string>
#include "Trabalhador.h"
#include "TrabalhadorAssalariado.h"


using namespace std;

TrabalhadorAssalariado::TrabalhadorAssalariado(void){}

TrabalhadorAssalariado::~TrabalhadorAssalariado(void){}

void TrabalhadorAssalariado::calcularPagamento(int h){
	
	if(h>=40)
		setSalarioM(5.8562*160);
	else
		setSalarioM(0);
	
}