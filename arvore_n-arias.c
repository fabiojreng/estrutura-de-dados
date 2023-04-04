#include <stdio.h>
#include <stdlib.h>

typedef struct aux{
    int chave;
    struct aux *primFilho;
    struct aux *proxIrmao;
} NO, *PONT;


PONT criarNovoNo(int chave){
    PONT novo = (PONT)malloc(sizeof(NO));
    novo->primFilho = NULL;
    novo->proxIrmao = NULL;
    novo->chave = chave;
    return novo;
}
void inicializar(PONT *raiz, int ch){
    *raiz = criarNovoNo(ch);
}

PONT buscaChave(int chave, PONT raiz){
    if(!raiz) return NULL;
    if(raiz->chave == chave) return raiz; // verifica se a chave da raiz eh a buscada

    PONT p = raiz->primFilho;
    while(p){ // enquanto existir um filho, fica na condicao
        PONT aux =  buscaChave(chave, p);
        if(aux) return aux; // se existir um filho valido retorna-o
        p = p->proxIrmao; // quando nao tiver filho, vai para o irmao
    }
    return NULL; // se o valor nao for encontrado
}

int inserir(PONT raiz, int novaChave, int chavePai){
    PONT pai = buscaChave(chavePai, raiz);
    if(!pai) return 0;
    PONT filho = criarNovoNo(novaChave); // cria-se um no para o filho
    PONT p = pai->primFilho; // variavel auxiliar que recebe o primeiro filho, caso exista
    if(!p) pai->primFilho = filho; // se o pai não tem filhos (p == NULL), faz receber um
    else{ // caso ja tenha, percorre os irmaos do filho ate o ultimo
        while(p->proxIrmao != NULL)
            p = p->proxIrmao;
        p->proxIrmao = filho; // adiciona o filho na ultima posicao entre os irmao
    }
    return 1;
}

void exibir(PONT raiz){
    if(!raiz) return;
    printf("%d(", raiz->chave);
    PONT aux = raiz->primFilho;
    while (aux){
        exibir(aux);
        aux = aux->proxIrmao;
    }
    printf(")");
}


int main(){

    PONT r;

    inicializar(&r, 8);

    inserir(r, 12, 8);    
    inserir(r, 9, 8);
    inserir(r, 15, 9);

    exibir(r);

    return 0;
}