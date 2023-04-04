#include <stdio.h>

#define MAX 3
#define INVALIDO -1

typedef int TIPOCHAVE;

typedef struct{
    TIPOCHAVE chave;
}REGISTRO;

typedef struct{
    REGISTRO reg;
    int prox;
}ELEMENTO;

typedef struct{
    ELEMENTO A[MAX];
    int inicio;
    int dispo;
}LISTA;

// criar os espaços da lista 
void inicializarLista(LISTA *lista){
    for (int i = 0; i < MAX-1; i++)
        lista->A[i].prox = i+1;
    lista->A[MAX-1].prox = INVALIDO;
    lista->inicio = INVALIDO;
    lista->dispo = 0;    
}

// retornar a quantidade de elementos da lista
int tamanhoLista(LISTA *lista){
    int i = lista->inicio;
    int tam = 0;
    while (i != INVALIDO){
        tam++;
        i = lista->A[i].prox;
    }
    return tam;
}

// mostrar os valores da lista
void imprimirLista(LISTA *lista){
    int i = lista->inicio;
    printf("Lista: \" ");
    while (i != INVALIDO){
        printf("%d ", lista->A[i].reg.chave);
        i = lista->A[i].prox;
    }
    printf(" \"\n");
}

// procurar valor dentro da lista ordenada 
void buscaSequencialOrd(LISTA *lista, int chave){
    int i = lista->inicio;
    while (i != INVALIDO && lista->A[i].reg.chave < chave){
        i = lista->A[i].prox;
    }
    if(i != INVALIDO && lista->A[i].reg.chave == chave)
        printf("Valor encontrado na posição: %d \n", i);
    else
        printf("%d \n", INVALIDO);
}

// função auxiliar que retorna a posição do 1º elemento dispo
int obterNo(LISTA *lista){
    int resultado = lista->dispo;
    if (lista->dispo != INVALIDO)
        lista->dispo = lista->A[lista->dispo].prox; // atualiza para o próximo elemento como disponível
    return resultado;
}

int inserirElemListaOrd(LISTA *lista, REGISTRO reg){
    if(lista->dispo == INVALIDO)
        return 0;
    int ant = INVALIDO;
    int i = lista->inicio;
    TIPOCHAVE chave = reg.chave;
    
    while (i != INVALIDO && lista->A[i].reg.chave < chave){
        ant = i;
        i = lista->A[i].prox;
    }
    if(i != INVALIDO && lista->A[i].reg.chave == chave)
        return 0; 
    i = obterNo(lista);
    lista->A[i].reg = reg;
    if(ant == INVALIDO){
        lista->A[i].prox = lista->inicio;
        lista->inicio = i;
    }
    else{
        lista->A[i].prox = lista->A[ant].prox;
        lista->A[ant].prox = i;
    }
    printf("inicio: %d\nANT: %d\ni: %d\ndispo: %d\n", lista->inicio, ant,i, lista->dispo);
    return 1;
}

void devolverNo(LISTA *lista, int j){
    lista->A[j].prox = lista->dispo;
    lista->dispo = j;
}

int excluirElemento(LISTA *lista, TIPOCHAVE chave){
    int ant = INVALIDO;
    int i = lista->inicio;

    while (i != INVALIDO && lista->A[i].reg.chave < chave){
        ant = i;
        i = lista->A[i].prox;
    }
    if(i == INVALIDO || lista->A[i].reg.chave != chave)
        return 0;
    if(ant == INVALIDO)
        lista->inicio = lista->A[i].prox;
    else
        lista->A[ant].prox = lista->A[i].prox;
    devolverNo(lista, i);
    return 1;
}


void reinicialiarLista(LISTA *lista){
    inicializarLista(lista);
}

int main(){
    LISTA lista;
    REGISTRO reg;

    inicializarLista(&lista);

    reg.chave = 5;
    inserirElemListaOrd(&lista, reg);
    reg.chave = 2;
    inserirElemListaOrd(&lista, reg);
    reg.chave = 1;
    inserirElemListaOrd(&lista, reg);
   
    imprimirLista(&lista);

    // excluirElemento(&lista, 5);
    // imprimirLista(&lista);
    return 0;
}