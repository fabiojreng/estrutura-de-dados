#include <stdio.h>
#include <malloc.h>

typedef int TIPOCHAVE;

typedef struct {
    TIPOCHAVE chave;
} REGISTRO;

typedef struct aux {
    REGISTRO reg;
    struct aux* prox;
} ELEMENTO;

typedef ELEMENTO* PONT;

typedef struct {
    PONT cabeca;
} LISTA;

void inicializarLista(LISTA *l){
    l->cabeca = (PONT)malloc(sizeof(ELEMENTO)); //criando nó cabeça
    l->cabeca->prox = l->cabeca; // campo prox recebe o endereço do nó cabeça 
}

int tamanho(LISTA *l){
    PONT end = l->cabeca->prox;
    int tam = 0;
    while (end != l->cabeca){ // como não existe NULL, percorrer até encontrar o nó cabeça
        tam++;
        end = end->prox;
    }
    return tam;
}

void exibirLista(LISTA* l) {
    PONT end = l->cabeca->prox;
    printf("Lista: ");
    while (end != l->cabeca) {
        printf("%d ", end->reg.chave);
        end = end->prox;
    }
}

PONT buscaSentinelaOrd(LISTA* l, TIPOCHAVE ch) {
    PONT pos = l->cabeca->prox;
    l->cabeca->reg.chave = ch;
    while (pos->reg.chave < ch) 
        pos = pos->prox;
    if (pos != l->cabeca && pos->reg.chave==ch) 
        return pos;
    return NULL;
}

PONT buscaSeqExc(LISTA* l, TIPOCHAVE ch, PONT* ant) {
    *ant = l->cabeca;
    PONT atual = l->cabeca->prox;
    l->cabeca->reg.chave = ch;
    while (atual->reg.chave<ch) {
        *ant = atual;
        atual = atual->prox;
    }
    if (atual != l->cabeca && atual->reg.chave == ch) 
        return atual;
    return NULL;
}

int inserirElemListaOrd(LISTA* l, REGISTRO reg) {
    PONT ant, i;
    i = buscaSeqExc(l,reg.chave,&ant);
    if (i != NULL) 
        return 0;

    i = (PONT) malloc(sizeof(ELEMENTO));
    i->reg = reg;
    i->prox = ant->prox;
    ant->prox = i;
    return 1;
}

int excluirElemLista(LISTA* l, TIPOCHAVE ch) {
    PONT ant, i;
    i = buscaSeqExc(l,ch,&ant);
    if (i == NULL) 
        return 0;

    ant->prox = i->prox;
    free(i);
    return 1;
}

void reinicializarLista(LISTA* l){
    PONT end = l->cabeca->prox;
    while (end != l->cabeca){
        PONT apagar = end;
        end = end->prox;
        free(apagar);
    }
    l->cabeca->prox = l->cabeca;
}

int main(){

    return 0;
}