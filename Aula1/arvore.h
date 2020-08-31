#include <stdio.h>
#include <stdlib.h>

typedef struct _arvore {
   char info;
   struct _arvore *esq;
   struct _arvore *dir;
} Arvore;

Arvore* cria_arv_vazia ();

void destroi_arv (Arvore *arv);

Arvore* constroi_arv (char elem, Arvore *esq, Arvore *dir);

int verifica_arv_vazia (Arvore *a);

void arv_libera (Arvore* a);

void pre_order(Arvore *arv);
void in_order(Arvore *arv);
void pos_order(Arvore *arv);

void imprime_arv_marcadores (Arvore* arv);

int pertence_arv (Arvore *a, char c);

int conta_nos (Arvore *a);

int calcula_altura_arvore (Arvore *a);

int conta_nos_folha (Arvore *a);
