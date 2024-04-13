#include <stdio.h>
#include <string.h>
#include "tarefas.h"

ERROS criar(Tarefa tarefas[], int *pos){
    if(*pos >= TOTAL)
        return MAX_TAREFA;

    int prioridade;
    do {
        printf("Entre com a prioridade: ");
        scanf("%d", &prioridade);
        if ((prioridade > 0) && (prioridade < 11)){
            tarefas[*pos].prioridade = prioridade;
        }   
        else{
            printf("Numero de prioridade nao cabivel!\n");
        }
        
        }while(prioridade < 1 || prioridade > 10);

    clearBuffer();
    printf("Entre com a categoria: ");

    fgets(tarefas[*pos].categoria, 100, stdin);
    printf("Entre com a descricao: ");
    fgets(tarefas[*pos].descricao, 300, stdin);

    tarefas[*pos].categoria[strcspn(tarefas[*pos].categoria, "\n")] = 0; //Essa função localiza dentro de tarefas.categoria a primeira vez que \n aparece e o substitui por \0
    tarefas[*pos].descricao[strcspn(tarefas[*pos].descricao, "\n")] = 0; //Essa função localiza dentro de tarefas.categoria a primeira vez que \n aparece e o substitui por \0

    *pos = *pos + 1;

    return OK;
}

ERROS deletar(Tarefa tarefas[], int *pos){
    // teste se existem tarefas
    if(*pos == 0)
        return SEM_TAREFAS;

    // verifica se a tarefa escolhida existe
    int pos_deletar;
    printf("Entre com a posicao da tarefa a ser deletada: ");
    scanf("%d", &pos_deletar);
    pos_deletar--; // garantir posicao certa no array
    if(pos_deletar >= *pos || pos_deletar < 0)
        return NAO_ENCONTRADO;
  
    int i = 0;
    for(i = pos_deletar; i < *pos; i++){
        tarefas[i].prioridade = tarefas[i+1].prioridade;
        strcpy(tarefas[i].categoria, tarefas[i+1].categoria);
        strcpy(tarefas[i].descricao,  tarefas[i+1].descricao);
    }

    *pos = *pos - 1;

    return OK;
}

ERROS listar(Tarefa tarefas[], int *pos){
    if(*pos == 0)
        return SEM_TAREFAS;
    printf("Quais categorias voce gostaria de listar: ");
    char filtro[100];
    clearBuffer();
    fgets(filtro, 100, stdin);
    int count = 0;
  
    if (strlen(filtro) == 1){
        int i=0;
        for(i; i<*pos; i++){
            printf("Pos: %d\t", i+1);
            printf("Prioridade: %d\t", tarefas[i].prioridade);
            printf("Categoria: %s\t", tarefas[i].categoria);
            printf("Descricao: %s\n", tarefas[i].descricao);
        }
    }
    else{
        int i = 0;
        for (i; i < *pos; i++)
        {
            if(strncmp(filtro, tarefas[i].categoria, 100) == 0){
                printf("Categoria: %s | Prioridade: %d | Descricao: %s \n", tarefas[i].categoria, tarefas[i].prioridade, tarefas[i].descricao);
            }
        }
    }

    int i = 0;
    for(i=0; i<*pos; i++){
        printf("Pos: %d\t", i+1);
        printf("Prioridade: %d\t", tarefas[i].prioridade);
        printf("Categoria: %s\t", tarefas[i].categoria);
        printf("Descricao: %s\n", tarefas[i].descricao);
    }

    return OK;
}

ERROS salvar(Tarefa tarefas[], int *pos){
    printf("Qual o nome do arquivo que você quer salvar? (adicione .bin ao final do nome) ");
      char nome[150];
  clearBuffer();
  fgets(nome, 150, stdin);
  
    FILE *f = fopen(nome, "wb+");
    if(f == NULL)
        return ABRIR;

    int qtd = fwrite(tarefas, TOTAL, sizeof(Tarefa), f);
    if(qtd == 0)
        return ESCREVER;

    qtd = fwrite(pos, 1, sizeof(int), f);
    if(qtd == 0)
        return ESCREVER;

    if(fclose(f))
        return FECHAR;

    return OK;
}

ERROS carregar(Tarefa tarefas[], int *pos){
    printf("Qual o nome do arquivo que você quer salvar? (adicione .bin ao final do nome) ");
    char nome[150];
  clearBuffer();
    fgets(nome, 150, stdin);

    FILE *f = fopen(nome, "rb+");
    if(f == NULL)
        return ABRIR;

    int qtd = fread(tarefas, TOTAL, sizeof(Tarefa), f);
    if(qtd == 0)
        return LER;

    qtd = fread(pos, 1, sizeof(int), f);
    if(qtd == 0)
        return LER;

    if(fclose(f))
        return FECHAR;

    return OK;

}

void clearBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
} 
