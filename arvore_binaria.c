#include <stdio.h>
#include <stdlib.h>

typedef enum{esquerdo, direito}LADO;

typedef struct aux{
    int chave;
    struct aux *esq;
    struct aux *dir;
} NO, *PONT;


PONT criarNovoNo(int chave){
    PONT novoNo = (PONT)malloc(sizeof(NO));
    novoNo->chave = chave;
    novoNo->dir = NULL;
    novoNo->esq = NULL;
    return novoNo;
}
void criarRaiz(PONT *raiz, int chave){
    *raiz = criarNovoNo(chave);
}

PONT buscaChave(PONT raiz, int chave){
    if(raiz == NULL) return NULL; // sair quando não existir raiz
    if(raiz->chave == chave) return raiz;
    PONT aux = buscaChave(raiz->esq, chave);
    if(aux) return aux;
    return buscaChave(raiz->dir, chave);
}

int inserirFilho(PONT raiz, int novaChave, int chavePai, LADO lado){
    PONT pai = buscaChave(raiz, chavePai);
    if(!pai) return 0;
    PONT novo = criarNovoNo(novaChave);
    if(lado == esquerdo){
        novo->esq = pai->esq;
        pai->esq = novo;
    }
    else{
        novo->dir = pai->dir;
        pai->dir = novo;
    }
    return 1;
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

    PONT r;

    criarRaiz(&r, 12);
    inserirFilho(r, 16, 12, esquerdo);
    inserirFilho(r, 19, 12, direito);
    exibir(r);

    return 0;
}