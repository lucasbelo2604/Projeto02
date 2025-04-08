
#include "funcoes.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

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

void comprar_cripto() {
    int senha_usuario;
    printf("Por favor, informe a sua senha: ");
    scanf("%d", &senha_usuario);
    
    if (senha_usuario == senha) {
        printf("\nCotação Bitcoin: R$%.2f\n", cotacao_bit);
        printf("Cotação Ethereum: R$%.2f\n", cotacao_ethe);
        printf("Cotação Ripple: R$%.2f\n", cotacao_ripple);
        
        char escolha[20];
        float compra;
        
        printf("\nQual criptomoeda deseja comprar (Bitcoin/Ethereum/Ripple): ");
        scanf("%s", escolha);
        
        // Normaliza a entrada para minúsculas
        for (int i = 0; escolha[i]; i++) {
            escolha[i] = tolower(escolha[i]);
        }
        
        printf("Quanto deseja comprar em R$? ");
        scanf("%f", &compra);
        
        if (compra > saldo_real) {
            printf("Seu saldo em real é insuficiente!\n");
            return;
        }
        
        if (strcmp(escolha, "bitcoin") == 0) {
            float quantidade = compra / cotacao_bit;
            saldo_real -= compra;
            saldo_bitcoin += quantidade * 0.98; // Taxa de 2%
            printf("Compra realizada! Você adquiriu %.6f BTC\n", quantidade * 0.98);
        }
        else if (strcmp(escolha, "ethereum") == 0) {
            float quantidade = compra / cotacao_ethe;
            saldo_real -= compra;
            saldo_ethe += quantidade * 0.99; // Taxa de 1%
            printf("Compra realizada! Você adquiriu %.4f ETH\n", quantidade * 0.99);
        }
        else if (strcmp(escolha, "ripple") == 0) {
            float quantidade = compra / cotacao_ripple;
            saldo_real -= compra;
            saldo_ripple += quantidade * 0.99; // Taxa de 1%
            printf("Compra realizada! Você adquiriu %.2f XRP\n", quantidade * 0.99);
        }
        else {
            printf("Criptomoeda inválida!\n");
        }
        
        printf("(Registro no extrato será implementado depois)\n");
    } else {
        printf("Senha inválida!\n");
    }
}

void vender_cripto() {
    int senha_usuario;
    printf("Por favor, informe a sua senha: ");
    scanf("%d", &senha_usuario);
    
    if (senha_usuario == senha) {
        printf("\nCotação Bitcoin: R$%.2f\n", cotacao_bit);
        printf("Cotação Ethereum: R$%.2f\n", cotacao_ethe);
        printf("Cotação Ripple: R$%.2f\n", cotacao_ripple);
        
        char escolha[20];
        float venda;
        
        printf("\nQual criptomoeda deseja vender (Bitcoin/Ethereum/Ripple): ");
        scanf("%s", escolha);
        
        for (int i = 0; escolha[i]; i++) {
            escolha[i] = tolower(escolha[i]);
        }
        
        printf("Quanto deseja vender? ");
        scanf("%f", &venda);
        
        if (strcmp(escolha, "bitcoin") == 0) {
            if (venda > saldo_bitcoin) {
                printf("Saldo insuficiente de Bitcoin!\n");
                return;
            }
            float valor_recebido = venda * cotacao_bit * 0.97; // Taxa de 3%
            saldo_bitcoin -= venda;
            saldo_real += valor_recebido;
            printf("Venda realizada! Você recebeu R$%.2f\n", valor_recebido);
        }
        else if (strcmp(escolha, "ethereum") == 0) {
            if (venda > saldo_ethe) {
                printf("Saldo insuficiente de Ethereum!\n");
                return;
            }
            float valor_recebido = venda * cotacao_ethe * 0.98; // Taxa de 2%
            saldo_ethe -= venda;
            saldo_real += valor_recebido;
            printf("Venda realizada! Você recebeu R$%.2f\n", valor_recebido);
        }
        else if (strcmp(escolha, "ripple") == 0) {
            if (venda > saldo_ripple) {
                printf("Saldo insuficiente de Ripple!\n");
                return;
            }
            float valor_recebido = venda * cotacao_ripple * 0.99; // Taxa de 1%
            saldo_ripple -= venda;
            saldo_real += valor_recebido;
            printf("Venda realizada! Você recebeu R$%.2f\n", valor_recebido);
        }
        else {
            printf("Criptomoeda inválida!\n");
        }
        
        printf("(Registro no extrato será implementado depois)\n");
    } else {
        printf("Senha inválida!\n");
    }
}



void menu() {
    printf("\n1. Consulta do Saldo\n");
    printf("2. Consulta de Extrato\n");
    printf("3. Depositar\n");
    printf("4. Sacar\n");
    printf("5. Comprar Criptomoedas\n");
    printf("6. Vender Criptomoedas\n");
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