#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcoes.h"

// Simulação de base de dados
#define MAX_INV 100
#define MAX_CRIPTOS 10

Investidor investidores[MAX_INV];
int totalInvestidores = 0;

Criptomoeda criptos[MAX_CRIPTOS] = {
    {"Bitcoin", 300000.0, 0.02, 0.015},
    {"Ethereum", 20000.0, 0.015, 0.012},
    {"Ripple", 1.50, 0.01, 0.008}
};
int totalCriptos = 3;

// Funções de login
int loginInvestidor(char *cpf, char *senha) {
    FILE *arq = fopen("investidores.txt", "r");
    Investidor temp;
    while (fread(&temp, sizeof(Investidor), 1, arq)) {
        if (strcmp(temp.cpf, cpf) == 0 && strcmp(temp.senha, senha) == 0) {
            fclose(arq);
            return 1;
        }
    }
    fclose(arq);
    return 0;
}

int loginAdmin(char *cpf, char *senha) {
    return strcmp(cpf, "admin") == 0 && strcmp(senha, "admin123");
}

// Menus
void menuInvestidor(char *cpf) {
    int op;
    do {
        printf("\n--- MENU INVESTIDOR ---\n");
        printf("1. Consultar Saldo\n");
        printf("2. Consultar Extrato\n");
        printf("3. Depositar\n");
        printf("4. Sacar\n");
        printf("5. Comprar Criptomoeda\n");
        printf("6. Vender Criptomoeda\n");
        printf("7. Atualizar Cotações\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);
        getchar();

        switch (op) {
            case 1: consultarSaldo(cpf); break;
            case 2: consultarExtrato(cpf); break;
            case 3: depositar(cpf); break;
            case 4: sacar(cpf); break;
            case 5: comprarCripto(cpf); break;
            case 6: venderCripto(cpf); break;
            case 7: atualizarCotacoes(); break;
        }
    } while (op != 0);
}

void menuAdmin() {
    int op;
    do {
        printf("\n--- MENU ADMIN ---\n");
        printf("1. Cadastrar Investidor\n");
        printf("2. Excluir Investidor\n");
        printf("3. Cadastrar Criptomoeda\n");
        printf("4. Excluir Criptomoeda\n");
        printf("5. Consultar Saldo de Investidor\n");
        printf("6. Consultar Extrato de Investidor\n");
        printf("7. Atualizar Cotações\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);
        getchar();

        switch (op) {
            case 1: cadastrarInvestidor(); break;
            case 2: excluirInvestidor(); break;
            case 3: cadastrarCriptomoeda(); break;
            case 4: excluirCriptomoeda(); break;
            case 5: consultarSaldoInvestidor(); break;
            case 6: consultarExtratoInvestidor(); break;
            case 7: atualizarCotacoes(); break;
        }
    } while (op != 0);
}

// Funções principais (implementações básicas de cada uma)
void consultarSaldo(char *cpf) {
    // Carrega investidor e mostra saldos
    printf(">>> Consultar saldo - Em desenvolvimento\n");
}

void consultarExtrato(char *cpf) {
    // Lê arquivo extrato_cpf.txt
    printf(">>> Consultar extrato - Em desenvolvimento\n");
}

void depositar(char *cpf) {
    printf(">>> Depositar - Em desenvolvimento\n");
}

void sacar(char *cpf) {
    printf(">>> Sacar - Em desenvolvimento\n");
}

void comprarCripto(char *cpf) {
    printf(">>> Comprar Cripto - Em desenvolvimento\n");
}

void venderCripto(char *cpf) {
    printf(">>> Vender Cripto - Em desenvolvimento\n");
}

void atualizarCotacoes() {
    srand(time(NULL));
    for (int i = 0; i < totalCriptos; i++) {
        float variacao = ((rand() % 1001) / 10000.0f) * ((rand() % 2) ? 1 : -1);
        criptos[i].cotacao += criptos[i].cotacao * variacao;
        printf("Nova cotação %s: R$ %.2f\n", criptos[i].nome, criptos[i].cotacao);
    }
}

// ADMIN
void cadastrarInvestidor() {
    printf(">>> Cadastrar investidor - Em desenvolvimento\n");
}

void excluirInvestidor() {
    printf(">>> Excluir investidor - Em desenvolvimento\n");
}

void cadastrarCriptomoeda() {
    printf(">>> Cadastrar criptomoeda - Em desenvolvimento\n");
}

void excluirCriptomoeda() {
    printf(">>> Excluir criptomoeda - Em desenvolvimento\n");
}

void consultarSaldoInvestidor() {
    printf(">>> Consultar saldo de investidor - Em desenvolvimento\n");
}

void consultarExtratoInvestidor() {
    printf(">>> Consultar extrato de investidor - Em desenvolvimento\n");
}