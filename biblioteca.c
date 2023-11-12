#include <stdio.h>
#include "biblioteca.h"

//função global que foi usada em quase todas as funções para limpar o buffer do teclado;
void limpaBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF){ }
}

//Função de menu, apresenta todas as opções para o usuario;
int printMenu(){ 
    printf("/// Bem vindo ao nosso codigo de listar tarefas, olhe as opcoes /// \n");
    printf("Opcao 1: Cadastrar nova tarefa\n"); // se opcao for 1,  cadastra uma nova tarefa
    printf("Opcao 2: Listar tarefa\n"); // se opcao for 2, lista as tarefas
    printf("Opcao 3: Deletar tarefa\n"); // se opcao for 3, deleta a tarefa selecionada pelo usuario
    printf("Opcao 4: Salvar tarefas\n"); // se opcao for 4, salva as tarefas em um arquivo txt
    printf("Opcao 5: Carregar tarefa\n"); // se opcao for 5, carrega as tarefas em um arquivo txt
    printf("Opcao 6: Alterar tarefa\n");  // opção 6, permite ao usuario alterar uma tarefa por completo
    printf("Opcao 7: Filtrar tarefa por pioridade\n"); //opção 7 filtra as tarefas de prioridade escolhida pelo usuario
    printf("Opcao 8: Filtrar tarefa por estado\n"); // opção filtra as tarefas pelo estado dela
    printf("Opcao 9: Filtrar tarefa por prioridade e categoria\n"); // filtra as tarefas pela prioridade e categoria escolhida pelo usuario, uma função que filtra algo mais especifico 
    printf("Opcao 10: Exportar tarefas por prioridade para arquivo.txt\n"); // exporta as tarefas para arquivo.txt pela prioridade solicitada pelos usuarios 
    printf("Opcao 11: Exportar tarefas por categoria para arquivo.txt\n"); // exporta as tarefas para arquivo.txt por categoria solicitada pelos usuarios 
    printf("Opcao 12: Exportar tarefas por prioridade e categoria para arquivo.txt\n");
    printf("Opcao 0: Sair do codigo.\n"); // Termina o laço de repetição do código
    printf("Qual opcao voce deseja: "); // input do usuario de qual opcao ele deseja
}

int cadastrarTarefa(ListaDeTarefas *lt){ //função que é usada para cadastrar uma nova tarefa para o usuario
    printf("Digite a prioridade da tarefa (0 a 10): "); // define a prioridade da tarefa
    scanf("%d", &lt->tarefas[lt->qtd].prioridade); // define a entrada de dados da prioridade da tarefa e salva na struct
    limpaBuffer(); // função que limpa o buffer do teclado
    printf("Descreva a tarefa: \n"); // solictia a definição da descrição para o usuario 
    fgets(lt->tarefas[lt->qtd].descricao, 300, stdin); 
    lt->tarefas[lt->qtd].descricao[strcspn(lt->tarefas[lt->qtd].descricao, "\n")] = '\0'; // Remove a quebra de linha do final
    printf("Categorize a tarefa (menos importante a muito importante): "); // define o grau de importância da tarefa
    fgets(lt->tarefas[lt->qtd].categoria, 100, stdin);
    lt->tarefas[lt->qtd].categoria[strcspn(lt->tarefas[lt->qtd].categoria, "\n")] = '\0'; // Remove a quebra de linha do final
    printf("Digite o estado da tarefa: "); // solicita ao usuario o estado atual da tarefa
    fgets(lt->tarefas[lt->qtd].estado, 100, stdin);
    lt->tarefas[lt->qtd].estado[strcspn(lt->tarefas[lt->qtd].estado, "\n")] = '\0';
    lt->qtd++; // adiciona a tarefa cadastrada
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
        fwrite(&lt->tarefas[i], sizeof(Tarefa), 1, arquivoTarefas); // escreve as tarefas no arquivo binario 
    };

    fclose(arquivoTarefas); // fecha o arquivo binario 
    printf("As tarefas foram salvas\n");
}

int carregarTarefas(ListaDeTarefas *lt, char *arquivo){ //função que carrega as tarefas salvas do arquivo binario para o código
    FILE *arquivoTarefas = fopen(arquivo, "rb");

    if (arquivoTarefas == NULL) {  // se o arquivo estiver vazio, retorna um erro ao carregar a tarefa
        printf("Erro ao encontrar o arquivo");
        return 0;
    };

    fread(&lt->qtd, sizeof(int), 1, arquivoTarefas); // le o arquivo binario 

    for (int i = 0; i < lt->qtd; i++) {
        fread(&lt->tarefas[i], sizeof(Tarefa), 1, arquivoTarefas); // le as tarefas salvas no arquivo binario, uma por uma
    };

    fclose(arquivoTarefas); // fecha o arquivo binario
    printf("Tarefas carregadas com sucesso");

    return 1;
}

