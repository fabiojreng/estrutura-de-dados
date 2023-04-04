#include <stdio.h>
#include <stdlib.h>

typedef struct aux{
    int ch;
    struct aux *ant;
    struct aux *prox;
} ELEMENTO, *PONT; // PONT eh um ponteiro para ELEMENTO 

typedef struct{
    PONT cabeca;
} DEQUE;

// duplamente ligado
void inicializar(DEQUE *d){
    d->cabeca = (PONT)malloc(sizeof(ELEMENTO));
    d->cabeca->prox = d->cabeca;
    d->cabeca->ant = d->cabeca;
}

void tamanho(DEQUE *d){
    PONT aux = d->cabeca->prox;
    int tam = 0;
    while(aux != d->cabeca){ // percorrer todo o deque ate chegar no cabeca
        tam++;
        aux = aux->prox;
    }
    printf("Tamanho igual a: %d\n", tam);
}

void exibeDequeFim(DEQUE *d){
    PONT aux = d->cabeca->ant;
    printf("Imprimindo deque do final para o inicio:\n");
    while(aux != d->cabeca){ // percorre todo o deque do final ate o cabeca, regredindo
        printf("%d ", aux->ch);
        aux = aux->ant;
    }
    printf("\n");
}

int inserirDequeFim(DEQUE *d, int chave){
    PONT novo = (PONT)malloc(sizeof(ELEMENTO));
    novo->ch = chave;
    novo->prox = d->cabeca; // o proximo do ultimo recebe o no cabeca
    novo->ant = d->cabeca->ant; // o anterior de novo recebe o antigo ultimo elemento
    d->cabeca->ant = novo; // o último elemento recebe o novo
    novo->ant->prox = novo; // onde o ultimo apontava agora aponta para o novo
    return 1;
}

void exibeDequeInicio(DEQUE *d){
    PONT aux = d->cabeca->prox;
    printf("Imprimindo deque do inicio para o final:\n");
    while(aux != d->cabeca){ // percorre todo o deque do inicio ate o cabeca, indo para o prox
        printf("%d ", aux->ch);
        aux = aux->prox;
    }
    printf("\n");
}

int inserirDequeInicio(DEQUE *d, int chave){
    PONT novo = (PONT)malloc(sizeof(ELEMENTO));
    novo->ch = chave;
    novo->ant = d->cabeca;
    novo->prox = d->cabeca->prox;
    d->cabeca->prox = novo;
    return 1;
}


int excluirElemDequeFinal(DEQUE *d, int *chave){
    if(d->cabeca->prox == d->cabeca)
        return 0;
    PONT apagar = d->cabeca->ant;
    *chave = apagar->ch;
    d->cabeca->ant = apagar->ant;
    apagar->prox = apagar->prox;
    free(apagar);
    return 1;
}


int excluirElemDequeInicio(DEQUE *d, int *chave){
    if(d->cabeca->prox == d->cabeca) // nao existe elemento
        return 0;
    PONT apagar = d->cabeca->prox;
    *chave = apagar->ch; // guardo o valor que foi apagado
    d->cabeca->prox = apagar->prox;
    apagar->prox->ant = d->cabeca;
    free(apagar);
    return 1;
}

void reinicializar(DEQUE *d){
    PONT aux = d->cabeca->prox;
    while (aux != d->cabeca){
        PONT apagar = aux;
        aux = aux->prox;
        free(apagar);
    }
    d->cabeca->prox = d->cabeca;
    d->cabeca->ant = d->cabeca;
}

int main(){
    
    DEQUE d;

    inicializar(&d);
    
        //inserindo no final
    inserirDequeFim(&d, 8);
    inserirDequeFim(&d, 13);
    inserirDequeFim(&d, 3);    

    //int *valor = 5;
    //excluirElemDequeFinal(&d, &valor);
    exibeDequeFim(&d);
    

        //inserindo no inicio
    // inserirDequeInicio(&d, 8);
    // inserirDequeInicio(&d, 13);
    // inserirDequeInicio(&d, 3);
    //excluirElemDequeInicio(&d, &valor);
    //exibeDequeInicio(&d);

    tamanho(&d);
    //reinicializar(&d);
   

    return 0;
}
