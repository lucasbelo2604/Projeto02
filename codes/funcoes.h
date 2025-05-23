#ifndef FUNCOES_H
#define FUNCOES_H

// Estruturas
typedef struct {
    char nome[100];
    char cpf[15];
    char senha[20];
    float saldoReais;
    float saldoBTC;
    float saldoETH;
    float saldoXRP;
} Investidor;

typedef struct {
    char nome[20];
    float cotacao;
    float taxaCompra;
    float taxaVenda;
} Criptomoeda;

// Funções do sistema
int loginInvestidor(char *cpf, char *senha);
int loginAdmin(char *cpf, char *senha);

// Investidor
void menuInvestidor(char *cpf);
void consultarSaldo(char *cpf);
void consultarExtrato(char *cpf);
void depositar(char *cpf);
void sacar(char *cpf);
void comprarCripto(char *cpf);
void venderCripto(char *cpf);
void atualizarCotacoes();

// Admin
void menuAdmin();
void cadastrarInvestidor();
void excluirInvestidor();
void cadastrarCriptomoeda();
void excluirCriptomoeda();
void consultarSaldoInvestidor();
void consultarExtratoInvestidor();

#endif