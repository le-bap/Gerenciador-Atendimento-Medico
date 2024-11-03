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

ELista *criar_elista(Registro *registro){
    ELista *elista = malloc(sizeof(ELista));
    elista->dados = registro;
    elista->proximo = NULL;
    return elista;
}

Efila *criar_efila(Registro *registro){
    Efila *efila = malloc(sizeof(Efila));
    efila->dados = registro;
    efila->proximo = NULL;
    return efila;
}

Lista *criar_lista(){
    Lista *lista = malloc(sizeof(Lista));
    lista->inicio = NULL;
    lista->qtd = 0;
    return lista;
}

Fila *criar_fila(){
  Fila *fila = malloc(sizeof(Fila));
  fila->head = NULL;
  fila->tail = NULL;
  fila->qtd = 0;
  return fila;
}

Stack *criar_stack(){
  Stack *stack = malloc(sizeof(Stack));
  stack->qtde = 0;
  stack->topo = NULL;
  return stack;
}

ABB *criar_ABB(){
    ABB* arvore = malloc(sizeof(ABB));
	arvore->raiz = NULL;
	arvore->qtde = 0;
	return arvore;
}

EABB *criar_EABB(Registro *registro){
    EABB *novo = malloc(sizeof(EABB));
    novo->dir = NULL;
    novo->esq = NULL;
    novo->dados = registro;
    return novo;
}

