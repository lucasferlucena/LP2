#include "stdio.h"
#include "stdlib.h"

// constantes para os indices das tres variaveis
#define P                 0
#define Q                 1
#define R                 2

#define VARS              3

#define IMP(b1, b2)       (b1 && !b2 ? FALSE : TRUE)

#define FALSE 0
#define TRUE 1

int L = 0, T = 0;

char nome[VARS];
int I[VARS];

void mostra_tabela()
{
  int fim = FALSE;

  inicializa_formula();

  printf("Formula:\n");
  printf("H = (P \\/ (Q /\\ R)) -> ((P \\/ Q) /\\ (P \\/ R))\n\n");

  for (int c = 0; c < VARS; c++) {
    printf(" %c |", nome[c]);
  }
  printf(" H\n");

  for (int c = 0; c < 4 * VARS + 3; c++)
    printf("-");
  printf("\n");

  while (!fim) {
  // imprime valores atuais das variaveis
  for (int c = 0; c < VARS; c++) {
    if (I[c])
      printf(" T |");
    else
      printf(" F |");
  }

  // calcula e imprime o valor da formula
  if (valor_formula()){
    printf(" T\n");
    T++;
  }
  else{
    printf(" F\n");
    L++;
  }

  // verifica se acabou a tabela ou passa para
  // a proxima linha
  if (ultima_interpretacao())
    fim = TRUE;
  else
    proxima_interpretacao();
}
}

void inicializa_formula()
{
  nome[P] = 'P';
  nome[Q] = 'Q';
  nome[R] = 'R';

  for (int c = 0; c < VARS; c++)
    I[c] = FALSE;
}

int valor_formula()
{
  return IMP((I[P] || (I[Q] && I[R])), ((I[P] || I[Q]) && (I[P] || I[R])));
}

int ultima_interpretacao()
{
  int res = 1;

  for (int c = 0; c < VARS; c++) {
    res = res && I[c];
  }

  return res;
}

void proxima_interpretacao()
{
  int c = VARS - 1;

  while (c >= 0 && I[c] != 0) {
    I[c--] = 0;
  }

  if (c >= 0)
    I[c] = 1;
}

int main(){
    mostra_tabela();
    if(L == 0)
        printf("Eh tautologia\n");
    else
        printf("Nao eh tautologia\n");

    if(T >= 1)
        printf("Eh satisfativel\n");
    else
        printf("Nao eh satisfativel\n");

    return 0;
}

