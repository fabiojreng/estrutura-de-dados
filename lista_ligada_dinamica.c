#include <stdio.h>
#include <malloc.h>


typedef struct{
    int chave;
} REGISTRO; 

typedef struct aux{
    REGISTRO reg;
    struct aux *prox;
} ELEMENTO;

typedef ELEMENTO *PONT;

typedef struct{
    PONT inicio;
} LISTA;


    // inicializar a LISTA
void inicializarLista(LISTA *l){
    l->inicio = NULL;
    printf("Lista inicializada...\n");
}

void reinicialiarLista(LISTA *l){
    PONT aux = l->inicio;
    
    while(aux != NULL){
        PONT apagar = aux;
        aux = aux->prox;
        free(apagar);
    }
    l->inicio = NULL;
    printf("Lista reinicializada...\n");
}

void tamanhoLista(LISTA *l){
    PONT aux = l->inicio;
    int tam = 0;
    
    while(aux != NULL){
        tam++;
        aux = aux->prox;
    }
    printf("Tamanho da lista: %d\n", tam);
}

void exibirLista(LISTA *l){
    PONT aux = l->inicio;
    printf("Lista: [ ");
    while(aux != NULL){
        printf("%d ", aux->reg.chave);
        aux = aux->prox;
    }
    printf("]\n");
}

PONT buscarElemento(LISTA *l, int ch){
    PONT atual = l->inicio;
    
    if(atual == NULL)
        return NULL;
    
    while(atual != NULL && atual->reg.chave < ch)
        atual = atual->prox;
    if(atual != NULL && atual->reg.chave == ch)
        return atual;
    return NULL;       
}

PONT buscaAux(LISTA *l, int ch, PONT *ant){
    *ant = NULL;
    PONT atual = l->inicio;
    
    if(atual == NULL)
        return NULL;
    
    while(atual != NULL && atual->reg.chave < ch){
        *ant = atual;
        atual = atual->prox;
    }
    if(atual != NULL && atual->reg.chave == ch)
        return atual;
    return NULL;
}

int inserirElemento(LISTA *l, int ch){
    PONT ant, atual;
    atual = buscaAux(l, ch, &ant);
    
    if(atual != NULL)
        return 0;
    
    atual = (PONT) malloc(sizeof(ELEMENTO));
    atual->reg.chave = ch;
    
    if(ant == NULL){ // inserindo pela primeira vez 
        atual->prox = l->inicio;
        l->inicio = atual;
    }else{
        atual->prox = ant->prox;
        ant->prox = atual;
    }
    return 1;   
}

int main(){
    
    LISTA lista;
    
    inicializarLista(&lista);
    
    
    inserirElemento(&lista, 5);
    inserirElemento(&lista, 2);
    inserirElemento(&lista, 7);
    inserirElemento(&lista, -9);
    
    exibirLista(&lista);
    tamanhoLista(&lista);
    reinicialiarLista(&lista);
    
    exibirLista(&lista);

    return 0;
}
