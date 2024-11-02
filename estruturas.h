#ifndef ESTRUTURAS_H  
#define ESTRUTURAS_H

// Forward declaration da estrutura ELista e Efila
typedef struct ELista ELista;
typedef struct Efila Efila;

typedef struct Data {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct Registro {
    char nome[50];
    int idade;
    char rg[20];
    Data *entrada;
} Registro;

// Definição da estrutura ELista
struct ELista {
    Registro *dados;
    ELista *proximo; // Aqui o tipo ELista já é conhecido devido ao forward declaration
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


#endif
