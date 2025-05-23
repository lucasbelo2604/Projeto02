#include <stdio.h>
#include <string.h>
#include "funcoes.h"

int main() {
    int opcao;
    char cpf[15], senha[20];

    while (1) {
        printf("\n=== SISTEMA DE INVESTIMENTOS ===\n");
        printf("1. Login Investidor\n");
        printf("2. Login Administrador\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer

        if (opcao == 0) break;

        printf("CPF: ");
        fgets(cpf, sizeof(cpf), stdin);
        cpf[strcspn(cpf, "\n")] = '\0';

        printf("Senha: ");
        fgets(senha, sizeof(senha), stdin);
        senha[strcspn(senha, "\n")] = '\0';

        if (opcao == 1 && loginInvestidor(cpf, senha)) {
            menuInvestidor(cpf);
        } else if (opcao == 2 && loginAdmin(cpf, senha)) {
            menuAdmin();
        } else {
            printf("CPF ou senha inválidos!\n");
        }
    }

    return 0;
}