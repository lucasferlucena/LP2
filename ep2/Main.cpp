#include <iostream>
#include <vector>
#include <thread>
#include "Banheiro.h"
#include "Pessoa.h"
#include "Mulher.h"
#include "Homem.h"

using namespace std;

int main() {
	Homem *homem[10];
	Mulher *mulher[10];

    for (int i = 0; i < 10; i++)
    	homem[i] = new Homem(i);
    for (int i = 0; i < 10; i++)
    	mulher[i] = new Mulher(i);

    vector<thread> tPessoas;

    for (auto &p : homem) tPessoas.push_back(thread(&Homem::run, p));
    for (auto &p : mulher) tPessoas.push_back(thread(&Mulher::run, p));

    for (auto &th : tPessoas) th.join();

    for (int i = 0; i < 10; i++)
    	delete homem[i];
    for (int i = 0; i < 10; i++)
    	delete mulher[i];

	return 0;
}