//Função de alterar por completo a tarefa
int alterarTarefas(ListaDeTarefas *lt){
    if (lt->qtd == 0) {
        printf("Nenhuma tarefa cadastrada\n"); // se não tiver tarefas cadastradas, não inicia o laço 
    }

    int numeroTarefa;
    printf("Escolha a tarefa que deseja alterar (1 a %d): ", lt->qtd); // mostra ao usuario o numero de tarefas e solicita a tarefa que ele deseja alterar
    scanf("%d", &numeroTarefa);

    if (numeroTarefa < 1 || numeroTarefa > lt->qtd) {
        printf("Numero de tarefa invalido\n");
    }

    printf("Digite a nova prioridade da tarefa (0 a 10): "); //define nova prioridade
    scanf("%d", &lt->tarefas[numeroTarefa - 1].prioridade);

    getchar();

    printf("Digite a nova descricao da tarefa: "); //define nova descrição
    fgets(lt->tarefas[numeroTarefa - 1].descricao, 300, stdin);
    lt->tarefas[numeroTarefa - 1].descricao[strcspn(lt->tarefas[numeroTarefa - 1].descricao, "\n")] = '\0';

    printf("Digite a nova categoria: "); //define nova categoria
    fgets(lt->tarefas[numeroTarefa - 1].categoria, 100, stdin);
    lt->tarefas[numeroTarefa - 1].categoria[strcspn(lt->tarefas[numeroTarefa - 1].categoria, "\n")] = '\0';

    printf("Digite o estado da tarefa: "); //define novo estado da tarefa
    fgets(lt->tarefas[numeroTarefa - 1].estado, 100, stdin);
    lt->tarefas[numeroTarefa - 1].estado[strcspn(lt->tarefas[numeroTarefa - 1].estado, "\n")] = '\0';
    printf("Tarefa alterada com sucesso\n"); // mostra que a tarefa foi alterada com sucesso 
}   

// Função de filtrar as tarefas pela prioridade
int filtrarTarefasPrioridade(ListaDeTarefas lt){
    if (lt.qtd == 0) {
        printf("Nenhuma tarefas cadastradaz\n"); // se não tiver tarefas cadastradas, não inicia o laço
        return 0;
    }
    
    int prioridade; 
    printf("Digite a prioridade para filtrar as tarefas (0 a 10): "); // Solicita a prioridade das tarefas que o usuario deseja filtrar
    scanf("%d", &prioridade);

    printf("Tarefas com prioridade %d:\n", prioridade); //Mostra a prioridade escolhida
    int encontradas = 0;

    for (int i = 0; i < lt.qtd; i++){ // Percorre as tarefas pela posição
        if (lt.tarefas[i].prioridade == prioridade) { // Se a prioridade da tarefa for igual a solicitada, imprime a tarefa 
            encontradas = 1;
            printf("Tarefa %d: \n", i + 1);
            printf("Prioridade: %d\n", lt.tarefas[i].prioridade);
            printf("Descricao: %s\n", lt.tarefas[i].descricao);
            printf("Categoria: %s\n", lt.tarefas[i].categoria);
            printf("Estado: %s\n", lt.tarefas[i].estado);
        }
    }    

    if (!encontradas) { // Se não tiver nenhuma tarefa com a prioridade solicitada imprime abaixo 
        printf("Nenhuma tarefas encontrada com a prioridade %d solicitada\n");
    }
}

// Função que filtra as tarefas pelo seu estado
int filtrarTarefasEstado(ListaDeTarefas *lt){
    if (lt.qtd == 0) {
        printf("Nenhuma tarefas cadastradaz\n"); // se não tiver tarefas cadastradas, não inicia o laço
        return 0;
    }    
    
    char estado[100]; 
    
    limpaBuffer(); // Limpa o buffer do teclado 
    printf("Digite o estado da tarefa que deseja filtrar: "); // Solicita ao usuario o estado das tarefas que deseja filtrar
    fgets(estado, 100, stdin);
    estado[strcspn(estado, "\n")] = '\0';
    
    int encontradas = 0;


    for (int i = 0; i < lt->qtd; i++) { // Percorre as tarefas pela posição
        if (strcmp(lt->tarefas[i].estado, estado) == 0) { // Se o estado da tarefa for igual ao solicitada, imprime a tarefa abaixo
            encontradas = 1;
            printf("Tarefa %d: \n", i + 1);
            printf("Prioridade: %d\n", lt->tarefas[i].prioridade);
            printf("Descricao: %s\n", lt->tarefas[i].descricao);
            printf("Categoria: %s\n", lt->tarefas[i].categoria);
            printf("Estado: %s\n", lt->tarefas[i].estado);
        }
    }    

    if (!encontradas) { // Se não tiver nenhuma tarefa com o estado solicitado imprime abaixo 
        printf("Nenhuma tarefas encontrada com o estado %s \n", estado);
    }
}

