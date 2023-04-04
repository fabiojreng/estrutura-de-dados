#include <stdio.h>
#include <stdlib.h>

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

PONT buscaElemento(PONT raiz, int ch){
    if(!raiz) return NULL;
    if(raiz->chave == ch) return raiz; // verifica se eh a chave buscada
    if(raiz->chave > ch)
        buscaElemento(raiz->esq, ch);
    buscaElemento(raiz->dir, ch);
}

int qtdElementos(PONT raiz){
    if(raiz == NULL) return 0;
    return (qtdElementos(raiz->esq) + 1 + qtdElementos(raiz->dir));
}

PONT buscaNo(PONT raiz, int ch, PONT *pai){
    PONT atual = raiz;
    *pai = NULL;
    while (atual){
        if(atual->chave == ch) return atual;
        *pai = atual;
        if(atual->chave > ch) atual = atual->esq;
        else atual = atual->dir;
    }
    return NULL;
}

PONT removerNo(PONT raiz, int chave){
    PONT pai, no, pai_subs, subs;
    no = buscaNo(raiz, chave, &pai);
    if(no == NULL) return raiz;

    //caso tenha um unico filho
    if(!no->esq || !no->dir){ // caso a raiz tenha apenas uma subarvore
        if(!no->esq) subs = no->dir; // se nao tiver a esquerda, vou para direita
        else subs = no->esq;
    } 
    //caso tenha dois filhos
    else{
        pai_subs = no;
        subs = no->esq;
        while(no->dir){ // percorrer o elemento mais a direita, da subarvore da esquerda
            pai_subs = subs;
            subs = subs->dir;
        }
        if(pai_subs != no){
            pai_subs->dir = subs->esq;
            subs->esq = no->esq;
        }
        subs->dir = no->dir;
    }
    //caso seja o no seja a raiz
    if(!pai){
        free(no);
        return subs;
    }
    //caso nao seja a raiz
    if(chave < pai->chave)
        pai->esq = subs;
    else    
        pai->dir = subs;

    free(no);
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

    PONT r;
    
    incializar(&r);
    
    r = inserir(r, 12);
    inserir(r, 16);
    inserir(r, 11);
    inserir(r, 15);
    
    //printf("CHAVE: %p\n", buscaElemento(r, 16));
    //printf("QUANTIDADE DE ELEMENTOS: %d\n", qtdElementos(r));
    
    exibir(r);
    removerNo(r, 11);
    printf("\n");
    exibir(r);

    printf("\n");
    return 0;
}