/*
 * Passageiro.h
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#ifndef PASSAGEIRO_H_
#define PASSAGEIRO_H_
#include <atomic>

class Carro;
class Parque;
class Thread;


class Passageiro {
public:
    static std::atomic<int> data;

	Passageiro(int id, Carro *c, Parque *t);
	virtual ~Passageiro();
	void entraNoCarro();
	void esperaVoltaAcabar();
	void saiDoCarro();
	void passeiaPeloParque();
	bool parqueFechado();
    int getId();
    int getTurn();

	void run();
private:
    int turn;
	int id;
	Carro *carro;
	Parque *parque;
};

#endif /* PASSAGEIRO_H_ */
