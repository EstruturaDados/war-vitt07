#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// =============================
// ESTRUTURA PRINCIPAL
// =============================
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// =============================
// FUNÇÃO: Cadastro de Territórios
// =============================
void cadastrarTerritorios(Territorio* mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("\n=== Cadastro do Território %d ===\n", i + 1);

        printf("Nome do território: ");
        getchar(); // limpar buffer
        fgets((mapa + i)->nome, sizeof((mapa + i)->nome), stdin);
        (mapa + i)->nome[strcspn((mapa + i)->nome, "\n")] = '\0';

        printf("Cor do exército (ex: azul, vermelho): ");
        scanf("%s", (mapa + i)->cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &((mapa + i)->tropas));
    }
}

// =============================
// FUNÇÃO: Exibir Mapa
// =============================
void exibirMapa(Territorio* mapa, int n) {
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < n; i++) {
        printf("%d. %s | Cor: %s | Tropas: %d\n",
               i + 1, (mapa + i)->nome, (mapa + i)->cor, (mapa + i)->tropas);
    }
    printf("---------------------------------\n");
}

// =============================
// FUNÇÃO: Ataque entre territórios
// =============================
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n--- Batalha entre %s (%s) e %s (%s) ---\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("❌ Um território não pode atacar outro da mesma cor!\n");
        return;
    }

    if (atacante->tropas <= 1) {
        printf("❌ O atacante precisa ter mais de 1 tropa!\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("🎲 Dado do atacante: %d\n", dadoAtacante);
    printf("🎲 Dado do defensor: %d\n", dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("✅ O atacante venceu a batalha!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas /= 2;
        printf("O território %s agora pertence à cor %s!\n", defensor->nome, defensor->cor);
    } else {
        printf("❌ O defensor resistiu ao ataque!\n");
        atacante->tropas -= 1;
    }
}

// =============================
// FUNÇÃO: Atribuir missão ao jogador
// =============================
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}

// =============================
// FUNÇÃO: Exibir missão (uma vez)
// =============================
void exibirMissao(const char* missao, int jogador) {
    printf("\n🎯 Missão do Jogador %d: %s\n", jogador, missao);
}

// =============================
// FUNÇÃO: Verificar se a missão foi cumprida
// =============================
// (Lógica simples inicial — pode ser expandida)
int verificarMissao(const char* missao, Territorio* mapa, int tamanho, const char* corJogador) {
    int conquistados = 0;
    int vermelhos = 0;

    for (int i = 0; i < tamanho; i++) {
        if (strcmp(mapa[i].cor, corJogador) == 0)
            conquistados++;
        if (strcmp(mapa[i].cor, "vermelho") == 0)
            vermelhos++;
    }

    // Missões simples de exemplo
    if (strstr(missao, "3 territorios") && conquistados >= 3)
        return 1;
    if (strstr(missao, "eliminar vermelho") && vermelhos == 0)
        return 1;

    return 0;
}

// =============================
// FUNÇÃO: Liberação de memória
// =============================
void liberarMemoria(Territorio* mapa, char* missao1, char* missao2) {
    free(mapa);
    free(missao1);
    free(missao2);
    printf("\nMemória liberada com sucesso!\n");
}

// =============================
// FUNÇÃO PRINCIPAL
// =============================
int main() {
    srand(time(NULL));

    int n;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &n);

    // Alocação dinâmica dos territórios
    Territorio* mapa = (Territorio*) calloc(n, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, n);

    // Vetor de missões pré-definidas
    char* missoes[] = {
        "Conquistar 3 territorios seguidos",
        "Eliminar todas as tropas da cor vermelha",
        "Conquistar metade do mapa",
        "Defender todos os seus territorios por 3 turnos",
        "Dominar todos os territorios azuis"
    };
    int totalMissoes = 5;

    // Alocação dinâmica das missões dos jogadores
    char* missaoJogador1 = (char*) malloc(100 * sizeof(char));
    char* missaoJogador2 = (char*) malloc(100 * sizeof(char));

    atribuirMissao(missaoJogador1, missoes, totalMissoes);
    atribuirMissao(missaoJogador2, missoes, totalMissoes);

    // Exibir missões no início
    exibirMissao(missaoJogador1, 1);
    exibirMissao(missaoJogador2, 2);

    // Jogo principal
    int turno = 1;
    int vencedor = 0;
    int opcao;

    while (!vencedor) {
        printf("\n==== TURNO DO JOGADOR %d ====\n", turno);
        exibirMapa(mapa, n);

        printf("1. Atacar território\n");
        printf("2. Passar turno\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int a, d;
            printf("Escolha o território atacante: ");
            scanf("%d", &a);
            printf("Escolha o território defensor: ");
            scanf("%d", &d);

            if (a < 1 || a > n || d < 1 || d > n) {
                printf("❌ Escolha inválida!\n");
                continue;
            }

            atacar(&mapa[a - 1], &mapa[d - 1]);
        }

        // Verifica missão após cada turno
        if (turno == 1 && verificarMissao(missaoJogador1, mapa, n, "azul")) {
            printf("\n🏆 Jogador 1 venceu! Missão cumprida: %s\n", missaoJogador1);
            vencedor = 1;
        } else if (turno == 2 && verificarMissao(missaoJogador2, mapa, n, "vermelho")) {
            printf("\n🏆 Jogador 2 venceu! Missão cumprida: %s\n", missaoJogador2);
            vencedor = 1;
        }

        // Alterna turno
        turno = (turno == 1) ? 2 : 1;
    }

    liberarMemoria(mapa, missaoJogador1, missaoJogador2);
    return 0;
}
