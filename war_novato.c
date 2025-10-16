/*
 * Sistema de Cadastro de Territórios
 * 
 * Este programa permite o cadastro de 5 territórios com suas características
 * (nome, cor do exército e quantidade de tropas) e exibe os dados cadastrados.
 */

#include <stdio.h>
#include <string.h>

// Definição da estrutura Territorio
// Agrupa informações relacionadas a um território em uma única unidade
typedef struct {
    char nome[30];    // Nome do território (até 29 caracteres + '\0')
    char cor[10];     // Cor do exército (até 9 caracteres + '\0')
    int tropas;       // Quantidade de tropas no território
} Territorio;

// Constante que define o número de territórios a serem cadastrados
#define NUM_TERRITORIOS 5

/*
 * Função principal do programa
 * Responsável por controlar o fluxo de cadastro e exibição dos territórios
 */
int main() {
    // Declaração do vetor de structs para armazenar os 5 territórios
    Territorio territorios[NUM_TERRITORIOS];
    
    // Mensagem de boas-vindas
    printf("========================================\n");
    printf("  SISTEMA DE CADASTRO DE TERRITORIOS\n");
    printf("========================================\n\n");
    
    // FASE 1: CADASTRO DOS TERRITÓRIOS
    // Laço for para preencher os dados de cada território
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("--- Cadastro do Territorio %d ---\n", i + 1);
        
        // Entrada do nome do território
        printf("Digite o nome do territorio: ");
        // Limpa o buffer antes de ler a string
        if (i == 0) {
            getchar(); // Remove o '\n' residual apenas na primeira iteração
        }
        // Usa fgets para leitura segura de strings com espaços
        fgets(territorios[i].nome, 30, stdin);
        // Remove o caractere de nova linha '\n' capturado pelo fgets
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';
        
        // Entrada da cor do exército
        printf("Digite a cor do exercito: ");
        fgets(territorios[i].cor, 10, stdin);
        // Remove o '\n' da string de cor
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';
        
        // Entrada da quantidade de tropas
        printf("Digite o numero de tropas: ");
        scanf("%d", &territorios[i].tropas);
        getchar(); // Consome o '\n' deixado pelo scanf
        
        printf("\n"); // Linha em branco para melhor legibilidade
    }
    
    // FASE 2: EXIBIÇÃO DOS DADOS CADASTRADOS
    printf("========================================\n");
    printf("  TERRITORIOS CADASTRADOS\n");
    printf("========================================\n\n");
    
    // Laço for para percorrer e exibir os dados de cada território
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("  Nome: %s\n", territorios[i].nome);
        printf("  Cor do Exercito: %s\n", territorios[i].cor);
        printf("  Quantidade de Tropas: %d\n", territorios[i].tropas);
        printf("----------------------------------------\n");
    }
    
    // Mensagem de encerramento
    printf("\nCadastro finalizado com sucesso!\n");
    
    return 0; // Retorna 0 indicando execução bem-sucedida
}