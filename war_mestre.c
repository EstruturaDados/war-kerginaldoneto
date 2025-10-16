/*
 * Sistema WAR - Simulação Completa com Missões Estratégicas
 * 
 * Este programa simula um jogo de guerra onde jogadores recebem missões
 * estratégicas e devem conquistar territórios para vencer.
 * Utiliza alocação dinâmica, ponteiros e verificação de condições de vitória.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da estrutura Territorio
typedef struct {
    char nome[30];    // Nome do território
    char cor[10];     // Cor do exército que controla o território
    int tropas;       // Quantidade de tropas no território
} Territorio;

// Definição da estrutura Jogador
typedef struct {
    char nome[30];    // Nome do jogador
    char cor[10];     // Cor do exército do jogador
    char* missao;     // Ponteiro para a missão (alocação dinâmica)
} Jogador;

// ==================== PROTÓTIPOS DAS FUNÇÕES ====================

void cadastrarTerritorios(Territorio* mapa, int quantidade);
void cadastrarJogadores(Jogador* jogadores, int quantidade);
void exibirTerritorios(Territorio* mapa, int quantidade);
void exibirMissao(char* missao);
void atribuirMissao(char* destino, char* missoes[], int totalMissoes);
int verificarMissao(char* missao, Territorio* mapa, int tamanho, char* corJogador);
void atacar(Territorio* atacante, Territorio* defensor);
void realizarAtaque(Territorio* mapa, int quantidade);
void verificarVitoria(Jogador* jogadores, int numJogadores, Territorio* mapa, int numTerritorios);
void liberarMemoria(Territorio* mapa, Jogador* jogadores, int numJogadores);
void limparBuffer();

// ==================== FUNÇÃO PRINCIPAL ====================

int main() {
    int numTerritorios, numJogadores;
    int opcao;
    int turno = 1;
    Territorio* mapa = NULL;
    Jogador* jogadores = NULL;
    
    // Inicializa o gerador de números aleatórios
    srand(time(NULL));
    
    // Mensagem de boas-vindas
    printf("========================================\n");
    printf("    SISTEMA WAR - MISSOES ESTRATEGICAS\n");
    printf("========================================\n\n");
    
    // Solicita o número de jogadores
    printf("Quantos jogadores vao participar? ");
    scanf("%d", &numJogadores);
    limparBuffer();
    
    if (numJogadores <= 0) {
        printf("Quantidade invalida! Encerrando programa.\n");
        return 1;
    }
    
    // Solicita a quantidade de territórios
    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &numTerritorios);
    limparBuffer();
    
    if (numTerritorios <= 0) {
        printf("Quantidade invalida! Encerrando programa.\n");
        return 1;
    }
    
    // ALOCAÇÃO DINÂMICA DOS TERRITÓRIOS
    mapa = (Territorio*) calloc(numTerritorios, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memoria para territorios!\n");
        return 1;
    }
    
    // ALOCAÇÃO DINÂMICA DOS JOGADORES
    jogadores = (Jogador*) calloc(numJogadores, sizeof(Jogador));
    if (jogadores == NULL) {
        printf("Erro ao alocar memoria para jogadores!\n");
        free(mapa);
        return 1;
    }
    
    printf("\n");
    
    // Cadastra os jogadores e atribui missões
    cadastrarJogadores(jogadores, numJogadores);
    
    // Cadastra os territórios
    cadastrarTerritorios(mapa, numTerritorios);
    
    // Menu principal do jogo
    do {
        printf("\n========================================\n");
        printf("        MENU PRINCIPAL - TURNO %d\n", turno);
        printf("========================================\n");
        printf("1. Exibir territorios\n");
        printf("2. Exibir missoes dos jogadores\n");
        printf("3. Realizar ataque\n");
        printf("4. Verificar condicoes de vitoria\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1:
                printf("\n");
                exibirTerritorios(mapa, numTerritorios);
                break;
            case 2:
                printf("\n========================================\n");
                printf("      MISSOES DOS JOGADORES\n");
                printf("========================================\n");
                for (int i = 0; i < numJogadores; i++) {
                    printf("\nJogador: %s (%s)\n", jogadores[i].nome, jogadores[i].cor);
                    exibirMissao(jogadores[i].missao);
                }
                break;
            case 3:
                realizarAtaque(mapa, numTerritorios);
                turno++;
                // Verifica vitória automaticamente após cada ataque
                verificarVitoria(jogadores, numJogadores, mapa, numTerritorios);
                break;
            case 4:
                verificarVitoria(jogadores, numJogadores, mapa, numTerritorios);
                break;
            case 5:
                printf("\nEncerrando o jogo...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while(opcao != 5);
    
    // Liberação da memória alocada dinamicamente
    liberarMemoria(mapa, jogadores, numJogadores);
    
    printf("Memoria liberada com sucesso!\n");
    printf("Ate a proxima batalha!\n");
    
    return 0;
}

// ==================== IMPLEMENTAÇÃO DAS FUNÇÕES ====================

/*
 * Função: cadastrarJogadores
 * Cadastra os jogadores e atribui missões aleatórias
 */
