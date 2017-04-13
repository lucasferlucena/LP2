#include <iostream>
#include <string>
//#include "Trabalhador.h"
#include "TrabalhadorPorHora.h"

using namespace std;

TrabalhadorPorHora::TrabalhadorPorHora(){	
}

TrabalhadorPorHora::~TrabalhadorPorHora(){}

void TrabalhadorPorHora::calcularPagamento(int h){
		int s;

		if(h<=40)
			setSalarioM(4*5.8562*h);
		else 
			{
				s = 4*40*5.8562 + 4*(h-40)*1.5*8.8562;
				setSalarioM(s);
			}
}