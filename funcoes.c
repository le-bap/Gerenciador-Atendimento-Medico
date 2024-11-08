#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#include "estruturas.h"

// funcao para criar a data
Data *criar_data(int dia, int mes, int ano){
    Data *data = malloc(sizeof(Data));
    data->dia = dia;
    data->mes = mes;
    data->ano = ano;
    return data;
}

// funcao para a criacao do registro, com todas as informações de nome, idade, tg e a data
Registro *criar_registro(char *nome, int idade, char *rg, Data *entrada){
    Registro *registro = malloc(sizeof(Registro));
    strcpy(registro->nome, nome);
    registro->idade = idade;
    strcpy(registro->rg, rg);
    registro->entrada = entrada;
    return registro;
}

// funcao para criar a elista
ELista *criar_elista(Registro *registro){
    ELista *elista = malloc(sizeof(ELista));
    elista->dados = registro;
    elista->proximo = NULL;
    return elista;
}

// funcao para criar a efila
Efila *criar_efila(Registro *registro){
    Efila *efila = malloc(sizeof(Efila));
    efila->dados = registro;
    efila->proximo = NULL;
    return efila;
}

// funcao para criar a lista
Lista *criar_lista(){
    Lista *lista = malloc(sizeof(Lista));
    lista->inicio = NULL;
    lista->qtd = 0;
    return lista;
}

// funcao para inicializar a fila
Fila *criar_fila(){
  Fila *fila = malloc(sizeof(Fila));
  fila->head = NULL; // valores iniciam como null para a fila 
  fila->tail = NULL; // o head e tail iniciam como NULL
  fila->qtd = 0;
  return fila;
}

// funcao para inicializar a pilha
Stack *criar_stack(){
  Stack *stack = malloc(sizeof(Stack));
  stack->qtde = 0;
  stack->topo = NULL;
  return stack;
}

// funcao para inicializar a arvore 
ABB *criar_ABB(){
    ABB* arvore = malloc(sizeof(ABB));
	arvore->raiz = NULL;
	arvore->qtde = 0;
	return arvore;
}

// funcao para criar a  EABB
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

    // insere o paciente nas arvores
    inserir_EABB_ano(abb_ano, novo_registro);
    inserir_EABB_mes(abb_mes, novo_registro);
    inserir_EABB_dia(abb_dia, novo_registro);
    inserir_EABB_idade(abb_idade, novo_registro);

}

// funcao para mostrar a lista de pacientes
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

// funcao para consultar algum paciente pelo rg
void consultar_paciente(Lista *lista){
    ELista *atual = lista->inicio;
    char procurado[20];
    printf("Digite o RG do paciente: ");
    scanf("%s", procurado);

    while(atual != NULL && strcmp(procurado, atual->dados->rg) != 0){ // percorremos a lista 
        atual = atual->proximo;
    }
    // atual vai guardar as informações do paciente buscado
    if (atual == NULL){
        printf("Paciente nao encontrado");
    }
    else { // mostra o paciente
        printf("\nNome: %s ", atual->dados->nome);
        printf("\nIdade: %d ", atual->dados->idade);
        printf("\nRG: %s ", atual->dados->rg);
        printf("\nData de entrada: %d / %d / %d \n", atual->dados->entrada->dia, 
        atual->dados->entrada->mes, atual->dados->entrada->ano);
    }
}

