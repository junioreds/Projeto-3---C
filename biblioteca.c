#include <stdio.h>
#include "biblioteca.h"

int cadastrarTarefa(ListaDeTarefas *lt){ //função que é usada para cadastrar uma nova tarefa para o usuario
    printf("Digite a prioridade da tarefa (0 a 10): "); // define a prioridade da tarefa
    scanf("%d", &lt->tarefas[lt->qtd].prioridade); // define a entrada de dados da prioridade da tarefa e salva na struct
    getchar(); // Limpa o buffer de entrada
    printf("Descreva a tarefa: \n"); // define o que seria a tarefa
    fgets(lt->tarefas[lt->qtd].descricao, 300, stdin);
    lt->tarefas[lt->qtd].descricao[strcspn(lt->tarefas[lt->qtd].descricao, "\n")] = '\0'; // Remove a quebra de linha do final
    printf("Categorize a tarefa (menos importante a muito importante): "); // define o grau de importância da tarefa
    fgets(lt->tarefas[lt->qtd].categoria, 100, stdin);
    lt->tarefas[lt->qtd].categoria[strcspn(lt->tarefas[lt->qtd].categoria, "\n")] = '\0'; // Remove a quebra de linha do final
    lt->qtd++;
    printf("\n");
    return 0;
}

int deletarTarefa(ListaDeTarefas *lt){
    if (lt->qtd == 0) { // se o número de tarefas for zero
        printf("Nenhuma tarefa cadastrada.\n"); // aparece a mensagem de nenhuma tarefa cadastrada
        return 0;
    }

    printf("Escolha o numero da tarefa que deseja deletar (1 a %d): ", lt->qtd); //puxa as tarefas salvas em na struct
    int numeroTarefa;                                                                  // contabiliza o numero de tarefas
    scanf("%d", &numeroTarefa);                                                 // e da a opcao para o usuario de qual tarefa apagar

    if (numeroTarefa < 1 || numeroTarefa > lt->qtd) { // se o usuario digitar um número menor do que 1
        printf("Numero de tarefa invalido.\n");// retorna o print de numero invalido
        return 0;
    }

    // Remove a tarefa escolhida movendo as tarefas restantes uma posição para frente
    for (int i = numeroTarefa - 1; i < lt->qtd - 1; i++) {
        lt->tarefas[i] = lt->tarefas[i + 1];
    }

    lt->qtd--;
    printf("Tarefa deletada com sucesso.\n");

    return 0;
}

int listarTarefas(ListaDeTarefas lt){ // lsita o número de tarefas feitas pelo usuario
    if (lt.qtd == 0) {                // se o numero de tarefas for 0 retorna o print
        printf("Nenhum tarefa cadastrada\n");
        return 0;
    }

    for (int  i = 0; i < lt.qtd; i++) { // Pega a posição das tarefas e lista elas como "tarefa1", "tarefa2"...
        printf("Tarefa %d: \n", i+1);
        printf("Prioridade: %d\n", lt.tarefas[i].prioridade);
        printf("Descricao: %s\n", lt.tarefas[i].descricao);
        printf("Categoria: %s\n", lt.tarefas[i].categoria);
    }
    return 0;
}

void printMenu(){ // função usada para listar as opções do nosso código para o usuario
    printf("/// Bem vindo ao nosso codigo de listar tarefas, olhe as opcoes /// \n");
    printf("Opcao 1: Cadastrar nova tarefa\n"); // se opcao for 1,  cadastra uma nova tarefa
    printf("Opcao 2: Listar tarefa\n"); // se opcao for 2, lista as tarefas
    printf("Opcao 3: Deletar tarefa\n"); // se opcao for 3, deleta a tarefa selecionada pelo usuario
    printf("Opcao 4: Salvar tarefas\n"); // se opcao for 4, salva as tarefas em um arquivo txt
    printf("Opcao 5: Carregar tarefa\n"); // se opcao for 5, carrega as tarefas em um arquivo txt
    printf("Opcao 0: Sair do codigo.\n"); // Termina o laço de repetição do código
    printf("Qual opcao voce deseja: "); // input do usuario de qual opcao ele deseja
}

int salvarTarefas(ListaDeTarefas *lt, char *arquivo){ // salva as tarefas feitas em um arquivo txt
    FILE *arquivoTarefas = fopen(arquivo, "w");

    if (arquivoTarefas == NULL) {
        printf("Erro ao salvar tarefa"); // se o arquivo estiver vazio, retorna um erro ao salvar a tarefa

        return 1;
    }

    for (int i = 0; i <lt -> qtd; i++) { //puxa a posição das tarefas dentro da struct e salva em arquivo
        fprintf(arquivoTarefas, "%d\n", lt->tarefas[i].prioridade);
        fprintf(arquivoTarefas, "%d\n", lt->tarefas[i].descricao);
        fprintf(arquivoTarefas, "%d\n", lt->tarefas[i].categoria);
    }

    fclose(arquivoTarefas);
    printf("As tarefas foram salvas\n");

    return 0;
}

int carregarTarefas(ListaDeTarefas *lt, char *arquivo){ // carrega as tarefas feitas em um arquivo txt
    FILE *arquivoTarefas = fopen(arquivo, "r");

    if (arquivoTarefas == NULL) {  // se o arquivo estiver vazio, retorna um erro ao carregar a tarefa
        printf("Erro ao carregar arquivo");
        return 1;
    }

    while (!feof(arquivoTarefas) && lt -> qtd < 100) { // define que enquanto o arquivoTarefas for < 100
        fscanf(arquivoTarefas, "%d", &lt->tarefas[lt->qtd].prioridade);
        fgetc(arquivoTarefas);                         // percorre cada armazenamento da da struct e carrega as tarefas
        fgets(lt->tarefas[lt->qtd].descricao, 300, arquivoTarefas);
        lt->tarefas[lt->qtd].descricao[strcspn(lt->tarefas[lt->qtd].descricao, "\n")] = '\0';
        fgets(lt->tarefas[lt->qtd].categoria, 100, arquivoTarefas);
        lt->tarefas[lt->qtd].categoria[strcspn(lt->tarefas[lt->qtd].categoria, "\n")] = '\0';
    }

    fclose(arquivoTarefas);
    printf("Tarefas carregadas com sucesso");

    return 1;
}
