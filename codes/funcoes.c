
#include "funcoes.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Variáveis globais (serão movidas para o arquivo principal posteriormente)
char nome[50] = "Luis, Lucas e Leo";
char cpf[15] = "12345678910";
int senha = 999999;
float saldo_real = 0;
float saldo_bitcoin = 0;
float saldo_ethe = 0;
float saldo_ripple = 0;
float cotacao_bit = 416328.72;
float cotacao_ethe = 15201.58;
float cotacao_ripple = 2.99;

void consultar_saldo() {
    int senha_usuario;
    printf("Por favor, informe a sua senha: ");
    scanf("%d", &senha_usuario);
    
    if (senha_usuario == senha) {
        printf("\nNome: %s\n", nome);
        printf("CPF: 123.456.789-10\n\n");
        printf("Saldo em Real: %.2f\n", saldo_real);
        printf("Saldo em Bitcoin: %.4f\n", saldo_bitcoin);
        printf("Saldo em Ethereum: %.2f\n", saldo_ethe);
        printf("Saldo em Ripple: %.2f\n", saldo_ripple);
    } else {
        printf("Senha ou CPF invalidos\n");
    }
}

void consultar_extrato() {
    printf("\nExtrato de Transações:\n");
    printf("(Funcionalidade completa será implementada depois)\n");
}

void depositar() {
    float deposito;
    printf("Qual o valor do deposito em real? R$");
    scanf("%f", &deposito);
    
    saldo_real += deposito;
    printf("Seu novo saldo é: %.2f \n", saldo_real);
    
    printf("(Registro no extrato será implementado depois)\n");
}

void sacar() {
    float saque;
    printf("Qual o valor do saque em real? R$");
    scanf("%f", &saque);
    
    if (saldo_real - saque >= 0) {
        saldo_real -= saque;
        printf("Seu novo saldo é: R$%.2f \n", saldo_real);
        printf("(Registro no extrato será implementado depois)\n");
    } else {
        printf("\nOperação invalida, seu saldo não é suficiente\n");
        printf("Seu saldo continua sendo: R$%.2f \n", saldo_real);
    }
}

void menu() {
    printf("\n1. Consulta do Saldo\n");
    printf("2. Consulta de Extrato\n");
    printf("3. Depositar\n");
    printf("4. Sacar\n");
    printf("0. Sair\n");
}

bool voltar() {
    char opcao[10];
    printf("Deseja voltar para o menu (sim/não): ");
    scanf("%s", opcao);
    
    if (strcmp(opcao, "não") == 0 || strcmp(opcao, "nao") == 0) {
        printf("Saindo, obrigado!\n");
        return true;
    }
    return false;
}