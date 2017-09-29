#include "stdio.h"
#include "stdlib.h"

#define VARS              3

#define IMPVAL(b1, b2)  (b1 && !b2 ? FALSE : TRUE)
#define BIMPVAL(b1, b2) (b1 == b2)

#define FALSE 0
#define TRUE 1

int L = 0, T = 0;

char nome[VARS] = {'P', 'Q', 'R'};
int I[VARS]={FALSE};

typedef enum tagTipo {
  NEG, AND, OR, IMP, BIMP, P, Q, R
} Tipo;

typedef struct tagForm
{
  Tipo tipo;
  struct tagForm *dir;
  struct tagForm *esq;
} Formula;

Formula* cria_formula(Tipo tipo, Formula *dir, Formula *esq)
{
  Formula *res = (Formula*) malloc(sizeof(Formula));

  if (res == NULL)
    return NULL;

  res->tipo = tipo;
  res->dir = dir;
  res->esq = esq;

  return res;
}

Formula *var_p()
{
  return cria_formula(P, NULL, NULL);
}

Formula *var_q()
{
  return cria_formula(Q, NULL, NULL);
}

Formula *var_r()
{
  return cria_formula(R, NULL, NULL);
}

Formula* neg(Formula *e)
{
  return cria_formula(NEG, e, NULL);
}

Formula* and(Formula *d, Formula *e)
{
  return cria_formula(AND, d, e);
}

Formula* or(Formula *d, Formula *e)
{
  return cria_formula(OR, d, e);
}

Formula* imp(Formula *d, Formula *e)
{
  return cria_formula(IMP, d, e);
}

Formula* bimp(Formula *d, Formula *e)
{
  return cria_formula(BIMP, d, e);
}

int indice_variavel(Tipo f)
{
    if(f == P)
        return 0;
    if(f == Q)
        return 1;
    if(f == R)
        return 2;
}

int valor_formula(Formula *f)
{
  switch(f->tipo) {
  case P:
      return I[indice_variavel(f->tipo)];
  case Q:
      return I[indice_variavel(f->tipo)];
  case R:
      return I[indice_variavel(f->tipo)];

  case NEG:
      return !valor_formula(f->dir);

  case AND:
      return valor_formula(f->dir) &&
             valor_formula(f->esq);

  case OR:
      return valor_formula(f->dir) ||
             valor_formula(f->esq);

  case IMP:
      return IMPVAL(valor_formula(f->dir),
                    valor_formula(f->esq));

  case BIMP:
      return BIMPVAL(valor_formula(f->dir),
                     valor_formula(f->esq));
  }
}

void mostra_tabela(Formula *f)
{
  int fim = FALSE;

  //cria_formula(f);

 // printf("Formula:\n");
 // printf("H = (P -> Q) /\\ (~Q \\/ R)\n\n");

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
  if (valor_formula(f)){
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

void destroi_formula(Formula *f){
    free(f);
}


int main(int argc, char **argv)
{

  //(P \/ (Q /\ R)) -> ((P \/ Q) /\ (P \/ R))

  Formula *f = imp(or(var_p(),and(var_q(), var_r())),
                   and(or(var_p(), var_q()), or(var_p(), var_r())));


  printf("Calculo de tabela-verdade\n\n");
  printf("Formula:\n");
  printf("H = (P \\/ (Q /\\ R)) -> ((P \\/ Q) /\\ (P \\/ R))\n\n");

  mostra_tabela(f);

  destroi_formula(f);

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
