#include <stdio.h>
#include <stdlib.h>

typedef struct aux {
  int chave;
  struct aux *esq;
  struct aux *dir;
  int h;
} NO, * PONT;


PONT criaNo(int ch){
  PONT novoNo = (PONT) malloc(sizeof(NO));
  novoNo->esq = NULL;
  novoNo->dir = NULL;
  novoNo->chave = ch;
  novoNo->h = 0;
  return novoNo;
}

PONT inicializa(){
  return NULL;
}

int max(int a, int b){
  if(a > b) return a;
  return b;
}

int altura(PONT raiz){
  if(!raiz) return -1;
  return raiz->h;
}

// rotação à direita
PONT direita(PONT r){
  PONT aux;
  aux = r->esq;
  r->esq = aux->dir;
  aux->dir = r;

  r->h = max(altura(r->dir),altura(r->esq)) + 1;
  aux->h = max(altura(aux->esq), r->h) + 1;

  return aux;
}

// rotação à esquerda
PONT esquerda(PONT r){
  PONT aux;
  aux = r->dir;
  r->dir = aux->esq;
  aux->esq = r;

  r->h = max(altura(r->dir),altura(r->esq)) + 1;
  aux->h = max(altura(aux->dir), r->h) + 1;

  return aux;
}

PONT esquerdaDireita(PONT r){
  r->esq = esquerda(r->esq);
  return direita(r);
}

PONT direitaEsquerda(PONT r){
  r->dir = direita(r->dir);
  return esquerda(r);
}


PONT insere(PONT raiz, int ch){
  if(!raiz) return criaNo(ch);

  if(ch < raiz->chave){
    raiz->esq = insere(raiz->esq, ch);
    if((altura(raiz->esq) - altura(raiz->dir)) == 2)
      if(ch < raiz->esq->chave)
        raiz = direita(raiz);
      else
        raiz = esquerdaDireita(raiz);

  } else 
      if(ch > raiz->chave){
        raiz->dir = insere(raiz->dir, ch);
        if((altura(raiz->dir) - altura(raiz->esq)) == 2) 
          if(ch > raiz->dir->chave)
            raiz = esquerda(raiz);
          else
            raiz = direitaEsquerda(raiz);
      }
  raiz->h = max(altura(raiz->esq), altura(raiz->dir)) + 1;

  return raiz;
}

void exibir(PONT raiz){
  if(raiz){
    printf("%d(", raiz->chave);
    exibir(raiz->esq);
    exibir(raiz->dir);
    printf(")");
  }
}

int main(){

  PONT r = inicializa();

  r = insere(r, 40);
  r = insere(r, 20);
  r = insere(r, 10);
  //r = insere(r, 15);
  r = insere(r, 30);
  r = insere(r, 35);
  r = insere(r, 80);


  exibir(r);



  return 0;
}