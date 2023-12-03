#include <stdio.h>
#include<stdlib.h>

typedef struct aux{
    int chave;
    struct aux *esq;
    struct aux *dir;
}NO, *PONT;

void incializar(PONT *raiz){
    *raiz = NULL;
}

PONT criarNovoNo(int ch){
    PONT no = (PONT)malloc(sizeof(NO));
    no->chave = ch;
    no->dir = NULL;
    no->esq = NULL;
    return no;
}

PONT inserir(PONT raiz, int ch){
    PONT no = criarNovoNo(ch); // criando o no para ser inserido
    if(raiz == NULL) return no;
    if(raiz->chave > no->chave)
        raiz->esq = inserir(raiz->esq, ch);
    else
        raiz->dir = inserir(raiz->dir, ch);
    
    return raiz;
}

PONT maiorAEsquerda(PONT p, PONT *ant){
    *ant = p; 
    p = p->esq; 
    while(p->dir){ 
        *ant = p;
        p = p->dir;
    }
    return p; 
}

PONT buscaNo(PONT raiz, int ch, PONT *pai){
    PONT atual = raiz;
    *pai = NULL;
    while (atual){
        if(atual->chave == ch) 
            return atual;
        *pai = atual;
        if(atual->chave > ch) 
            atual = atual->esq;
        else 
            atual = atual->dir;
    }
    return NULL;
}

PONT buscaBinIterativa(PONT raiz, int ch){
    PONT atual = raiz;
    while(atual){
        if(atual->chave == ch) return atual;
        if(ch < atual->chave) atual = atual->esq;
        else atual = atual->dir;
    }
    return NULL;
}

int exluirNo(PONT *raiz, int ch){
    PONT atual, no_pai, substituto, maiorEsq, paiMaiorEsq;
    atual = buscaNo(*raiz, ch, &no_pai);
    if(!atual) return 0;

    if(!atual->esq || !atual->dir){ //caso tenha apenas 1 filho
        if(atual->esq) 
            substituto = atual->esq;
        else 
            substituto = atual->dir;
        //verifica se o no a ser removido eh a raiz
        if(!no_pai){
            *raiz = substituto;
        } else{
            if(no_pai->esq == atual) 
                no_pai->esq = substituto;
            else 
                no_pai->dir = substituto;
        }
        free(atual);
    }
        
    else{ // caso tenha 2 filhos
        maiorEsq = maiorAEsquerda(atual, &paiMaiorEsq);
        atual->chave = maiorEsq->chave;

        if(paiMaiorEsq->esq == maiorEsq) 
            paiMaiorEsq->esq = maiorEsq->esq;
        else   
            paiMaiorEsq->dir = maiorEsq->esq;
        
        free(maiorEsq);
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
    incializar(&r);
    r = inserir(r, 10);
    inserir(r, 11);
    inserir(r, 12);
    inserir(r, 5);
    inserir(r, 9);
    exibir(r);
    
    printf("\nBUSCA: %p\n", buscaBinIterativa(r, 10));

    exluirNo(&r, 10);
    printf("\n");
    exibir(r);
    
    return 0;
}
