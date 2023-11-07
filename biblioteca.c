#include <stdio.h>
#include "biblioteca.h"

void printMenu(){ // função usada para listar as opções do nosso código para o usuario
    printf("/// Bem vindo ao nosso codigo de listar tarefas, olhe as opcoes /// \n");
    printf("Opcao 1: Cadastrar nova tarefa\n"); // se opcao for 1,  cadastra uma nova tarefa
    printf("Opcao 2: Listar tarefa\n"); // se opcao for 2, lista as tarefas
    printf("Opcao 3: Deletar tarefa\n"); // se opcao for 3, deleta a tarefa selecionada pelo usuario
    printf("Opcao 4: Salvar tarefas\n"); // se opcao for 4, salva as tarefas em um arquivo txt
    printf("Opcao 5: Carregar tarefa\n"); // se opcao for 5, carrega as tarefas em um arquivo txt
    printf("Opcao 6: Alterar tarefa\n");
    printf("Opcao 7: Filtrar tarefa por pioridade\n");
    printf("Opcao 8: Filtrar tarefa por estado\n");
    printf("Opcao 9: Filtrar tarefa por prioridade e categoria\n");
    printf("Opcao 10: Exportar tarefas por prioridade para arquivo.txt\n");
    printf("Opcao 11: Exportar tarefas por categoria para arquivo.txt\n");
    printf("Opcao 12: Exportar tarefas por prioridade e categoria para arquivo.txt\n");
    printf("Opcao 0: Sair do codigo.\n"); // Termina o laço de repetição do código
    printf("Qual opcao voce deseja: "); // input do usuario de qual opcao ele deseja
}

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
    printf("Digite o estado da tarefa: ");
    fgets(lt->tarefas[lt->qtd].estado, 100, stdin);
    lt->tarefas[lt->qtd].estado[strcspn(lt->tarefas[lt->qtd].estado, "\n")] = '\0';
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

int listarTarefas(ListaDeTarefas *lt){ // lista o número de tarefas feitas pelo usuario
    if (lt->qtd == 0) {                // se o numero de tarefas for 0 retorna o print
        printf("Nenhum tarefa cadastrada\n");
        return 0;
    };

    for (int  i = 0; i < lt->qtd; i++) { // Pega a posição das tarefas e lista elas como "tarefa1", "tarefa2"...
        printf("Tarefa %d: \n", i+1);
        printf("Prioridade: %d\n", lt->tarefas[i].prioridade);
        printf("Descricao: %s\n", lt->tarefas[i].descricao);
        printf("Categoria: %s\n", lt->tarefas[i].categoria);
        printf("Estado: %s\n", lt->tarefas[i].estado);
    }
    return 0;
}

int salvarTarefas(ListaDeTarefas *lt, char *arquivo){ // salva as tarefas feitas em um arquivo binario
    FILE *arquivoTarefas = fopen(arquivo, "wb");

    if (arquivoTarefas == NULL) {
        printf("Erro ao salvar tarefa"); // se o arquivo estiver vazio, retorna um erro ao salvar a tarefa
    };

    fwrite(&lt->qtd, sizeof(int), 1, arquivoTarefas);

    for (int i = 0; i < lt->qtd; i++) {
        fwrite(&lt->tarefas[i], sizeof(Tarefa), 1, arquivoTarefas);
    };

    fclose(arquivoTarefas);
    printf("As tarefas foram salvas\n");
}

int carregarTarefas(ListaDeTarefas *lt, char *arquivo){ // carrega as tarefas feitas em um arquivo txt
    FILE *arquivoTarefas = fopen(arquivo, "rb");

    if (arquivoTarefas == NULL) {  // se o arquivo estiver vazio, retorna um erro ao carregar a tarefa
        printf("Erro ao encontrar o arquivo");
        return 0;
    };

    fread(&lt->qtd, sizeof(int), 1, arquivoTarefas);

    for (int i = 0; i < lt->qtd; i++) {
        fread(&lt->tarefas[i], sizeof(Tarefa), 1, arquivoTarefas);
    };

    fclose(arquivoTarefas);
    printf("Tarefas carregadas com sucesso");

    return 1;
}

