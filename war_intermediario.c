/*
 * Sistema WAR - Simulação de Ataques entre Territórios
 * 
 * Este programa simula um jogo de guerra onde territórios podem ser cadastrados
 * e jogadores podem atacar territórios inimigos usando dados aleatórios.
 * Utiliza alocação dinâmica de memória e manipulação por ponteiros.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da estrutura Territorio
// Agrupa informações relacionadas a um território em uma única unidade
typedef struct {
    char nome[30];    // Nome do território (até 29 caracteres + '\0')
    char cor[10];     // Cor do exército que controla o território
    int tropas;       // Quantidade de tropas no território
} Territorio;

// ==================== PROTÓTIPOS DAS FUNÇÕES ====================

void cadastrarTerritorios(Territorio* mapa, int quantidade);
void exibirTerritorios(Territorio* mapa, int quantidade);
void atacar(Territorio* atacante, Territorio* defensor);
void realizarAtaque(Territorio* mapa, int quantidade);
void liberarMemoria(Territorio* mapa);
void limparBuffer();

// ==================== FUNÇÃO PRINCIPAL ====================

/*
 * Função principal do programa
 * Gerencia o fluxo de cadastro, ataques e liberação de memória
 */
int main() {
    int numTerritorios;
    int opcao;
    Territorio* mapa = NULL; // Ponteiro para o vetor dinâmico de territórios
    
    // Inicializa o gerador de números aleatórios
    // Usa o tempo atual como semente para garantir aleatoriedade
    srand(time(NULL));
    
    // Mensagem de boas-vindas
    printf("========================================\n");
    printf("       SISTEMA WAR - TERRITORIOS\n");
    printf("========================================\n\n");
    
    // Solicita a quantidade de territórios a serem cadastrados
    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &numTerritorios);
    limparBuffer();
    
    // Validação da quantidade de territórios
    if (numTerritorios <= 0) {
        printf("Quantidade invalida! Encerrando programa.\n");
        return 1;
    }
    
    // ALOCAÇÃO DINÂMICA DE MEMÓRIA
    // Usa calloc para alocar e inicializar com zeros
    mapa = (Territorio*) calloc(numTerritorios, sizeof(Territorio));
    
    // Verifica se a alocação foi bem-sucedida
    if (mapa == NULL) {
        printf("Erro ao alocar memoria! Encerrando programa.\n");
        return 1;
    }
    
    printf("\n");
    
    // Cadastra os territórios
    cadastrarTerritorios(mapa, numTerritorios);
    
    // Menu principal do jogo
    do {
        printf("\n========================================\n");
        printf("              MENU PRINCIPAL\n");
        printf("========================================\n");
        printf("1. Exibir territorios\n");
        printf("2. Realizar ataque\n");
        printf("3. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1:
                printf("\n");
                exibirTerritorios(mapa, numTerritorios);
                break;
            case 2:
                realizarAtaque(mapa, numTerritorios);
                break;
            case 3:
                printf("\nEncerrando o jogo...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while(opcao != 3);
    
    // Liberação da memória alocada dinamicamente
    liberarMemoria(mapa);
    
    printf("Memoria liberada com sucesso!\n");
    printf("Ate a proxima batalha!\n");
    
    return 0;
}

// ==================== IMPLEMENTAÇÃO DAS FUNÇÕES ====================

/*
 * Função: cadastrarTerritorios
 * Realiza o cadastro de todos os territórios usando ponteiros
 * Parâmetros:
 *   - mapa: ponteiro para o vetor de territórios
 *   - quantidade: número de territórios a cadastrar
 */
void cadastrarTerritorios(Territorio* mapa, int quantidade) {
    printf("========================================\n");
    printf("      CADASTRO DE TERRITORIOS\n");
    printf("========================================\n\n");
    
    // Percorre o vetor usando aritmética de ponteiros
    for (int i = 0; i < quantidade; i++) {
        printf("--- Territorio %d ---\n", i + 1);
        
        // Acessa o território usando (mapa + i) ou mapa[i]
        // Ambas as notações são equivalentes
        printf("Digite o nome do territorio: ");
        fgets((mapa + i)->nome, 30, stdin);
        (mapa + i)->nome[strcspn((mapa + i)->nome, "\n")] = '\0';
        
        printf("Digite a cor do exercito: ");
        fgets((mapa + i)->cor, 10, stdin);
        (mapa + i)->cor[strcspn((mapa + i)->cor, "\n")] = '\0';
        
        printf("Digite o numero de tropas: ");
        scanf("%d", &(mapa + i)->tropas);
        limparBuffer();
        
        printf("\n");
    }
    
    printf("Todos os territorios foram cadastrados!\n");
}

/*
 * Função: exibirTerritorios
 * Exibe informações de todos os territórios cadastrados
 * Parâmetros:
 *   - mapa: ponteiro para o vetor de territórios
 *   - quantidade: número de territórios a exibir
 */
void exibirTerritorios(Territorio* mapa, int quantidade) {
    printf("========================================\n");
    printf("      TERRITORIOS CADASTRADOS\n");
    printf("========================================\n\n");
    
    // Usa ponteiros para percorrer e exibir os dados
    for (int i = 0; i < quantidade; i++) {
        Territorio* t = mapa + i; // Ponteiro para o território atual
        
        printf("Territorio %d:\n", i + 1);
        printf("  Nome: %s\n", t->nome);
        printf("  Cor do Exercito: %s\n", t->cor);
        printf("  Quantidade de Tropas: %d\n", t->tropas);
        printf("----------------------------------------\n");
    }
}

/*
 * Função: atacar
 * Simula um ataque entre dois territórios usando dados aleatórios
 * Parâmetros:
 *   - atacante: ponteiro para o território atacante
 *   - defensor: ponteiro para o território defensor
 */
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n========================================\n");
    printf("         SIMULACAO DE BATALHA\n");
    printf("========================================\n");
    printf("Atacante: %s (%s) - %d tropas\n", 
           atacante->nome, atacante->cor, atacante->tropas);
    printf("Defensor: %s (%s) - %d tropas\n", 
           defensor->nome, defensor->cor, defensor->tropas);
    printf("----------------------------------------\n");
    
    // Simula rolagem de dados (1 a 6) para cada lado
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;
    
    printf("Dado do Atacante: %d\n", dadoAtacante);
    printf("Dado do Defensor: %d\n", dadoDefensor);
    printf("----------------------------------------\n");
    
    // Determina o vencedor da batalha
    if (dadoAtacante > dadoDefensor) {
        printf("VITORIA DO ATACANTE!\n");
        printf("O territorio %s foi conquistado!\n", defensor->nome);
        
        // Atualiza o território defensor
        // Muda a cor (transfere controle) para o atacante
        strcpy(defensor->cor, atacante->cor);
        
        // Transfere metade das tropas do atacante para o defensor
        int tropasTransferidas = atacante->tropas / 2;
        if (tropasTransferidas < 1) tropasTransferidas = 1; // Mínimo de 1 tropa
        
        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;
        
        printf("Tropas transferidas: %d\n", tropasTransferidas);
        
    } else {
        printf("VITORIA DO DEFENSOR!\n");
        printf("O ataque foi repelido!\n");
        
        // O atacante perde uma tropa
        if (atacante->tropas > 1) {
            atacante->tropas--;
            printf("O atacante perdeu 1 tropa.\n");
        } else {
            printf("O atacante nao possui tropas suficientes para perder.\n");
        }
    }
    
    printf("========================================\n");
}

/*
 * Função: realizarAtaque
 * Gerencia a seleção de territórios e execução do ataque
 * Parâmetros:
 *   - mapa: ponteiro para o vetor de territórios
 *   - quantidade: número de territórios disponíveis
 */
void realizarAtaque(Territorio* mapa, int quantidade) {
    int indiceAtacante, indiceDefensor;
    
    printf("\n========================================\n");
    printf("         SELECAO DE ATAQUE\n");
    printf("========================================\n\n");
    
    // Exibe os territórios disponíveis
    printf("Territorios disponiveis:\n");
    for (int i = 0; i < quantidade; i++) {
        printf("%d. %s (%s) - %d tropas\n", 
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    
    // Seleciona o território atacante
    printf("\nEscolha o territorio ATACANTE (1-%d): ", quantidade);
    scanf("%d", &indiceAtacante);
    limparBuffer();
    indiceAtacante--; // Ajusta para índice do vetor (0-based)
    
    // Validação do índice do atacante
    if (indiceAtacante < 0 || indiceAtacante >= quantidade) {
        printf("Territorio invalido!\n");
        return;
    }
    
    // Verifica se o atacante tem tropas suficientes
    if (mapa[indiceAtacante].tropas < 2) {
        printf("O territorio atacante precisa ter pelo menos 2 tropas!\n");
        return;
    }
    
    // Seleciona o território defensor
    printf("Escolha o territorio DEFENSOR (1-%d): ", quantidade);
    scanf("%d", &indiceDefensor);
    limparBuffer();
    indiceDefensor--; // Ajusta para índice do vetor
    
    // Validação do índice do defensor
    if (indiceDefensor < 0 || indiceDefensor >= quantidade) {
        printf("Territorio invalido!\n");
        return;
    }
    
    // Impede ataque ao próprio território
    if (indiceAtacante == indiceDefensor) {
        printf("Um territorio nao pode atacar a si mesmo!\n");
        return;
    }
    
    // Impede ataque entre territórios da mesma cor
    if (strcmp(mapa[indiceAtacante].cor, mapa[indiceDefensor].cor) == 0) {
        printf("Nao e possivel atacar um territorio da mesma cor!\n");
        return;
    }
    
    // Executa o ataque usando ponteiros
    atacar(&mapa[indiceAtacante], &mapa[indiceDefensor]);
    
    // Exibe o estado atualizado dos territórios envolvidos
    printf("\nEstado apos o ataque:\n");
    printf("Atacante - %s: %d tropas (%s)\n", 
           mapa[indiceAtacante].nome, mapa[indiceAtacante].tropas, 
           mapa[indiceAtacante].cor);
    printf("Defensor - %s: %d tropas (%s)\n", 
           mapa[indiceDefensor].nome, mapa[indiceDefensor].tropas, 
           mapa[indiceDefensor].cor);
}

/*
 * Função: liberarMemoria
 * Libera a memória alocada dinamicamente para os territórios
 * Parâmetro:
 *   - mapa: ponteiro para o vetor de territórios a ser liberado
 */
void liberarMemoria(Territorio* mapa) {
    // Verifica se o ponteiro não é nulo antes de liberar
    if (mapa != NULL) {
        free(mapa);
        mapa = NULL; // Boa prática: evita ponteiros pendentes
    }
}

/*
 * Função: limparBuffer
 * Limpa o buffer de entrada para evitar problemas com leitura
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}