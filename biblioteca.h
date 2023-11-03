//
// Created by edson on 19/09/2023.
//

#ifndef UNTITLED1_BIBLIOTECA_H
#define UNTITLED1_BIBLIOTECA_H

typedef struct { //struct que onde as tarefas estão armazenadas
    int prioridade;
    char categoria[100];
    char descricao[300];
} Tarefa;


typedef struct { // struct que armazena a quantidade de tarefas
    Tarefa tarefas[100];
    int qtd;
} ListaDeTarefas; // o máximo de tarefas possiveis são 100

// Funções para o código de tarefas


int cadastrarTarefa(ListaDeTarefas *lt);
int deletarTarefa(ListaDeTarefas *lt);
int listarTarefas(ListaDeTarefas *lt);
void printMenu();
int salvarTarefas(ListaDeTarefas *lt, char *arquivo);
int carregarTarefas(ListaDeTarefas *lt, char *arquivo);
void alterarTarefas(ListaDeTarefas *lt);
void filtrarTarefasPrioridade(ListaDeTarefas lt);
void filtrarTarefasEstado();
void filtrarPrioridadeCategoria();
void exportarTarefasPrioridade();
void exportarTarefasCategoria();
void exportarTarefasPrioridadeCategoria();


#endif //UNTITLED1_BIBLIOTECA_H
