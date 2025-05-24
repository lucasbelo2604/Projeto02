#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_INVESTIDORES 100
#define MAX_CRIPTOMOEDAS 10
#define MAX_TRANSACOES 1000

typedef struct {
    char nome[50];
    char cpf[12];
    char senha[20];
    float saldo_reais;
    float saldo_bitcoin;
    float saldo_ethereum;
    float saldo_ripple;
} Investidor;

typedef struct {
    char nome[50];
    float cotacao;
    float taxa_compra;
    float taxa_venda;
} Criptomoeda;

typedef struct {
    char cpf[12];
    char tipo[20]; // "DEPOSITO", "SAQUE", "COMPRA", "VENDA"
    float valor;
    float taxa;
    char data[20];
    char criptomoeda[20]; // Apenas para compra/venda
} Transacao;

// Funções para investidor
int loginInvestidor(Investidor investidores[], int numInvestidores, char cpf[], char senha[]);
void consultarSaldo(Investidor investidor);
void consultarExtrato(Transacao transacoes[], int numTransacoes, char cpf[]);
void depositarReais(Investidor *investidor, Transacao transacoes[], int *numTransacoes);
void sacarReais(Investidor *investidor, Transacao transacoes[], int *numTransacoes, char senha[]);
void comprarCriptomoedas(Investidor *investidor, Criptomoeda criptomoedas[], int numCriptomoedas, Transacao transacoes[], int *numTransacoes, char senha[]);
void venderCriptomoedas(Investidor *investidor, Criptomoeda criptomoedas[], int numCriptomoedas, Transacao transacoes[], int *numTransacoes, char senha[]);
void atualizarCotacoes(Criptomoeda criptomoedas[], int numCriptomoedas);

// Funções para administrador
int loginAdmin(char senha[]);
void cadastrarInvestidor(Investidor investidores[], int *numInvestidores);
void excluirInvestidor(Investidor investidores[], int *numInvestidores);
void cadastrarCriptomoeda(Criptomoeda criptomoedas[], int *numCriptomoedas);
void excluirCriptomoeda(Criptomoeda criptomoedas[], int *numCriptomoedas);
void consultarSaldoInvestidor(Investidor investidores[], int numInvestidores);
void consultarExtratoInvestidor(Transacao transacoes[], int numTransacoes);
void atualizarCotacoesAdmin(Criptomoeda criptomoedas[], int numCriptomoedas);

// Funções auxiliares
void gerarData(char data[]);
void salvarTransacao(Transacao transacoes[], int *numTransacoes, char cpf[], char tipo[], float valor, float taxa, char criptomoeda[]);

#endif