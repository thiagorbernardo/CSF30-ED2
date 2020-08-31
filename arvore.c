#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Arvore *constroi_arv(char elem, Arvore *esq, Arvore *dir)
{
	Arvore *arv = (Arvore *)malloc(sizeof(Arvore));
	arv->info = elem;
	arv->esq = esq;
	arv->dir = dir;
	return arv;
}

Arvore *cria_arv_vazia()
{
	return NULL;
}

int verifica_arv_vazia(Arvore *a)
{
	return (a == NULL);
}

void arv_libera(Arvore *a)
{
	if (!verifica_arv_vazia(a))
	{
		arv_libera(a->esq);
		arv_libera(a->dir);
		free(a);
	}
}

void destroi_arv(Arvore *arv)
{
	if (arv != NULL)
	{
		destroi_arv(arv->esq);
		destroi_arv(arv->dir);
		free(arv);
	}
}

void pre_order(Arvore *arv)
{
	printf("%d ", arv->info);
	if (arv->esq != NULL)
		pre_order(arv->esq);

	if (arv->dir != NULL)
		pre_order(arv->dir);
}

void in_order(Arvore *arv)
{
	if (arv->esq != NULL)
		in_order(arv->esq);

	printf("%d ", arv->info);

	if (arv->dir != NULL)
		in_order(arv->dir);
}

void pos_order(Arvore *arv)
{
	if (arv->esq != NULL)
		pos_order(arv->esq);

	if (arv->dir != NULL)
		pos_order(arv->dir);

	printf("%d ", arv->info);
}

void imprime_arv_marcadores(Arvore *arv)
{
	printf("<");
	printf("%d", arv->info);
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

int pertence_arv(Arvore *arv, char c)
{
	int x, y;
	if (arv->info == c)
		return 1;
	if (arv->esq != NULL)
		x = pertence_arv(arv->esq, c);
	if (x == 1)
		return 1;
	if (arv->dir != NULL)
		y = pertence_arv(arv->dir, c);

	return y;
}

int conta_nos(Arvore *arv)
{
	int nos = 1;

	if (arv->esq != NULL)
		nos += conta_nos(arv->esq);

	if (arv->dir != NULL)
		nos += conta_nos(arv->dir);

	return (nos);
}

int calcula_altura_arvore(Arvore *arv)
{

	if (verifica_arv_vazia(arv))
		return -1;

	int alturaEsq, alturaDir;

	if (arv->esq != NULL)
		alturaEsq = calcula_altura_arvore(arv->esq);
	else
		alturaEsq = 0;

	if (arv->dir != NULL)
		alturaDir = calcula_altura_arvore(arv->dir);
	else
		alturaDir = 0;

	if (alturaEsq > alturaDir)
		return (alturaEsq + 1);
	else
		return (alturaDir + 1);
}

int conta_nos_folha(Arvore *arv)
{
	int nos = 0;

	if (arv->esq != NULL)
		nos = conta_nos(arv->esq);

	if (arv->dir != NULL)
		nos = conta_nos(arv->dir);

	if (arv->esq == NULL && arv->dir == NULL)
		nos += 1;

	return nos;
}

Arvore *inserir(Arvore *arv, int v)
{
	if (arv == NULL)
	{
		arv = (Arvore *)malloc(sizeof(Arvore));
		arv->info = v;
		arv->esq = NULL;
		arv->dir = NULL;
	}
	else if (v < arv->info)
		arv->esq = inserir(arv->esq, v);
	else
		arv->dir = inserir(arv->dir, v);
	return arv;
}

Arvore *remover(Arvore *a, int v)
{
	if (a == NULL)
		return NULL;
	else
	{
		if (v < a->info)
			a->esq = remover(a->esq, v);
		else if (v > a->info)
			a->dir = remover(a->dir, v);
		else if ((a->esq == NULL) && (a->dir == NULL))
		{
			free(a);
			a = NULL;
		}
		else if (a->dir == NULL)
		{
			Arvore *tmp = a;
			a = a->esq;
			free(tmp);
		}
		else if (a->esq == NULL)
		{
			Arvore *tmp = a;
			a = a->dir;
			free(tmp);
		}
		else
		{
			Arvore *tmp = a->esq;
			while (tmp->dir != NULL)
				tmp = tmp->dir;
			a->info = tmp->info;
			tmp->info = v;
			a->esq = remover(a->esq, v);
		}
	}
	return a;
}

int buscar(Arvore *arv, int v)
{
	if (arv == NULL)
		return 0;
	else if (v < arv->info)
		return buscar(arv->esq, v);
	else if (v > arv->info)
		return buscar(arv->dir, v);
	else
		return 1;
}

int min(Arvore *a)
{
	if (a == NULL)
		return 0;
	while (a->esq != NULL)
		return min(a->esq);
	return a->info;
}

int max(Arvore *a)
{
	if (a == NULL)
		return 0;
	while (a->dir != NULL)
		return max(a->dir);
	return a->info;
}

void imprime_decrescente(Arvore *a)
{
	if (a->dir != NULL)
		imprime_decrescente(a->dir);
	printf("%d ", a->info);
	if (a->esq != NULL)
		imprime_decrescente(a->esq);
}

int maior_ramo(Arvore *a)
{
	if (a != NULL)
	{
		if (a->esq != NULL && a->dir != NULL)
		{
			if (a->info + maior_ramo(a->esq) >= a->info + maior_ramo(a->dir))
				return a->info + maior_ramo(a->esq);
			else
				return a->info + maior_ramo(a->dir);
		}
		else if (a->esq != NULL)
			return a->info + maior_ramo(a->esq);
		else if (a->dir != NULL)
			return a->info + maior_ramo(a->dir);
		else
			return a->info;
	}
}

int ancestral(Arvore *a, int e1, int e2)
{
	if (a == NULL)
		return 0;
	else if (e1 < a->info && e2 < a->info)
		return ancestral(a->esq, e1, e2);
	else if (e1 > a->info && e2 > a->info)
		return ancestral(a->dir, e1, e2);
	else
		return a->info;
}

int main()
{

	int i = 0;
	Arvore *a = cria_arv_vazia();

	a = inserir(a, 50);
	a = inserir(a, 30);
	a = inserir(a, 90);
	a = inserir(a, 20);
	a = inserir(a, 40);
	a = inserir(a, 95);
	a = inserir(a, 10);
	a = inserir(a, 35);
	a = inserir(a, 37);

	//a = remover(a, 10);

	printf("\nEx1: ");
	pre_order(a);
	printf("\n%d ", buscar(a, 40));
	printf("\nEx2: %d ", min(a));
	printf("\nEx2: %d ", max(a));
	//printf("\nEx3 %d ", buscar(a, 100000)); //13.473
	//printf("\nEx4 %d ", buscar(a, 100000)); //11.449
	printf("\nEx4: ");
	imprime_decrescente(a);
	printf("\nEx5: %d", maior_ramo(a));
	printf("\nEx6: %d", ancestral(a, 10, 35));

	return 0;
}
