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

void exibirArvoreOrdemW(PONT raiz){
    if (raiz == NULL) return;
    exibirArvoreOrdemW(raiz->esq);
    exibirArvoreOrdemW(raiz->dir);
    printf("%i ",raiz->chave);
}

int max(int a, int b){
  if(a > b) return a;
  return b;
}

int funcaoZZZ(PONT raiz){
    if (!raiz ) return -1;
    return 1 + max(funcaoZZZ(raiz->esq), funcaoZZZ(raiz->dir));
}

int funcaoX(PONT raiz){
    if (!raiz ) return 0;
    return 1 + funcaoX(raiz->esq) + funcaoX(raiz->dir);
}

int main(){

    PONT r;

    criarRaiz(&r, 1);
    inserirFilho(r, 2, 1, direito);
    inserirFilho(r, 3, 1, esquerdo);
    
    printf("FuncaoZZZ (1a exec): %d\n", funcaoZZZ(r));
    printf("FuncaoX (1a exec): %d\n", funcaoX(r));
    printf("Imprimindo (1a exec):");
    exibirArvoreOrdemW(r);

    inserirFilho(r, 4, 2, esquerdo);
    inserirFilho(r, 5, 2, direito);
    inserirFilho(r, 6, 2, esquerdo);
    inserirFilho(r, 7, 6, direito);
    
    printf("FuncaoZZZ (2a exec): %d\n", funcaoZZZ(r));
    printf("FuncaoX (2a exec): %d\n", funcaoX(r));
    printf("Imprimindo (2a exec):");
    exibirArvoreOrdemW(r);

    

    return 0;
}