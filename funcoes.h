#ifndef FUNCOES_H  
#define FUNCOES_H

#include "estruturas.h"

Data *criar_data(int dia, int mes, int ano);
Registro *criar_registro(char *nome, int idade, char *rg, Data *entrada);

;// Funções de cadastro
ELista *criar_elista(Registro *registro);
Lista *criar_lista();

void cadastrar(Lista *lista);
void consulta_paciente(Lista lista);
void mostrar_lista(Lista *lista);


void clearBuffer();
#endif