void cadastrarJogadores(Jogador* jogadores, int quantidade) {
    // Vetor de missões pré-definidas
    char* missoes[] = {
        "Conquistar 3 territorios seguidos com a mesma cor",
        "Eliminar todas as tropas da cor vermelha do mapa",
        "Controlar pelo menos 5 territorios ao mesmo tempo",
        "Acumular 30 ou mais tropas em um unico territorio",
        "Conquistar territorios de pelo menos 3 cores diferentes",
        "Dominar todos os territorios cujo nome comeca com a letra 'B'",
        "Ter controle de territorios com soma total de 40 tropas"
    };
    int totalMissoes = 7;
    
    printf("========================================\n");
    printf("      CADASTRO DE JOGADORES\n");
    printf("========================================\n\n");
    
    for (int i = 0; i < quantidade; i++) {
        printf("--- Jogador %d ---\n", i + 1);
        
        printf("Digite o nome do jogador: ");
        fgets(jogadores[i].nome, 30, stdin);
        jogadores[i].nome[strcspn(jogadores[i].nome, "\n")] = '\0';
        
        printf("Digite a cor do exercito: ");
        fgets(jogadores[i].cor, 10, stdin);
        jogadores[i].cor[strcspn(jogadores[i].cor, "\n")] = '\0';
        
        // ALOCAÇÃO DINÂMICA PARA A MISSÃO
        jogadores[i].missao = (char*) malloc(100 * sizeof(char));
        if (jogadores[i].missao == NULL) {
            printf("Erro ao alocar memoria para a missao!\n");
            exit(1);
        }
        
        // Atribui uma missão aleatória (passagem por referência)
        atribuirMissao(jogadores[i].missao, missoes, totalMissoes);
        
        printf("\nMissao atribuida para %s:\n", jogadores[i].nome);
        exibirMissao(jogadores[i].missao); // Passagem por valor
        printf("\n");
    }
    
    printf("Todos os jogadores foram cadastrados!\n");
}

/*
 * Função: atribuirMissao
 * Sorteia e atribui uma missão aleatória ao jogador
 * Parâmetros:
 *   - destino: ponteiro para onde a missão será copiada (passagem por referência)
 *   - missoes: vetor de strings com as missões disponíveis
 *   - totalMissoes: quantidade total de missões no vetor
 */
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    // Sorteia um índice aleatório
    int indice = rand() % totalMissoes;
    
    // Copia a missão sorteada para o destino usando strcpy
    strcpy(destino, missoes[indice]);
}

/*
 * Função: exibirMissao
 * Exibe a missão do jogador (passagem por valor - apenas leitura)
 */
void exibirMissao(char* missao) {
    printf("Missao: %s\n", missao);
}

/*
 * Função: verificarMissao
 * Verifica se a missão do jogador foi cumprida
 * Retorna 1 se cumprida, 0 caso contrário
 */