// funcao para atualizar dados de um paciente
void atualizar_dados(Lista *lista){
    ELista *atual = lista->inicio;
    char procurado[20];
    printf("Digite o RG do paciente: ");
    scanf("%s", procurado);

    while(atual != NULL && strcmp(procurado, atual->dados->rg) != 0){ //percorremos a lista
        atual = atual->proximo;
    }
    // atual vai guardar as informações do paciente buscado
    if (atual == NULL){
        printf("\nPaciente nao encontrado");
    }else{
        int escolha; // o usuario escolhe a informacao que deseja modificar
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
void remover_paciente(Lista *lista, ABB *abb_ano, ABB *abb_mes, ABB *abb_dia, ABB *abb_idade){
    if (lista->inicio == NULL) {
        printf("A lista está vazia. Não há pacientes para remover.\n");
        return;
    }

    char removido[20];
    printf("Digite o RG do paciente: ");
    scanf("%s", removido);

    ELista *atual = lista->inicio;
    ELista *anterior = NULL;

    while (atual != NULL && strcmp(removido, atual->dados->rg) != 0) { // percorremos a lista
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
    //free(atual->dados->entrada);
    //free(atual->dados);

    remover_no(abb_ano, atual->dados);
    remover_no(abb_mes, atual->dados);
    remover_no(abb_dia, atual->dados);
    remover_no(abb_idade, atual->dados);

    free(atual);

    printf("Paciente removido com sucesso!\n");
}

//item 2: Atendimento - fila

// Função para enfileirar um paciente
void enfileirar_paciente(Fila *fila, Lista *lista, Stack *stack) {
    char rg[20];
    printf("Digite o RG do paciente que deseja enfileirar: ");
    scanf("%s", rg);
    clearBuffer();
    
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

    // Enfileira o paciente
    if (fila->qtd == 0) {
        fila->head = novo;
        fila->tail = novo;
    } else {
        fila->tail->proximo = novo;
        fila->tail = novo;
    }
    fila->qtd++;
    printf("\nO paciente foi enfileirado!\n");

    Operacao nova_operacao = {1, registro}; // Cria a operação para desfazer
    push(stack, nova_operacao);
}

// Função para desenfileirar um paciente
void desenfileirar_paciente(Fila *fila, Stack *stack) {
    if (fila->qtd == 0) {
        printf("\nNão há paciente para desenfileirar!");
        return; 
    }

    Efila *remover = fila->head;
    fila->head = fila->head->proximo;

    if (fila->head == NULL) {
        fila->tail = NULL;
    }

    printf("\nPaciente removido da fila: %s\n", remover->dados->nome);

    Operacao nova_operacao = {2, remover->dados}; // Cria a operação para desfazer
    push(stack, nova_operacao);

    free(remover); // Libera apenas o nó, não o registro
    fila->qtd--;
}

// funcao de mostrar fila
void mostrar_fila(Fila *fila){
    if (fila->qtd == 0) {
        printf("A fila está vazia.\n");
        return;
    }

    Efila *atual = fila->head;
    printf("Pacientes na fila:\n");

    while (atual != NULL) { // percorre a fila e mostra os pacientes enfileirados
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

// funcao para a arvore por ano
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

// funcao de arvore por mes
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

// funcao de arvore ´pelo dia
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

// funcao de arvore pela idade
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

void remover_no(ABB *abb, Registro *registro) {
    EABB *vertice = abb->raiz;
    EABB *anterior = NULL;

    // Buscar o nó que contém os dados do 'registro' na árvore
    while (vertice != NULL) {
        // Comparar os registros para encontrar o nó correspondente
        if (registro->idade < vertice->dados->idade) {
            anterior = vertice;
            vertice = vertice->esq;
        } else if (registro->idade > vertice->dados->idade) {
            anterior = vertice;
            vertice = vertice->dir;
        } else {
            // Encontrou o nó correspondente, então sai do loop
            break;
        }
    }

    // Se o nó não for encontrado
    if (vertice == NULL) {
        printf("Registro não encontrado.\n");
        return;
    }

    // Agora que temos o nó a ser removido, vamos proceder com a remoção
    int num_filhos = 0;

    if (vertice->esq != NULL) num_filhos++;
    if (vertice->dir != NULL) num_filhos++;

    // Caso o nó não tenha filhos (nó folha)
    if (num_filhos == 0) {
        if (vertice == abb->raiz) {
            abb->raiz = NULL;  // Se for a raiz, a árvore fica vazia
        } else {
            // Se não for a raiz, remove o nó da árvore
            if (anterior->esq == vertice) {
                anterior->esq = NULL;
            } else {
                anterior->dir = NULL;
            }
        }
    }
    // Caso o nó tenha 1 filho
    else if (num_filhos == 1) {
        EABB *filho = (vertice->esq != NULL) ? vertice->esq : vertice->dir;
        if (vertice == abb->raiz) {
            abb->raiz = filho;  // Se for a raiz, o filho se torna a nova raiz
        } else {
            // Se não for a raiz, conecta o filho no lugar do nó removido
            if (anterior->esq == vertice) {
                anterior->esq = filho;
            } else {
                anterior->dir = filho;
            }
        }
    }
    // Caso o nó tenha 2 filhos
    else {
        // Encontrar o sucessor (o maior nó da subárvore esquerda)
        EABB *sucessor = vertice->esq;
        EABB *sucessor_pai = vertice;

        // Percorrer até o maior nó da subárvore esquerda
        while (sucessor->dir != NULL) {
            sucessor_pai = sucessor;
            sucessor = sucessor->dir;
        }

        // Copiar os dados do sucessor para o nó atual
        vertice->dados = sucessor->dados;

        // Se o sucessor não tem filho esquerdo, remove diretamente o sucessor
        if (sucessor->esq != NULL) {
            if (sucessor_pai->esq == sucessor) {
                sucessor_pai->esq = sucessor->esq;
            } else {
                sucessor_pai->dir = sucessor->esq;
            }
        } else {
            if (sucessor_pai->esq == sucessor) {
                sucessor_pai->esq = NULL;
            } else {
                sucessor_pai->dir = NULL;
            }
        }

        free(sucessor); // Libera o nó sucessor
    }

    abb->qtde--;  // Atualiza a quantidade de nós na árvore
    free(vertice); // Libera a memória do nó removido
}


// funcao de adicionar na pilha
void push(Stack *stack, Operacao operacao) {
    Celula *novo = malloc(sizeof(Celula));
    if (novo == NULL) {
        printf("Erro ao alocar memoria para a nova celula!\n");
        return;
    }
    // define a operacao que vai ser desfeita
    novo->operacao = operacao; 
    novo->anterior = stack->topo;
    novo->proximo = NULL;
    
    if (stack->qtde > 0) {
        stack->topo->proximo = novo;
    }
    
    stack->topo = novo;
    stack->qtde++;
}
// funcao para apagar da pilha
Operacao pop(Stack *stack) {
    Operacao operacao_vazia = {0, NULL}; 
    if (stack->qtde == 0) {
        return operacao_vazia;
    }

    // retorna a operacao desfeita
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

// funcao de desfazer
void desfazer(Stack *stack, Fila *fila) {
    if (stack->qtde == 0) {
        printf("Nenhuma operacao para desfazer!\n");
        return;
    }

    Operacao ultima_operacao = pop(stack);  // ve qual foi a ultima operacao e confirma com o usuario se ele dejesa desfazer
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
            //fila->tail->proximo = novo;
            //fila->tail = novo;
            novo->proximo = fila->head;
            fila->head = novo;
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