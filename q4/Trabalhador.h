#ifndef TRABALHADOR_H
#define TRABALHADOR_H
#include <iostream>

class Trabalhador{
private:
	std::string nome;
	float salarioM;
public:

	Trabalhador();
	~Trabalhador();

	virtual void calcularPagamento(int h)=0;
	
	void setNome(std::string);
	void setSalarioM(float);

	std::string getNome();
	float getSalarioM();

};



#endif