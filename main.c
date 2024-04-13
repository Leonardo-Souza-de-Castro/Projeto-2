#include <stdio.h>
#include "tarefas.h"

int main(){
    funcao fs[] = {criar, deletar, listar, salvar, carregar};

    Tarefa tarefas[TOTAL];
    int pos;
    ERROS resultado;

    int opcao;
    do{
        printf("\nMenu principal\n");
        printf("1 - Criar tarefa\n");
        printf("2 - Deletar tarefa\n");
        printf("3 - Listar tarefas\n"); 
        printf("4 - Carregar tarefas\n"); 
        printf("5 - Salvar tarefas\n"); 
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        opcao--;
        if(opcao > 4)
            printf("Opcao invalida\n");
        else if(opcao >= 0)
            resultado = fs[opcao](tarefas, &pos);
            if(resultado != OK)
                switch(resultado){
                  case MAX_TAREFA:
                    printf("Erro: Máximo de tarefas atingido\n");
                  break;
                  case SEM_TAREFAS:
                    printf("Erro: Não existem tarefas cadastradas\n");
                  break;
                  case NAO_ENCONTRADO:
                    printf("Erro: Tarefa não encontrada\n");
                  break;
                  case ABRIR:
                    printf("Erro: Erro ao abrir arquivo\n");
                  break;
                  case FECHAR:
                    printf("Erro: Erro ao fechar arquivo\n");
                  break;
                  case LER:
                    printf("Erro: Erro ao ler arquivo\n");
                  break;
                  case ESCREVER:
                    printf("Erro: Erro ao escrever no arquivo\n");
                  break;
                }

    } while(opcao >= 0);
}
