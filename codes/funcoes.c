#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcoes.h"

#define MAX_CRIPTOS 10

// Dados globais
Criptomoeda criptos[MAX_CRIPTOS];
int totalCriptos = 3;

void atualizarCotacoes() {
    srand(time(NULL));
    for (int i = 0; i < totalCriptos; i++) {
        float variacao = ((rand() % 1001) / 10000.0f) * ((rand() % 2) ? 1 : -1);
        criptos[i].cotacao += criptos[i].cotacao * variacao;
        printf("Nova cotacao %s: R$ %.2f\n", criptos[i].nome, criptos[i].cotacao);
    }
}

int loginInvestidor(char *cpf, char *senha) {
    FILE *arq = fopen("investidores.txt", "rb");
    if (!arq) return 0;
    Investidor inv;
    while (fread(&inv, sizeof(Investidor), 1, arq)) {
        if (strcmp(inv.cpf, cpf) == 0 && strcmp(inv.senha, senha) == 0) {
            fclose(arq);
            return 1;
        }
    }
    fclose(arq);
    return 0;
}

int loginAdmin(char *cpf, char *senha) {
    return strcmp(cpf, "admin") == 0 && strcmp(senha, "admin123") == 0;
}

void consultarSaldo(char *cpf) {
    FILE *arq = fopen("investidores.txt", "rb");
    if (!arq) return;
    Investidor inv;
    while (fread(&inv, sizeof(Investidor), 1, arq)) {
        if (strcmp(inv.cpf, cpf) == 0) {
            printf("\n--- SALDO ---\n");
            printf("Nome: %s\n", inv.nome);
            printf("Reais: R$ %.2f\n", inv.saldoReais);
            printf("BTC: %.6f\n", inv.saldoBTC);
            printf("ETH: %.6f\n", inv.saldoETH);
            printf("XRP: %.6f\n", inv.saldoXRP);
        }
    }
    fclose(arq);
}

void consultarExtrato(char *cpf) {
    char nomeArquivo[50];
    sprintf(nomeArquivo, "extrato_%s.txt", cpf);
    FILE *arq = fopen(nomeArquivo, "r");
    if (!arq) {
        printf("Nenhum extrato encontrado.\n");
        return;
    }
    char linha[256];
    while (fgets(linha, sizeof(linha), arq)) {
        printf("%s", linha);
    }
    fclose(arq);
}

void registrarTransacao(char *cpf, char *descricao) {
    char nomeArquivo[50];
    sprintf(nomeArquivo, "extrato_%s.txt", cpf);
    FILE *arq = fopen(nomeArquivo, "a");
    if (arq) {
        fprintf(arq, "%s\n", descricao);
        fclose(arq);
    }
}

void salvarInvestidor(Investidor *inv) {
    FILE *arq = fopen("investidores.txt", "rb+");
    if (!arq) return;
    Investidor temp;
    while (fread(&temp, sizeof(Investidor), 1, arq)) {
        if (strcmp(temp.cpf, inv->cpf) == 0) {
            fseek(arq, -sizeof(Investidor), SEEK_CUR);
            fwrite(inv, sizeof(Investidor), 1, arq);
            break;
        }
    }
    fclose(arq);
}

Investidor buscarInvestidor(char *cpf) {
    FILE *arq = fopen("investidores.txt", "rb");
    Investidor inv;
    while (fread(&inv, sizeof(Investidor), 1, arq)) {
        if (strcmp(inv.cpf, cpf) == 0) break;
    }
    fclose(arq);
    return inv;
}

void depositar(char *cpf) {
    Investidor inv = buscarInvestidor(cpf);
    float valor;
    printf("Digite o valor a depositar: R$ ");
    scanf("%f", &valor);
    inv.saldoReais += valor;
    salvarInvestidor(&inv);
    char descricao[100];
    sprintf(descricao, "Deposito | Reais | R$ %.2f | Saldo: R$ %.2f", valor, inv.saldoReais);
    registrarTransacao(cpf, descricao);
}

void sacar(char *cpf) {
    Investidor inv = buscarInvestidor(cpf);
    char senha[20];
    printf("Digite sua senha: ");
    scanf("%s", senha);
    if (strcmp(inv.senha, senha) != 0) {
        printf("Senha incorreta.\n");
        return;
    }
    float valor;
    printf("Valor do saque: R$ ");
    scanf("%f", &valor);
    if (valor > inv.saldoReais) {
        printf("Saldo insuficiente.\n");
        return;
    }
    inv.saldoReais -= valor;
    salvarInvestidor(&inv);
    char descricao[100];
    sprintf(descricao, "Saque | Reais | R$ %.2f | Saldo: R$ %.2f", valor, inv.saldoReais);
    registrarTransacao(cpf, descricao);
}

void comprarCripto(char *cpf) {
    Investidor inv = buscarInvestidor(cpf);
    char senha[20];
    printf("Digite sua senha: ");
    scanf("%s", senha);
    if (strcmp(inv.senha, senha) != 0) {
        printf("Senha incorreta.\n");
        return;
    }
    printf("1. BTC\n2. ETH\n3. XRP\nEscolha: ");
    int opc;
    scanf("%d", &opc);
    if (opc < 1 || opc > 3) return;
    float valor;
    printf("Valor (em reais) para comprar: ");
    scanf("%f", &valor);

    Criptomoeda *c = &criptos[opc - 1];
    float taxa = valor * c->taxaCompra;
    float valorLiquido = valor - taxa;
    float quantidade = valorLiquido / c->cotacao;

    if (valor > inv.saldoReais) {
        printf("Saldo insuficiente.\n");
        return;
    }
    inv.saldoReais -= valor;
    if (opc == 1) inv.saldoBTC += quantidade;
    else if (opc == 2) inv.saldoETH += quantidade;
    else if (opc == 3) inv.saldoXRP += quantidade;

    salvarInvestidor(&inv);
    char descricao[200];
    sprintf(descricao, "Compra | %s | R$ %.2f | Taxa: R$ %.2f | Qtde: %.6f | Saldo Reais: R$ %.2f", c->nome, valor, taxa, quantidade, inv.saldoReais);
    registrarTransacao(cpf, descricao);
}