int verificarMissao(char* missao, Territorio* mapa, int tamanho, char* corJogador) {
    // Contadores para verificação das missões
    int territoriosControlados = 0;
    int tropasVermelhas = 0;
    int tropasEmUmTerritorio = 0;
    int coresConquistadas[10] = {0}; // Até 10 cores diferentes
    int indiceCores = 0;
    int somaTotalTropas = 0;
    int territoriosSequenciais = 0;
    int sequenciaAtual = 0;
    char coresUnicas[10][10];
    int numCoresUnicas = 0;
    
    // Analisa todos os territórios
    for (int i = 0; i < tamanho; i++) {
        // Conta territórios controlados pelo jogador
        if (strcmp(mapa[i].cor, corJogador) == 0) {
            territoriosControlados++;
            somaTotalTropas += mapa[i].tropas;
            sequenciaAtual++;
            
            // Verifica maior quantidade de tropas em um território
            if (mapa[i].tropas > tropasEmUmTerritorio) {
                tropasEmUmTerritorio = mapa[i].tropas;
            }
            
            // Adiciona cor única se ainda não foi contada
            int corJaContada = 0;
            for (int j = 0; j < numCoresUnicas; j++) {
                if (strcmp(coresUnicas[j], mapa[i].cor) == 0) {
                    corJaContada = 1;
                    break;
                }
            }
            if (!corJaContada && numCoresUnicas < 10) {
                strcpy(coresUnicas[numCoresUnicas], mapa[i].cor);
                numCoresUnicas++;
            }
        } else {
            if (sequenciaAtual > territoriosSequenciais) {
                territoriosSequenciais = sequenciaAtual;
            }
            sequenciaAtual = 0;
        }
        
        // Conta tropas vermelhas no mapa
        if (strcmp(mapa[i].cor, "vermelha") == 0 || strcmp(mapa[i].cor, "Vermelha") == 0) {
            tropasVermelhas += mapa[i].tropas;
        }
    }
    
    // Atualiza sequência final
    if (sequenciaAtual > territoriosSequenciais) {
        territoriosSequenciais = sequenciaAtual;
    }
    
    // VERIFICAÇÃO DAS MISSÕES ESPECÍFICAS
    
    // Missão 1: Conquistar 3 territórios seguidos
    if (strstr(missao, "3 territorios seguidos") != NULL) {
        return territoriosSequenciais >= 3;
    }
    
    // Missão 2: Eliminar todas as tropas vermelhas
    if (strstr(missao, "tropas da cor vermelha") != NULL) {
        return tropasVermelhas == 0;
    }
    
    // Missão 3: Controlar pelo menos 5 territórios
    if (strstr(missao, "5 territorios") != NULL) {
        return territoriosControlados >= 5;
    }
    
    // Missão 4: Acumular 30 ou mais tropas em um único território
    if (strstr(missao, "30 ou mais tropas") != NULL) {
        return tropasEmUmTerritorio >= 30;
    }
    
    // Missão 5: Conquistar territórios de 3 cores diferentes
    if (strstr(missao, "3 cores diferentes") != NULL) {
        return numCoresUnicas >= 3;
    }
    
    // Missão 6: Dominar territórios que começam com 'B'
    if (strstr(missao, "comeca com a letra 'B'") != NULL) {
        int territoriosB = 0;
        int territoriosBControlados = 0;
        for (int i = 0; i < tamanho; i++) {
            if (mapa[i].nome[0] == 'B' || mapa[i].nome[0] == 'b') {
                territoriosB++;
                if (strcmp(mapa[i].cor, corJogador) == 0) {
                    territoriosBControlados++;
                }
            }
        }
        return territoriosB > 0 && territoriosBControlados == territoriosB;
    }
    
    // Missão 7: Ter 40 tropas somadas
    if (strstr(missao, "40 tropas") != NULL) {
        return somaTotalTropas >= 40;
    }
    
    return 0; // Missão não cumprida
}

/*
 * Função: verificarVitoria
 * Verifica se algum jogador cumpriu sua missão e declara o vencedor
 */
void verificarVitoria(Jogador* jogadores, int numJogadores, Territorio* mapa, int numTerritorios) {
    printf("\n========================================\n");
    printf("    VERIFICACAO DE CONDICOES DE VITORIA\n");
    printf("========================================\n");
    
    int alguemVenceu = 0;
    
    for (int i = 0; i < numJogadores; i++) {
        // Verifica a missão (passagem por referência para verificação)
        int missaoCumprida = verificarMissao(jogadores[i].missao, mapa, numTerritorios, jogadores[i].cor);
        
        if (missaoCumprida) {
            printf("\n*** VITORIA! ***\n");
            printf("O jogador %s (%s) cumpriu sua missao!\n", 
                   jogadores[i].nome, jogadores[i].cor);
            printf("Missao: %s\n", jogadores[i].missao);
            printf("\n*** PARABENS! ***\n");
            alguemVenceu = 1;
        }
    }
    
    if (!alguemVenceu) {
        printf("\nNenhum jogador cumpriu sua missao ainda.\n");
        printf("Continue jogando!\n");
    }
    
    printf("========================================\n");
}

/*
 * Função: cadastrarTerritorios
 * Realiza o cadastro de todos os territórios
 */
