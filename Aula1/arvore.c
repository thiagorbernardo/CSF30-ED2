#include "arvore.h"

Arvore *constroi_arv(char elem, Arvore *esq, Arvore *dir) {
	Arvore *arv = (Arvore *)malloc(sizeof(Arvore));
	arv->info = elem;
	arv->esq = esq;
	arv->dir = dir;
	return arv;
}

Arvore *cria_arv_vazia() {
	return NULL;
}

int verifica_arv_vazia (Arvore *a) {
	return (a == NULL);
}

void arv_libera (Arvore* a) {
	if (!verifica_arv_vazia(a)) {
		arv_libera (a->esq);
		arv_libera (a->dir);
		free(a);
	}
}

void destroi_arv(Arvore *arv) {
	if (arv != NULL) {
		destroi_arv(arv->esq);
		destroi_arv(arv->dir);
		free(arv);
	}
}

void pre_order(Arvore *arv) {
	printf("%c ", arv->info);
	if (arv->esq != NULL)
		pre_order(arv->esq);

	if (arv->dir != NULL)
		pre_order(arv->dir);
}
void in_order(Arvore *arv) {
	if (arv->esq != NULL)
		in_order(arv->esq);

	printf("%c ", arv->info);

	if (arv->dir != NULL)
		in_order(arv->dir);
}
void pos_order(Arvore *arv) {
	if (arv->esq != NULL)
		pos_order(arv->esq);

	if (arv->dir != NULL)
		pos_order(arv->dir);

	printf("%c ", arv->info);
}
void imprime_arv_marcadores (Arvore* arv){
	printf("<");
	printf("%c", arv->info);
	if (arv->esq != NULL)
		imprime_arv_marcadores(arv->esq);
	else
		printf("<>");
	
	if (arv->dir != NULL)
		imprime_arv_marcadores(arv->dir);
	else
		printf("<>");
	printf(">");
	
}
int pertence_arv (Arvore *arv, char c){
	int x, y;
	if(arv->info == c)
		return 1;
	if (arv->esq != NULL)
		x = pertence_arv(arv->esq, c);
	if(x == 1)
		return 1;
	if (arv->dir != NULL)
		y = pertence_arv(arv->dir, c);
	return y;
}
int conta_nos (Arvore *arv){
	int nos = 1;
	
	if (arv->esq != NULL)
		nos += conta_nos(arv->esq);

	if (arv->dir != NULL)
		nos += conta_nos(arv->dir);

	return (nos);
}
int calcula_altura_arvore (Arvore *arv){
	
	if(verifica_arv_vazia(arv))
		return -1;
	
	int alturaEsq, alturaDir;
	
	if (arv->esq != NULL)
		alturaEsq  = calcula_altura_arvore(arv->esq);
	else
		alturaEsq = 0;

	if (arv->dir != NULL)
		alturaDir = calcula_altura_arvore(arv->dir);
	else
		alturaDir = 0;
	
	if(alturaEsq > alturaDir)
		return (alturaEsq + 1);
	else
		return (alturaDir + 1);
}
int conta_nos_folha (Arvore *arv){
	int nos = 0;
	
	if (arv->esq != NULL)
		nos = conta_nos(arv->esq);

	if (arv->dir != NULL)
		nos = conta_nos(arv->dir);
	
	if(arv->esq == NULL && arv->dir == NULL)
		nos += 1;
	
	return nos;
}

int main() {
	char caracter = 'a';
	Arvore *a = constroi_arv ('a',
	                          constroi_arv('b',
	                                       cria_arv_vazia(),
	                                       constroi_arv('d',cria_arv_vazia(),cria_arv_vazia())
	                                      ),
	                          constroi_arv('c',
	                                       constroi_arv('e',cria_arv_vazia(),cria_arv_vazia()),
	                                       constroi_arv('f',cria_arv_vazia(),cria_arv_vazia())
	                                      )
	                         );
	printf ("Ex1:");

	printf ("\npre-order: ");
	pre_order(a);

	printf ("\nin-order: ");
	in_order(a);

	printf ("\npos-order: ");
	pos_order(a);
	
	printf ("\n\nEx2: ");
	
	imprime_arv_marcadores(a);
	
	printf ("\n\nEx3: %d", pertence_arv(a, caracter));
	
	printf ("\n\nEx4: %d", conta_nos(a));
	
	printf ("\n\nEx5: %d", calcula_altura_arvore(a));

	printf ("\n\nEx6: %d", conta_nos_folha(a));
}
