#include <iostream>
#include <vector>
#include <thread>
#include "Banheiro.h"
#include "Pessoa.h"
#include "windows.h"
#include <chrono>

#define MAX 20

using namespace std;

int main() {
    srand (time(NULL));
    Pessoa *pessoa[MAX];

    for (int i = 0; i < MAX; i++){
        if(i%2)
            pessoa[i] = new Pessoa(i, 'M');
        else
            pessoa[i] = new Pessoa(i, 'F');
    }

   /* Pessoa::mulher.lock();
    Pessoa::homem.lock();*/

    vector<thread> tPessoas;

    for (auto &p : pessoa) tPessoas.push_back(thread(&Pessoa::run, p));

    for (auto &th : tPessoas) th.join();

    for (int i = 0; i < MAX; i++)
    	delete pessoa[i];

	return 0;
}

