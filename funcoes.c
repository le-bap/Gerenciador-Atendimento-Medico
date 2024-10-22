#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#include "estruturas.h"

Data *criar_data(int dia, int mes, int ano){
    Data *data = malloc(sizeof(Data));
    data->dia = dia;
    data->mes = mes;
    data->ano = ano;
    return data;
}

Registro *criar_registro(char *nome, int idade, char *rg, Data *entrada){
    Registro *registro = malloc(sizeof(Registro));
    strcpy(registro->nome, nome);
    registro->idade = idade;
    strcpy(registro->rg, rg);
    registro->entrada = entrada;
    return registro;
}

// funções de cadastrar
ELista *criar_elista(Registro *registro){
    ELista *elista = malloc(sizeof(ELista));
    elista->dados = registro;
    elista->proximo = NULL;
    return elista;
}

Lista *criar_lista(){
    Lista *lista = malloc(sizeof(Lista));
    lista->inicio = NULL;
    lista->qtd = 0;
    return lista;
}

// cadastrar novo paciente
void cadastrar(Lista *lista) {
    char nome[50];
    int idade;
    char rg[20];
    int dia, mes, ano;

    printf("\nNome: ");
    scanf("%s", nome);
    clearBuffer();
    printf("Idade: ");
    scanf("%d", &idade);
    clearBuffer();
    printf("RG: ");
    scanf("%s", rg);
    clearBuffer();
    printf("Data de registro:\n");
    printf("Dia: ");
    scanf("%d", &dia);
    clearBuffer();
    printf("Mes: ");
    scanf("%d", &mes);
    clearBuffer();
    printf("Ano: ");
    scanf("%d", &ano);
    clearBuffer();

    // cria a data de início e o registro da pessoa
    Data *entrada = criar_data(dia, mes, ano);
    Registro *novo_registro = criar_registro(nome, idade, rg, entrada);
    ELista *novo_elemento = criar_elista(novo_registro);

    // insere no começo da fila
    novo_elemento->proximo = lista->inicio;
    lista->inicio = novo_elemento;
    lista->qtd++;
}

void mostrar_lista(Lista *lista){
    ELista *atual = lista->inicio;
    while (atual != NULL){
        printf("\nNome: %s ", atual->dados->nome);
        printf("\nIdade: %d ", atual->dados->idade);
        printf("\nRG: %s ", atual->dados->rg);
        printf("\nData de entrada: %d / %d / %d \n", atual->dados->entrada->dia, 
        atual->dados->entrada->mes, atual->dados->entrada->ano);
        atual = atual->proximo;
    }
    printf("\n");
}

void consultar_paciente(Lista *lista){
    ELista *atual = lista->inicio;
    char procurado[20];
    printf("Digite o RG do paciente: ");
    scanf("%s", procurado);

    while(atual != NULL && strcmp(procurado, atual->dados->rg) != 0){
        atual = atual->proximo;
    }
    // atual vai guardar as informações do paciente buscado
    if (atual == NULL){
        printf("Paciente nao encontrado");
    }
    else {
        printf("\nNome: %s ", atual->dados->nome);
        printf("\nIdade: %d ", atual->dados->idade);
        printf("\nRG: %s ", atual->dados->rg);
        printf("\nData de entrada: %d / %d / %d \n", atual->dados->entrada->dia, 
        atual->dados->entrada->mes, atual->dados->entrada->ano);
    }
}

void atualizar_dados(Lista *lista){
    ELista *atual = lista->inicio;
    char procurado[20];
    printf("Digite o RG do paciente: ");
    scanf("%s", procurado);

    while(atual != NULL && strcmp(procurado, atual->dados->rg) != 0){
        atual = atual->proximo;
    }
    // atual vai guardar as informações do paciente buscado
    if (atual == NULL){
        printf("\nPaciente nao encontrado");
    }else{
        int escolha;
        printf("\nEscolha a inforamacao que gostaria de atualizar:");
        printf("\n1 - Nome");
        printf("\n2 - Idade");
        printf("\n3 - RG");
        printf("\n4 - Data de entrada\n");
        scanf("%d", &escolha);
        clearBuffer();
        if (escolha == 1){
            char nome2[50];
            printf("Novo nome: ");
            scanf("%s", nome2);
            clearBuffer();
            strcpy(atual->dados->nome, nome2);
        } else if(escolha == 2){
            int idade2;
            printf("\nNova idade: ");
            scanf("%d", &idade2);
            clearBuffer();
            atual->dados->idade = idade2;
        } else if (escolha == 3){
            char rg2[20];
            printf("\nNovo RG: ");
            scanf("%s", rg2);
            clearBuffer();
            strcpy(atual->dados->rg, rg2);
        } else if (escolha == 4){
            int dia2, mes2, ano2;
            printf("Dia: ");
            scanf("%d", &dia2);
            clearBuffer();
            printf("Mes: ");
            scanf("%d", &mes2);
            clearBuffer();
            printf("Ano: ");
            scanf("%d", &ano2);
            clearBuffer();
            atual->dados->entrada->dia = dia2;
            atual->dados->entrada->mes = mes2;
            atual->dados->entrada->ano = ano2;
        }else{
            printf("Numero invalido.");
            return;
        }
        printf("Informacoes atualizadas com sucesso!\n");
    }
}

// funções auxiliares
void clearBuffer(){ 
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}