// Função de filtrar as tarefas pela sua prioridade e categoria
int filtrarPrioridadeCategoria(ListaDeTarefas lt){
    if (lt.qtd == 0) {
        printf("Nenhuma tarefas cadastradaz\n"); // Se não tiver tarefas cadastradas, não inicia o laço
        return 0;
    }    
    
    char categoria[100];
    printf("Digite a categoria que deseja filtrar: "); // Solicita a categoria das tarefas que deseja filtrar
    limpaBuffer();  // Limpa o buffer do teclado
    fgets(categoria, 100, stdin);
    categoria[strcspn(categoria, "\n")] = '\0';
    
    int prioridade;
    printf("Digite a prioridade: "); // Solicita ao usuario a prioridade das tarefas que deseja filtrar
    scanf("%d", &prioridade);
    limpaBuffer(); //Limpa o buffer do teclado


    printf("Tarefas com a categoria e prioridade solicitadas\n");

    int encontradas = 0;

    for (int i = 0; i < lt.qtd; i++) { // Percorre as tarefas salvas
        if (strcmp(lt.tarefas[i].categoria, categoria) == 0 && lt.tarefas[i].prioridade == prioridade){ // Se a categoria e prioridade solicita for igual a de uma tarefa salva, imprime na tela
            encontradas = 1;
            printf("Tarefa %d: \n", i + 1);
            printf("Prioridade: %d\n", lt.tarefas[i].prioridade);
            printf("Descrição tarefa: %s\n", lt.tarefas[i].descricao);
            printf("Categoria: %s\n", lt.tarefas[i].categoria);
            printf("Prioridade: %s\n", lt.tarefas[i].estado);
        }
    }

    if (!encontradas) { // Se não tiver nenhuma tarefa com o estado solicitado imprime abaixo 
        printf("Nenhuma tarefa encontrada com a categoria %s e prioridade %d\n", categoria, prioridade);
    }
}

// Função que exporta as tarefas para um arquivo txt de acordo com a prioridade solicitada
int exportarTarefasPrioridade(ListaDeTarefas lt) {
    FILE *arquivo;
    int prioridade;

    printf("Digite a prioridade para exportar as tarefas (0 a 10): "); // Solicita a prioridade que o usuario deseja filtrar
    scanf("%d", &prioridade);
    limpaBuffer(); // Limpa o buffer do teclado 

    char nomeArquivo[100];
    sprintf(nomeArquivo, "tarefas_prioridade_%d.txt", prioridade);

    arquivo = fopen(nomeArquivo, "w"); // Abre o arquivo

    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo de exportacao.\n"); // Se o arquivo for igual a NULL siginifica que teve um erro na hora de abrir o arquivo
        return 0;
    }

    fprintf(arquivo, "Tarefas com prioridade %d:\n", prioridade);
    int encontradas = 0;

    for (int i = 0; i < lt.qtd; i++) { // Passa cada posição das tarefas cadastradas
        if (lt.tarefas[i].prioridade == prioridade) { // Se a prioridade da tarefa for igual a solicitada pelo usuario, exporta elas para o arquivo txt e imprime elas
            encontradas = 1;
            fprintf(arquivo, "Tarefa %d:\n", i + 1);
            fprintf(arquivo, "Prioridade: %d\n", lt.tarefas[i].prioridade);
            fprintf(arquivo, "Descricao: %s\n", lt.tarefas[i].descricao);
            fprintf(arquivo, "Categoria: %s\n", lt.tarefas[i].categoria);
            fprintf(arquivo, "Estado: %s\n", lt.tarefas[i].estado);
            fprintf(arquivo, "\n");
        }
    }

    fclose(arquivo); // Fecha o arquivo

    if (encontradas) {
        printf("Tarefas exportadas com sucesso para %s.\n", nomeArquivo); // Se terminar o laço, imprime essa mensagem
    } else {
        remove(nomeArquivo); // Remove o arquivo 
        printf("Nenhuma tarefa encontrada com a prioridade %d.\n", prioridade); //Imprime a mensagem se não encontrar nenhuma tarefa com a prioridade solicitada
    }
}

//Ponteiro de função para ordenar tarefas
int compararTarefas(const void *a, const void *b){
    return ((Tarefa*)b)->prioridade - ((Tarefa*)a)->prioridade;
}

