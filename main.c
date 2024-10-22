#include <stdio.h>
#include <stdlib.h>
#include "estruturas.h"
#include "funcoes.h"


int main(void) {
	
    
    Lista *lista = criar_lista();

    // menu
    int op;
    int op2;    
    printf("1 - Cadastrar\n");
    printf("2 - Atendimentos\n");
    printf("3 - Pesquisa\n");
    printf("4 - Desfazer\n");
    printf("5 - Carregar/Salvar\n");
    printf("6 - Sobre\n");

    scanf("%d", &op);
    clearBuffer();

    while(op != 0){
        if (op == 1){
            printf("\n1 - Cadastrar novo paciente\n");
            printf("2 - Consulta paciente cadastrado\n");
            printf("3 - Mostrar lista completa\n");
            printf("4 - Atualizar dados do paciente\n");
            printf("5 - Remover paciente\n"); 
            printf("0 - Sair\n"); 
            scanf("%d", &op2); 
            clearBuffer();
            if (op2 == 1){
                cadastrar(lista);
            }
            else if (op2 == 3){
                mostrar_lista(lista);
            }
        }

        else if (op == 2){
            printf("\n1 - Enfileirar paciente\n");
            printf("2 - Desenfileirar paciente\n");
            printf("3 - Mostrar fila\n"); 
            scanf("%d", &op2);
            clearBuffer();  
        }

        else if (op == 3){
            printf("\n1 - Mostrar registros ordenados por ano\n");
            printf("2 - Mostrar registros ordenados por mês\n");
            printf("3 - Mostrar registros ordenados por dia\n");   
            printf("4 - Mostrar registros ordenados por idade do paciente\n");
            scanf("%d", &op2);
            clearBuffer();
        }

        else if (op == 4){
            // chamar a função desfazer
        }
        
        else if (op == 5){
            printf("\n1 - Ler um arquivo com os dados dos pacientes e carregar a lista\n");
            printf("2 - Salvar um arquivo com os dados dos pacientes\n"); 
            scanf("%d", &op2); 
            clearBuffer();
        }
        else if(op == 6){
            // chamar a função sobre()
            /*Nome do aluno;
            ▶ Ciclo;
            ▶ Curso;
            ▶ Disciplina;
            ▶ Data.
            */
        }
        else if (op == 0){
            break;
        }
        else{
            printf("\nDigite um numero valido\n");
        }
    }
    return 0;
}