//item 1 do menu
// cadastrar novo paciente
void *cadastrar(Lista *lista, ABB *abb_ano, ABB *abb_mes, ABB *abb_dia, ABB *abb_idade) {
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

    inserir_EABB_ano(abb_ano, novo_registro);
    inserir_EABB_mes(abb_mes, novo_registro);
    inserir_EABB_dia(abb_dia, novo_registro);
    inserir_EABB_idade(abb_idade, novo_registro);

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

// funcao de remover paciente pelo RG
void remover_paciente(Lista *lista){
    if (lista->inicio == NULL) {
        printf("A lista está vazia. Não há pacientes para remover.\n");
        return;
    }

    char removido[20];
    printf("Digite o RG do paciente: ");
    scanf("%s", removido);

    ELista *atual = lista->inicio;
    ELista *anterior = NULL;

    while (atual != NULL && strcmp(removido, atual->dados->rg) != 0) {
        anterior = atual;  
        atual = atual->proximo;
    }

    // Se nao houver pacientes com esse RG
    if (atual == NULL) {
        printf("Paciente não encontrado.\n");
        return;
    }

    // Caso o paciente esteja no início da lista
    if (atual == lista->inicio) {
        lista->inicio = atual->proximo; 
    } else {
        // Remove de qualquer lugar da lista
        anterior->proximo = atual->proximo;
    }

    lista->qtd--;  
    // Libera a memória
    free(atual->dados->entrada);
    free(atual->dados);
    free(atual);

    printf("Paciente removido com sucesso!\n");
}

//item 2: Atendimento - fila

void enfileirar_paciente(Fila *fila, Lista *lista,  Stack *stack) {
    char rg[20];
    printf("Digite o RG do paciente que deseja enfileirar: ");
    scanf("%s", rg);
    clearBuffer();
    
    // Busca o paciente na lista
    ELista *atual = lista->inicio;
    Registro *registro = NULL;
    while (atual != NULL && strcmp(atual->dados->rg, rg) != 0) {
        atual = atual->proximo;
    }
    

    if (atual != NULL) {
        registro = atual->dados;  // Paciente encontrado
    } else {
        printf("Paciente não encontrado!\n");
        return;
    }
    
    Efila *novo = malloc(sizeof(Efila));
    if (novo == NULL) {
        printf("Erro ao alocar memória!\n");
        return;
    }

    novo->dados = registro;
    novo->proximo = NULL;

    // Enfileirar o paciente
    if (fila->qtd == 0) {
        fila->head = novo;
        fila->tail = novo;
    } else {
        fila->tail->proximo = novo;
        fila->tail = novo;
    }

    fila->qtd++;
    printf("\nO paciente foi enfileirado!\n");

    Operacao nova_operacao = {1, registro};
    push(stack, nova_operacao);
}


void desenfileirar_paciente(Fila *fila,  Stack *stack) {
    if (fila->qtd == 0) {
        printf("\nNão há paciente para desenfileirar!");
        return; 
    }

    // O paciente a ser removido é o primeiro da fila
    Efila *remover = fila->head;
    fila->head = fila->head->proximo; 

    // Se a fila agora estiver vazia, atualiza o tail 
    if (fila->head == NULL) {
        fila->tail = NULL;
    }
    
    printf("\nPaciente removido da fila: %s\n", remover->dados->nome);

    Operacao nova_operacao = {2, remover->dados};
    push(stack, nova_operacao);

    free(remover->dados->entrada); 
    free(remover->dados); 
    free(remover); 
    fila->qtd--; 
}


void mostrar_fila(Fila *fila){
    if (fila->qtd == 0) {
        printf("A fila está vazia.\n");
        return;
    }

    Efila *atual = fila->head;
    printf("Pacientes na fila:\n");

    while (atual != NULL) {
        printf("\nNome: %s", atual->dados->nome);
        printf("\nIdade: %d", atual->dados->idade);
        printf("\nRG: %s", atual->dados->rg);
        printf("\nData de entrada: %d/%d/%d\n", 
            atual->dados->entrada->dia, 
            atual->dados->entrada->mes, 
            atual->dados->entrada->ano);
        
        atual = atual->proximo; 
    }
}


// item 3: arvore binaria de busca
void in_ordem(EABB *raiz) {
    if (raiz == NULL){return;}
    in_ordem(raiz->esq);
    printf("\nNome: %s", raiz->dados->nome);
    printf("\nIdade: %d", raiz->dados->idade);
    printf("\nRG: %s", raiz->dados->rg);
    printf("\nData de entrada:  %d/%d/%d\n", raiz->dados->entrada->dia,
        raiz->dados->entrada->mes, raiz->dados->entrada->ano);
    in_ordem(raiz->dir);
}

void inserir_EABB_ano(ABB *abb, Registro *registro){
	EABB *novo = criar_EABB(registro);
	
    if (abb->qtde == 0){
        abb->raiz = novo;
    }
    else{
        EABB *atual = abb->raiz;
        EABB *anterior = NULL;
        while(atual != NULL){
            anterior = atual;
            if (registro->entrada->ano < atual->dados->entrada->ano){ // quando valor for menor q atual, vai pra esq
                atual = atual->esq;
            }
            else { // se for maior, vai pra direita
                atual = atual->dir;
            }
            
        }
        // insere no anterior
        if (registro->entrada->ano > anterior->dados->entrada->ano){
            anterior->dir = novo;
        } else{
            anterior->esq = novo;
        }
    }
    abb->qtde++;
} 
void inserir_EABB_mes(ABB *abb, Registro *registro){
	EABB *novo = criar_EABB(registro);
    if (abb->qtde == 0){
        abb->raiz = novo;
    }
    else{
        EABB *atual = abb->raiz;
        EABB *anterior = NULL;
        while(atual != NULL){
            anterior = atual;
            if (registro->entrada->mes < atual->dados->entrada->mes){ // quando valor for menor q atual, vai pra esq
                atual = atual->esq;
            }
            else { // se for maior, vai pra direita
                atual = atual->dir;
            }
            
        }
        // insere no anterior
        if (registro->entrada->mes > anterior->dados->entrada->mes){
            anterior->dir = novo;
        } else{
            anterior->esq = novo;
        }
    }
    abb->qtde++;
} 
void inserir_EABB_dia(ABB *abb, Registro *registro){
	EABB *novo = criar_EABB(registro);
    if (abb->qtde == 0){
        abb->raiz = novo;
    }
    else{
        EABB *atual = abb->raiz;
        EABB *anterior = NULL;
        while(atual != NULL){
            anterior = atual;
            if (registro->entrada->dia < atual->dados->entrada->dia){ // quando valor for menor q atual, vai pra esq
                atual = atual->esq;
            }
            else { // se for maior, vai pra direita
                atual = atual->dir;
            }
            
        }
        // insere no anterior
        if (registro->entrada->dia > anterior->dados->entrada->dia){
            anterior->dir = novo;
        } else{
            anterior->esq = novo;
        }
    }
    abb->qtde++;
} 
void inserir_EABB_idade(ABB *abb, Registro *registro){
	EABB *novo = criar_EABB(registro);
    if (abb->qtde == 0){
        abb->raiz = novo;
    }
    else{
        EABB *atual = abb->raiz;
        EABB *anterior = NULL;
        while(atual != NULL){
            anterior = atual;
            if (registro->idade < atual->dados->idade){ // quando valor for menor q atual, vai pra esq
                atual = atual->esq;
            }
            else { // se for maior, vai pra direita
                atual = atual->dir;
            }
            
        }
        // insere no anterior
        if (registro->idade > anterior->dados->idade){
            anterior->dir = novo;
        } else{
            anterior->esq = novo;
        }
    }
    abb->qtde++;
} 

//item 4: desfazer
Celula *criar_celula(Operacao operacao){
  Celula *celula = malloc(sizeof(Celula));
  celula->anterior = NULL;
  celula->proximo = NULL;
  celula->operacao = operacao;
  return celula;
}

void push(Stack *stack, Operacao operacao) {
    Celula *novo = malloc(sizeof(Celula));
    if (novo == NULL) {
        printf("Erro ao alocar memoria para a nova celula!\n");
        return;
    }
    
    novo->operacao = operacao; 
    novo->anterior = stack->topo;
    novo->proximo = NULL;
    
    if (stack->qtde > 0) {
        stack->topo->proximo = novo;
    }
    
    stack->topo = novo;
    stack->qtde++;
}

Operacao pop(Stack *stack) {
    Operacao operacao_vazia = {0, NULL}; 
    if (stack->qtde == 0) {
        return operacao_vazia;
    }

    Operacao operacao = stack->topo->operacao;
    Celula *temp = stack->topo;
    stack->topo = stack->topo->anterior;
    if (stack->qtde > 1) {
        stack->topo->proximo = NULL;
    }

    free(temp);
    stack->qtde--;
    return operacao;
}


void desfazer(Stack *stack, Fila *fila) {
    if (stack->qtde == 0) {
        printf("Nenhuma operacao para desfazer!\n");
        return;
    }

    Operacao ultima_operacao = pop(stack);  
    printf("Deseja desfazer a ultima operação realizada? (1 --> Sim, 0 --> Nao): ");
    int confirmacao;
    scanf("%d", &confirmacao);

    if (confirmacao != 1) {
        printf("Operacao de desfazer cancelada.\n");
        return;
    }

    pop(stack);  

    if (ultima_operacao.tipo_operacao == 1) {
        // desfazer um enfileiramento
        Efila *atual = fila->head, *anterior = NULL;
        while (atual != NULL && atual->dados != ultima_operacao.registro) {
            anterior = atual;
            atual = atual->proximo;
        }
        if (atual == NULL){
            return;
        }

        // Remove o paciente da fila
        if (anterior == NULL) {
            fila->head = atual->proximo;
        }else {
            anterior->proximo = atual->proximo;
            if (fila->tail == atual) {
                fila->tail = anterior;
            }
        }

        free(atual);
        fila->qtd--;

        printf("Operacao desfeita.\n");
    }
    else if (ultima_operacao.tipo_operacao == 2) {
        // Desfazer um desenfileiramento
        Efila *novo = criar_efila(ultima_operacao.registro);
        if (fila->qtd == 0) {
            fila->head = novo;
            fila->tail = novo;
        } else {
            fila->tail->proximo = novo;
            fila->tail = novo;
        }
        fila->qtd++;

        printf("Operacao desfeita.\n");
    }
}


//item 5: salvar e carregar na lista

int salvar_lista(Lista *lista, const char *nome_arquivo) {
    FILE *f = fopen(nome_arquivo, "wb"); 
    if (f == NULL) {
        printf("Erro ao abrir o arquivo para salvar.\n");
        return 1;
    }
    
    fwrite(&lista->qtd, sizeof(int), 1, f);
    ELista *atual = lista->inicio;
    while (atual != NULL) {
        fwrite(atual->dados, sizeof(Registro), 1, f);         
        fwrite(atual->dados->entrada, sizeof(Data), 1, f);      
        atual = atual->proximo;
    }

    fclose(f);
    printf("Lista salva com sucesso!\n");
    return 0;
}

int carregar_lista(Lista *lista, const char *nome_arquivo, ABB *abb_ano, ABB *abb_mes,  ABB *abb_dia, ABB *abb_idade) {
    FILE *f = fopen(nome_arquivo, "rb"); 
    if (f == NULL) {
        printf("Arquivo não encontrado.\n");
        return 1;
    }
    
    fread(&lista->qtd, sizeof(int), 1, f);
    lista->inicio = NULL;

    for (int i = 0; i < lista->qtd; i++) {
        Registro *registro = malloc(sizeof(Registro));
        Data *data = malloc(sizeof(Data));

        fread(registro, sizeof(Registro), 1, f);  
        fread(data, sizeof(Data), 1, f);          
        registro->entrada = data;
        
        ELista *novo = criar_elista(registro);
        inserir_EABB_ano(abb_ano, registro);
        inserir_EABB_mes(abb_mes, registro);
        inserir_EABB_dia(abb_dia, registro);
        inserir_EABB_idade(abb_idade, registro);
        novo->proximo = lista->inicio;
        lista->inicio = novo;
    }

    fclose(f);
    printf("Lista carregada com sucesso!\n");
    return 0;
}

// item 6 do menu
void sobre(){
    printf("Aluna: Rafaela Altheman de Campos - R.A: 24.123.010-1\n");
    printf("Aluna: Letizia Lowatzki Baptistella - R.A: 24.123.031-7\n");
    printf("Ciclo: 4o Semestre\n");
    printf("Curso: Ciencia da Computacao\n");
    printf("Disciplina: Estrutura de dados (CC4652) Professor: Luciano Rossi\n");
    printf("Data de entrega: 08/11/2024\n");
}


// funções auxiliares
void clearBuffer(){ 
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}