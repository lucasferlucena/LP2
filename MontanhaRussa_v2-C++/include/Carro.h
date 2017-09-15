/*
 * Carro.h
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#ifndef CARRO_H_
#define CARRO_H_
#include "atomic"

class Parque;

class Carro {
public:
	static const int CAPACIDADE;
	static std::atomic<int> numPassageiros;
    static bool voltaAcabou;
    static bool vazio;
	Carro();
	virtual ~Carro();
	void esperaEncher();
	void daUmaVolta();
	bool esperaEsvaziar();
	int getNVoltas();
	void run();
	bool getV();

	void operator()()
	{
		run();
	}

private:
	int voltas;

};

#endif /* CARRO_H_ */
