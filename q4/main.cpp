#include <iostream>
#include "Trabalhador.h"
#include "TrabalhadorAssalariado.h"
#include "TrabalhadorPorHora.h"

using namespace std;

int main()
{
	TrabalhadorAssalariado a;
	TrabalhadorPorHora h;

//	TrabalhadorAssalariado *a = new TrabalhadorAssalariado;
//	a->calcularPagamento(50);

//	Trabalhador *t;
//	t = new TrabalhadorAssalariado;

//	t.calcularPagamento(50);

	a.calcularPagamento(50);
	h.calcularPagamento(50);

	cout << a.getSalarioM() << endl;
	cout << h.getSalarioM() << endl;

	return 0;
}