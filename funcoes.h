#ifndef FUNCOES_H  
#define FUNCOES_H

#include "estruturas.h"

Data *criar_data(int dia, int mes, int ano);
Registro *criar_registro(char *nome, int idade, char *rg, Data *entrada);

;// Funções de cadastro
ELista *criar_elista(Registro *registro);
Efila *criar_efila(Registro *registro);
Lista *criar_lista();
Fila *criar_fila();

// Item: Cadastrar
void cadastrar(Lista *lista);
void consultar_paciente(Lista *lista);
void mostrar_lista(Lista *lista);
void atualizar_dados(Lista *lista);
void remover_paciente(Lista *lista);

// Item: Atendimento 
void enfileirar_paciente(Fila *fila, Lista *lista,  Stack *stack);
void desenfileirar_paciente(Fila *fila,  Stack *stack);
void mostrar_fila(Fila *fila);

//funcoes de desfazer
Celula *criar_celula(Operacao operacao);
Stack *criar_stack();
void push(Stack *stack, Operacao operacao);
Operacao pop(Stack *pilha);
void desfazer(Stack *stack, Fila *fila);

int salvar_lista(Lista *lista, const char *nome_arquivo);
int carregar_lista(Lista *lista, const char *nome_arquivo);

//item sobre:
void sobre();

void clearBuffer();
#endif