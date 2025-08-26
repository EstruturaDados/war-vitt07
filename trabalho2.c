#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da struct Territorio
// Cada território tem: nome, cor do exército e quantidade de tropas
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {
    // Vetor para armazenar 5 territórios
    struct Territorio territorios[5];

    // Cadastro dos territórios
    for (int i = 0; i < 5; i++) {
        printf("=== Cadastrando Territorios ===\n");

        // Leitura do nome do território
        printf("Nome do territorio:\n ");
        scanf("%s", territorios[i].nome); // lê string com espaços

        // Leitura da cor do exército
        printf("Cor do exercito (ex: azul, verde): \n");
        scanf("%s", territorios[i].cor); // lê string sem espaços

        // Leitura da quantidade de tropas
        printf("Quantidade de tropas:\n ");
        scanf("%d", &territorios[i].tropas);

        printf("\n");
    }

    // Exibição dos dados cadastrados
    printf("\n=== Territórios Cadastrados ===\n");
    for (int i = 0; i < 5; i++) {
        printf("Territorio %d:\n");
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exercito: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
        printf("---------------------------\n");
    }

    return 0;
}
