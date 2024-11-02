#ifndef ESTRUTURAS_H  
#define ESTRUTURAS_H

typedef struct Data {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct ELista ELista;
typedef struct Efila Efila;
typedef struct Registro {
    char nome[50];
    int idade;
    char rg[20];
    Data *entrada;
} Registro;

struct ELista {
    Registro *dados;
    ELista *proximo; 
};

typedef struct Lista {
    ELista *inicio;
    int qtd;
} Lista;

typedef struct Fila{
   Efila *head;
   Efila *tail;
  int qtd;
} Fila;

struct Efila{
    Registro *dados;
    Efila *proximo;
};

typedef struct {
    int tipo_operacao;      
    Registro *registro;     
} Operacao;

typedef struct Celula {
    Operacao operacao;         
    struct Celula *anterior;
    struct Celula *proximo;
} Celula;

typedef struct Stack {
    Celula *topo;
    int qtde;
} Stack;

typedef struct EABB{
	Registro *dados;
	struct EABB* esq;
	struct EABB* dir;
} EABB;

typedef struct ABB{
	EABB* raiz;
	int qtde;
} ABB;

#endif
