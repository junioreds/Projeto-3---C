#include <stdio.h>
#include "biblioteca.h"

// Edson Pedreira de Oliveira Junior R.A 22.123.038-6


int main() {
    ListaDeTarefas lt;
    lt.qtd = 0; // Inicializa a quantidade de tarefas como 0


    int opcao;  //    Laço de repetição que da as opções de escolha para o usuario
    while(1) { // Enquanto for verdadeiro, ira continuar o laço até o usuario digitar "0"
        printMenu();
        scanf("%d", &opcao);

        if (opcao == 0){ // se a opcao digitada pelo usuario for "0", sai do laço de repetição e interrompe o código
            break; // Sai do loop
        } else if (opcao == 1){
            cadastrarTarefa(&lt); // Chama a função de cadastrar a tarefa localizada nas bibliotecas .c e .h
        } else if (opcao == 2) {
            listarTarefas(lt); // Chama a função de listar as tarefas que ja foram salvas
        } else if (opcao == 3) {
            deletarTarefa(&lt); // Deleta a tarefa selecionada pelo usuario
        }  else if (opcao == 4){
            salvarTarefas(&lt, "tarefas.txt"); // salva as tarefas em um arquivo.txt
        }  else if (opcao == 5){
            carregarTarefas(&lt, "tarefas.txt"); // carrega as tarefas em um arquivo.txt
        } else{
            printf("Opcao nao disponivel.\n"); // Mostra ao usuario que não existe a opção alem de 1 a 5, e retorna as opções de entrada
        }
    }

    return 0;
}