void venderCripto(char *cpf) {
    Investidor inv = buscarInvestidor(cpf);
    printf("1. BTC\n2. ETH\n3. XRP\nEscolha: ");
    int opc;
    scanf("%d", &opc);
    if (opc < 1 || opc > 3) return;
    float qtde;
    printf("Quantidade para vender: ");
    scanf("%f", &qtde);

    Criptomoeda *c = &criptos[opc - 1];
    float valorBruto = qtde * c->cotacao;
    float taxa = valorBruto * c->taxaVenda;
    float valorLiquido = valorBruto - taxa;

    if ((opc == 1 && qtde > inv.saldoBTC) ||
        (opc == 2 && qtde > inv.saldoETH) ||
        (opc == 3 && qtde > inv.saldoXRP)) {
        printf("Saldo insuficiente.\n");
        return;
    }

    inv.saldoReais += valorLiquido;
    if (opc == 1) inv.saldoBTC -= qtde;
    else if (opc == 2) inv.saldoETH -= qtde;
    else if (opc == 3) inv.saldoXRP -= qtde;

    salvarInvestidor(&inv);
    char descricao[200];
    sprintf(descricao, "Venda | %s | Qtde: %.6f | Bruto: R$ %.2f | Taxa: R$ %.2f | Liquido: R$ %.2f | Reais: R$ %.2f", c->nome, qtde, valorBruto, taxa, valorLiquido, inv.saldoReais);
    registrarTransacao(cpf, descricao);
}

// Admin
void cadastrarInvestidor() {
    Investidor inv;
    printf("Nome: "); fgets(inv.nome, sizeof(inv.nome), stdin);
    inv.nome[strcspn(inv.nome, "\n")] = 0;
    printf("CPF: "); fgets(inv.cpf, sizeof(inv.cpf), stdin);
    inv.cpf[strcspn(inv.cpf, "\n")] = 0;
    printf("Senha: "); fgets(inv.senha, sizeof(inv.senha), stdin);
    inv.senha[strcspn(inv.senha, "\n")] = 0;
    inv.saldoReais = inv.saldoBTC = inv.saldoETH = inv.saldoXRP = 0;

    FILE *arq = fopen("investidores.txt", "ab");
    fwrite(&inv, sizeof(Investidor), 1, arq);
    fclose(arq);
    printf("Investidor cadastrado.\n");
}

void excluirInvestidor() {
    char cpf[15];
    printf("CPF a excluir: ");
    fgets(cpf, sizeof(cpf), stdin);
    cpf[strcspn(cpf, "\n")] = 0;

    FILE *arq = fopen("investidores.txt", "rb");
    FILE *temp = fopen("temp.txt", "wb");
    Investidor inv;
    int encontrado = 0;

    while (fread(&inv, sizeof(Investidor), 1, arq)) {
        if (strcmp(inv.cpf, cpf) == 0) {
            printf("Nome: %s\nConfirmar exclusao? (s/n): ", inv.nome);
            char op = getchar(); getchar();
            if (op == 's' || op == 'S') {
                encontrado = 1;
                continue;
            }
        }
        fwrite(&inv, sizeof(Investidor), 1, temp);
    }

    fclose(arq);
    fclose(temp);
    remove("investidores.txt");
    rename("temp.txt", "investidores.txt");
    if (encontrado) printf("Investidor excluido.\n");
    else printf("Investidor nao encontrado.\n");
}

void cadastrarCriptomoeda() {
    Criptomoeda nova;
    printf("Nome: "); fgets(nova.nome, sizeof(nova.nome), stdin);
    nova.nome[strcspn(nova.nome, "\n")] = 0;
    printf("Cotacao inicial: "); scanf("%f", &nova.cotacao);
    printf("Taxa compra (ex: 0.02): "); scanf("%f", &nova.taxaCompra);
    printf("Taxa venda (ex: 0.01): "); scanf("%f", &nova.taxaVenda);
    getchar();
    criptos[totalCriptos++] = nova;
    printf("Criptomoeda cadastrada.\n");
}

void excluirCriptomoeda() {
    char nome[20];
    printf("Nome da criptomoeda: "); fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;
    for (int i = 0; i < totalCriptos; i++) {
        if (strcmp(criptos[i].nome, nome) == 0) {
            printf("Confirmar exclusao de %s? (s/n): ", nome);
            char op = getchar(); getchar();
            if (op == 's' || op == 'S') {
                for (int j = i; j < totalCriptos - 1; j++) {
                    criptos[j] = criptos[j + 1];
                }
                totalCriptos--;
                printf("Criptomoeda excluida.\n");
                return;
            }
        }
    }
    printf("Criptomoeda nao encontrada.\n");
}

void consultarSaldoInvestidor() {
    char cpf[15];
    printf("CPF do investidor: "); fgets(cpf, sizeof(cpf), stdin);
    cpf[strcspn(cpf, "\n")] = 0;
    consultarSaldo(cpf);
}

void consultarExtratoInvestidor() {
    char cpf[15];
    printf("CPF do investidor: "); fgets(cpf, sizeof(cpf), stdin);
    cpf[strcspn(cpf, "\n")] = 0;
    consultarExtrato(cpf);
}
