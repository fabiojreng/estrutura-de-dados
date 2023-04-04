#include <stdio.h>
#include <malloc.h>

typedef int TIPOCHAVE;

typedef struct {
	TIPOCHAVE chave;
} REGISTRO;

typedef struct aux {
	REGISTRO reg;
struct aux* prox;
} ELEMENTO, *PONT;

typedef struct {
	PONT inicio;
	PONT fim;
} FILA;

void inicializarFila(FILA* fila){
	fila->fim = NULL;
	fila->inicio = NULL;
}

int tamanho(FILA* fila){
	PONT end = fila->inicio;
	int tam = 0;
	while(end != NULL){
		tam++;
		end = end->prox;
	}
	return tam;
}

void imprimirFila(FILA* fila){
	PONT end = fila->inicio;
	printf("Fila: \" ");
	while(end != NULL){
		printf("%d ", end->reg.chave);
		end = end->prox;
	}
	printf(" \"\n");
}

int inserirNaFila(FILA* fila, REGISTRO reg){
	PONT novo = (PONT)malloc(sizeof(ELEMENTO));
	novo->reg = reg;
	novo->prox = NULL;
	if(fila->fim == NULL)
		fila->inicio = novo;
	else
		fila->fim->prox = novo;
	fila->fim = novo;
	return 1;
}

int excluirDaFila(FILA* fila, REGISTRO* reg) {
	if (fila->inicio==NULL) 
		return 0;
	*reg = fila->inicio->reg;
	PONT apagar = fila->inicio;
	fila->inicio = fila->inicio->prox;
	free(apagar);
	if (fila->inicio == NULL) 
		fila->fim = NULL;
	return 1;
}

void reinicializarFila(FILA* fila){
	PONT end = fila->inicio;
	while(end != NULL){
		PONT apagar = end;
		end = end->prox;
		free(apagar);
	}
	fila->fim = NULL;
	fila->inicio = NULL;
}


int main(){
	
	FILA fila;
	REGISTRO reg;
	
	inicializarFila(&fila);
	
	// inserindo elementos
	reg.chave = 5;
	inserirNaFila(&fila, reg);
	reg.chave = 9;
	inserirNaFila(&fila, reg);
	reg.chave = 3;
	inserirNaFila(&fila, reg);
	
	// imprimir
	imprimirFila(&fila);
	
	// excluir elemento
	reg.chave = 1;
	excluirDaFila(&fila, &reg);
	
	imprimirFila(&fila);
	
	reinicializarFila(&fila);
	
	imprimirFila(&fila);
	
	return 0;
}