void cadastrarTerritorios(Territorio* mapa, int quantidade) {
    printf("\n========================================\n");
    printf("      CADASTRO DE TERRITORIOS\n");
    printf("========================================\n\n");
    
    for (int i = 0; i < quantidade; i++) {
        printf("--- Territorio %d ---\n", i + 1);
        
        printf("Digite o nome do territorio: ");
        fgets(mapa[i].nome, 30, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';
        
        printf("Digite a cor do exercito: ");
        fgets(mapa[i].cor, 10, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';
        
        printf("Digite o numero de tropas: ");
        scanf("%d", &mapa[i].tropas);
        limparBuffer();
        
        printf("\n");
    }
    
    printf("Todos os territorios foram cadastrados!\n");
}

/*
 * Função: exibirTerritorios
 * Exibe informações de todos os territórios
 */
void exibirTerritorios(Territorio* mapa, int quantidade) {
    printf("========================================\n");
    printf("      TERRITORIOS CADASTRADOS\n");
    printf("========================================\n\n");
    
    for (int i = 0; i < quantidade; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("  Nome: %s\n", mapa[i].nome);
        printf("  Cor do Exercito: %s\n", mapa[i].cor);
        printf("  Quantidade de Tropas: %d\n", mapa[i].tropas);
        printf("----------------------------------------\n");
    }
}

/*
 * Função: atacar
 * Simula um ataque entre dois territórios usando dados aleatórios
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
    
    // Simula rolagem de dados (1 a 6)
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;
    
    printf("Dado do Atacante: %d\n", dadoAtacante);
    printf("Dado do Defensor: %d\n", dadoDefensor);
    printf("----------------------------------------\n");
    
    if (dadoAtacante > dadoDefensor) {
        printf("VITORIA DO ATACANTE!\n");
        printf("O territorio %s foi conquistado!\n", defensor->nome);
        
        // Transfere controle e tropas
        strcpy(defensor->cor, atacante->cor);
        int tropasTransferidas = atacante->tropas / 2;
        if (tropasTransferidas < 1) tropasTransferidas = 1;
        
        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;
        
        printf("Tropas transferidas: %d\n", tropasTransferidas);
    } else {
        printf("VITORIA DO DEFENSOR!\n");
        printf("O ataque foi repelido!\n");
        
        if (atacante->tropas > 1) {
            atacante->tropas--;
            printf("O atacante perdeu 1 tropa.\n");
        }
    }
    
    printf("========================================\n");
}

/*
 * Função: realizarAtaque
 * Gerencia a seleção de territórios e execução do ataque
 */
void realizarAtaque(Territorio* mapa, int quantidade) {
    int indiceAtacante, indiceDefensor;
    
    printf("\n========================================\n");
    printf("         SELECAO DE ATAQUE\n");
    printf("========================================\n\n");
    
    printf("Territorios disponiveis:\n");
    for (int i = 0; i < quantidade; i++) {
        printf("%d. %s (%s) - %d tropas\n", 
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    
    printf("\nEscolha o territorio ATACANTE (1-%d): ", quantidade);
    scanf("%d", &indiceAtacante);
    limparBuffer();
    indiceAtacante--;
    
    if (indiceAtacante < 0 || indiceAtacante >= quantidade) {
        printf("Territorio invalido!\n");
        return;
    }
    
    if (mapa[indiceAtacante].tropas < 2) {
        printf("O territorio atacante precisa ter pelo menos 2 tropas!\n");
        return;
    }
    
    printf("Escolha o territorio DEFENSOR (1-%d): ", quantidade);
    scanf("%d", &indiceDefensor);
    limparBuffer();
    indiceDefensor--;
    
    if (indiceDefensor < 0 || indiceDefensor >= quantidade) {
        printf("Territorio invalido!\n");
        return;
    }
    
    if (indiceAtacante == indiceDefensor) {
        printf("Um territorio nao pode atacar a si mesmo!\n");
        return;
    }
    
    if (strcmp(mapa[indiceAtacante].cor, mapa[indiceDefensor].cor) == 0) {
        printf("Nao e possivel atacar um territorio da mesma cor!\n");
        return;
    }
    
    atacar(&mapa[indiceAtacante], &mapa[indiceDefensor]);
    
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
 * Libera toda a memória alocada dinamicamente
 */
void liberarMemoria(Territorio* mapa, Jogador* jogadores, int numJogadores) {
    // Libera as missões de cada jogador
    for (int i = 0; i < numJogadores; i++) {
        if (jogadores[i].missao != NULL) {
            free(jogadores[i].missao);
            jogadores[i].missao = NULL;
        }
    }
    
    // Libera o vetor de jogadores
    if (jogadores != NULL) {
        free(jogadores);
        jogadores = NULL;
    }
    
    // Libera o vetor de territórios
    if (mapa != NULL) {
        free(mapa);
        mapa = NULL;
    }
}

/*
 * Função: limparBuffer
 * Limpa o buffer de entrada
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}