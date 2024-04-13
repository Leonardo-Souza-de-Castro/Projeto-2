#include <stdio.h>
#include <string.h>
#include "tarefas.h"

ERROS criar(Tarefa tarefas[], int *pos){
    if(*pos >= TOTAL)
        return MAX_TAREFA;

    printf("Entre com a prioridade: ");
    scanf("%d", &tarefas[*pos].prioridade);
    clearBuffer();
    printf("Entre com a categoria: ");
    fgets(tarefas[*pos].categoria, 100, stdin);

    printf("Entre com a descricao: ");
    fgets(tarefas[*pos].descricao, 300, stdin);

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

    int i = pos_deletar;
    for(i; i < *pos; i++){
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

    char filtro[100];

    clearBuffer();
    printf("Quais categorias voce gostaria de listar: ");
    fgets(filtro, 100, stdin);

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
    printf("Voce gostaria de salvar tarefas de alguma categoria especifica? (s/n)");
    char opcao[10];
    fgets(opcao, 10, stdin);
    if(strcmp(opcao, "s")){
        salvar_texto(tarefas, *pos, filtro);
    }
    else{
        printf("nn funciona");
    }

    return OK;
}

ERROS salvar(Tarefa tarefas[], int *pos){
    FILE *f = fopen("tarefas.bin", "wb");
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
ERROS salvar_texto(Tarefa tarefas[], int *pos, char filtro[100]){
    printf("Qual o nome do arquivo que você quer utilizar (Não inserir extenção do arquivo)");
    char nome_arquivo[300];
    fgets(nome_arquivo, 300, stdin);


    // FILE *f = fopen(strcat(nome_arquivo,".txt"), "w");
    FILE *f = fopen("teste.txt", "w");
    if(f == NULL)
        return ABRIR;

    // int qtd = fwrite(tarefas, TOTAL, sizeof(Tarefa), f);
    int qtd = 0;
    // fprintf(f, "teste");
    // if(qtd == 0)
    //     return ESCREVER;

    // qtd = fwrite(pos, 1, sizeof(int), f);
    // if(qtd == 0)
    //     return ESCREVER;

    // if(fclose(f))
    //     return FECHAR;
    int i = 0;
    for (i; i < *pos; i++)
    {
        if(strncmp(filtro, tarefas[*pos].categoria, 100)){
            fprintf(f, "Categoria: %s | Prioridade: %s | Descricao: %s", tarefas[*pos].categoria, tarefas[*pos].prioridade, tarefas[*pos].descricao);
        }
    }
    

    return OK;
}

ERROS carregar(Tarefa tarefas[], int *pos){
    FILE *f = fopen("tarefas.bin", "rb");
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