void alterarTarefas(ListaDeTarefas *lt){
    if (lt->qtd == 0) {
        printf("Nenhuma tarefa cadastrada\n");
    }

    int numeroTarefa;
    printf("Escolha a tarefa que deseja alterar (1 a %d): ", lt->qtd);
    scanf("%d", &numeroTarefa);

    if (numeroTarefa < 1 || numeroTarefa > lt->qtd) {
        printf("Numero de tarefa invalido\n");
    }

    printf("Digite a nova prioridade da tarefa (0 a 10): ");
    scanf("%d", &lt->tarefas[numeroTarefa - 1].prioridade);

    getchar();

    printf("Digite a nova descricao da tarefa: ");
    fgets(lt->tarefas[numeroTarefa - 1].descricao, 300, stdin);
    lt->tarefas[numeroTarefa - 1].descricao[strcspn(lt->tarefas[numeroTarefa - 1].descricao, "\n")] = '\0';

    printf("Digite a nova categoria: ");
    fgets(lt->tarefas[numeroTarefa - 1].categoria, 100, stdin);
    lt->tarefas[numeroTarefa - 1].categoria[strcspn(lt->tarefas[numeroTarefa - 1].categoria, "\n")] = '\0';

    printf("Digite o estado da tarefa: ");
    fgets(lt->tarefas[numeroTarefa - 1].estado, 100, stdin);
    lt->tarefas[numeroTarefa - 1].estado[strcspn(lt->tarefas[numeroTarefa - 1].estado, "\n")] = '\0';
    printf("Tarefa alterada com sucesso\n");
}   

void filtrarTarefasPrioridade(ListaDeTarefas lt){
    int prioridade; 
    printf("Digite a prioridade para filtrar as tarefas (0 a 10): ");
    scanf("%d", &prioridade);

    printf("Tarefas com prioridade %d:\n", prioridade);
    int encontradas = 0;

    for (int i = 0; i < lt.qtd; i++){
        if (lt.tarefas[i].prioridade == prioridade) {
            encontradas = 1;
            printf("Tarefa %d: \n", i + 1);
            printf("Prioridade: %d\n", lt.tarefas[i].prioridade);
            printf("Descricao: %s\n", lt.tarefas[i].descricao);
            printf("Categoria: %s\n", lt.tarefas[i].categoria);
            printf("Estado: %s\n", lt.tarefas[i].estado);
        }
    }    

    if (!encontradas) {
        printf("Nenhuma tarefas encontrada com a prioridade %d solicitada\n");
    }
}

void filtrarTarefasEstado(ListaDeTarefas *lt){
    char estado[100]; 
    int encontradas = 0;

    printf("Digite o estado da tarefa que deseja filtrar: ");
    scanf("%s", &estado);
    

    for (int i = 0; i < lt->qtd; i++) {
        if (strcmp(lt->tarefas[i].estado, estado) == 0) {
            encontradas = 1;
            printf("Tarefa %d: \n", i + 1);
            printf("Prioridade: %d\n", lt->tarefas[i].prioridade);
            printf("Descricao: %s\n", lt->tarefas[i].descricao);
            printf("Categoria: %s\n", lt->tarefas[i].categoria);
            printf("Estado: %s\n", lt->tarefas[i].estado);
        }
    }    

    if (!encontradas) {
        printf("Nenhuma tarefas encontrada com o estado %s solicitada\n", estado);
    }

}

void filtrarPrioridadeCategoria(){
    printf("Fitra Tarefas por Prioridade e Categoria");
    
}

void exportarTarefasPrioridade(){
    printf("Exporta tarefas para um arquivo txt por prioridade");
}

void exportarTarefasCategoria(){
    printf("Exporta tarefas para um arquivo txt por categoria");

}

void exportarTarefasPrioridadeCategoria(){
    printf("Exporta tarefas para um arquivo txt pela juncao da prioridade e categoria");

}