int exportarTarefasCategoria(ListaDeTarefas lt) {
    char categoria[100];

    printf("Digite a categoria para exportar as tarefas: "); //Solicita ao usuario a categoria das tarefas que ele deseja exportar
    limpaBuffer(); // Limpa o buffer do teclado 
    fgets(categoria, 100, stdin);
    categoria[strcspn(categoria, "\n")] = '\0';

    qsort(lt.tarefas, lt.qtd, sizeof(Tarefa), compararTarefas); // Ordena as tarefas pela prioridade em ordem descrescente 

    char nomeArquivo[100];
    sprintf(nomeArquivo, "tarefas_categoria_%s.txt", categoria);

    FILE *arquivo = fopen(nomeArquivo, "w"); // Abre o arquivo 

    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo %s.\n", nomeArquivo); // Se o arquivo for igual a NULL indica que tem um erro na hora de criar o arquivo 
        return 1; // Indica que houve um erro na criação do arquivo
    }

    int encontradas = 0;

    for (int i = 0; i < lt.qtd; i++) { // Passa cada posição das tarefas cadastradas
        if (strcmp(lt.tarefas[i].categoria, categoria) == 0) { //Se a categoria das tarefas salvas forem iguais a solicitada pelo usuario, imprime as tarefas 
            encontradas = 1;
            fprintf(arquivo, "Tarefa %d:\n", i + 1);
            fprintf(arquivo, "Prioridade: %d\n", lt.tarefas[i].prioridade);
            fprintf(arquivo, "Descricao: %s\n", lt.tarefas[i].descricao);
            fprintf(arquivo, "Categoria: %s\n", lt.tarefas[i].categoria);
            fprintf(arquivo, "Estado: %s\n", lt.tarefas[i].estado);
            fprintf(arquivo, "\n");

        }
    }

    fclose(arquivo); // Fecha o arquivo 

    if (!encontradas) {
        remove(nomeArquivo); // Remove o arquivo 
        printf("Nenhuma tarefa encontrada com a categoria %s. O arquivo não foi criado.\n", categoria); //Imprime a mensagem se não encontrar nenhuma tarefa com a prioridade solicitada
    } else {
        printf("Tarefas exportadas com sucesso para %s.\n", nomeArquivo); // Se terminar o laço, imprime que as tarefas foram exportadas com sucesso 
    }

    return 0; 
}

int exportarTarefasPrioridadeCategoria(ListaDeTarefas lt){
    int prioridade;
    char categoria[100];

    printf("Digite a prioridade para exportar as tarefas (0 a 10): "); // Solicita a prioridade desejada pelo usuario 
    scanf("%d", &prioridade);
    limpaBuffer(); // Limpa o buffer do teclado

    printf("Digite a categoria para exportar as tarefas: "); // Solicita a categoria desejada pelo usuario 
    fgets(categoria, 100, stdin);
    categoria[strcspn(categoria, "\n")] = '\0';

    // Ordenar as tarefas por prioridade (da maior para a menor)
    qsort(lt.tarefas, lt.qtd, sizeof(Tarefa), compararTarefas);

    char nomeArquivo[100];
    sprintf(nomeArquivo, "tarefas_prioridade_categoria_%d_%s.txt", prioridade, categoria);

    FILE *arquivo = fopen(nomeArquivo, "w"); // Abre o arquivo 

    if (arquivo == NULL) { // Se o arquivo for igual a NULL indica que tem um erro na hora de criar o arquivo 
        printf("Erro ao criar o arquivo %s.\n", nomeArquivo);
        return 1; // Indica que houve um erro na criação do arquivo
    }

    int encontradas = 0;

    for (int i = 0; i < lt.qtd; i++) { // Passa cada posição das tarefas cadastradas
        if (lt.tarefas[i].prioridade == prioridade && strcmp(lt.tarefas[i].categoria, categoria) == 0) { // Se a categoria e prioridade solicita for igual as de uma tarefa salva, exporta para um arquivo txt
            encontradas = 1;
            
            fprintf(arquivo, "Tarefa %d:\n", i + 1);
            fprintf(arquivo, "Prioridade: %d\n", lt.tarefas[i].prioridade);
            fprintf(arquivo, "Descricao: %s\n", lt.tarefas[i].descricao);
            fprintf(arquivo, "Categoria: %s\n", lt.tarefas[i].categoria);
            fprintf(arquivo, "Estado: %s\n", lt.tarefas[i].estado);
            fprintf(arquivo, "\n");
        }
    }

    fclose(arquivo); // Fecha o arquivo 

    if (!encontradas) {
        remove(nomeArquivo); // Remove o arquivo vazio, já que nenhuma tarefa foi encontrada
        printf("Nenhuma tarefa encontrada com a prioridade %d e categoria %s. O arquivo não foi criado.\n", prioridade, categoria);
    } else {
        printf("Tarefas exportadas com sucesso para %s.\n", nomeArquivo); // Se o laço for terminado, imprime que as tarefas foram exportadas com sucesso 
    }

    return 0; 
}


