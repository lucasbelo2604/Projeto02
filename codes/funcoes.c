#include "funcoes.h"
#include <time.h>

// Funções para investidor
int loginInvestidor(Investidor investidores[], int numInvestidores, char cpf[], char senha[]) {
    for (int i = 0; i < numInvestidores; i++) {
        if (strcmp(investidores[i].cpf, cpf) == 0 && strcmp(investidores[i].senha, senha) == 0) {
            return i; // Retorna o índice do investidor
        }
    }
    return -1; // Login falhou
}

void consultarSaldo(Investidor investidor) {
    printf("\nSaldo da Carteira:\n");
    printf("Reais: R$ %.2f\n", investidor.saldo_reais);
    printf("Bitcoin: %.8f\n", investidor.saldo_bitcoin);
    printf("Ethereum: %.8f\n", investidor.saldo_ethereum);
    printf("Ripple: %.8f\n", investidor.saldo_ripple);
}

void consultarExtrato(Transacao transacoes[], int numTransacoes, char cpf[]) {
    printf("\nExtrato de Transacoes:\n");
    for (int i = 0; i < numTransacoes; i++) {
        if (strcmp(transacoes[i].cpf, cpf) == 0) {
            printf("Data: %s | Tipo: %s | Valor: %.2f | Taxa: %.2f", transacoes[i].data, transacoes[i].tipo, transacoes[i].valor, transacoes[i].taxa);
            if (strcmp(transacoes[i].tipo, "COMPRA") == 0 || strcmp(transacoes[i].tipo, "VENDA") == 0) {
                printf(" | Criptomoeda: %s", transacoes[i].criptomoeda);
            }
            printf("\n");
        }
    }
}

void depositarReais(Investidor *investidor, Transacao transacoes[], int *numTransacoes) {
    float valor;
    printf("\nDigite o valor para deposito: ");
    scanf("%f", &valor);
    if (valor > 0) {
        investidor->saldo_reais += valor;
        char data[20];
        gerarData(data);
        salvarTransacao(transacoes, numTransacoes, investidor->cpf, "DEPOSITO", valor, 0, "");
        printf("Deposito realizado com sucesso!\n");
    } else {
        printf("Valor invalido!\n");
    }
}

void sacarReais(Investidor *investidor, Transacao transacoes[], int *numTransacoes, char senha[]) {
    float valor;
    printf("\nDigite o valor para saque: ");
    scanf("%f", &valor);
    if (valor > 0 && valor <= investidor->saldo_reais) {
        printf("Digite sua senha para confirmar: ");
        char senhaDigitada[20];
        scanf("%s", senhaDigitada);
        if (strcmp(senhaDigitada, senha) == 0) {
            investidor->saldo_reais -= valor;
            char data[20];
            gerarData(data);
            salvarTransacao(transacoes, numTransacoes, investidor->cpf, "SAQUE", valor, 0, "");
            printf("Saque realizado com sucesso!\n");
        } else {
            printf("Senha incorreta!\n");
        }
    } else {
        printf("Valor invalido ou saldo insuficiente!\n");
    }
}

void comprarCriptomoedas(Investidor *investidor, Criptomoeda criptomoedas[], int numCriptomoedas, Transacao transacoes[], int *numTransacoes, char senha[]) {
    printf("\nCriptomoedas disponiveis:\n");
    for (int i = 0; i < numCriptomoedas; i++) {
        printf("%d. %s (Cotacao: %.2f | Taxa Compra: %.2f%%)\n", i + 1, criptomoedas[i].nome, criptomoedas[i].cotacao, criptomoedas[i].taxa_compra);
    }
    int opcao;
    printf("Escolha a criptomoeda: ");
    scanf("%d", &opcao);
    if (opcao < 1 || opcao > numCriptomoedas) {
        printf("Opcao invalida!\n");
        return;
    }
    Criptomoeda *cripto = &criptomoedas[opcao - 1];
    float valor;
    printf("Digite o valor em reais para comprar %s: ", cripto->nome);
    scanf("%f", &valor);
    if (valor <= 0 || valor > investidor->saldo_reais) {
        printf("Valor invalido ou saldo insuficiente!\n");
        return;
    }
    printf("Digite sua senha para confirmar: ");
    char senhaDigitada[20];
    scanf("%s", senhaDigitada);
    if (strcmp(senhaDigitada, senha) != 0) {
        printf("Senha incorreta!\n");
        return;
    }
    float taxa = valor * (cripto->taxa_compra / 100);
    float valorCompra = valor - taxa;
    float quantidade = valorCompra / cripto->cotacao;
    printf("\nResumo da Compra:\n");
    printf("Criptomoeda: %s\n", cripto->nome);
    printf("Valor: R$ %.2f\n", valor);
    printf("Taxa: R$ %.2f (%.2f%%)\n", taxa, cripto->taxa_compra);
    printf("Quantidade: %.8f %s\n", quantidade, cripto->nome);
    printf("Confirmar compra? (s/n): ");
    char confirmacao;
    scanf(" %c", &confirmacao);
    if (confirmacao == 's' || confirmacao == 'S') {
        investidor->saldo_reais -= valor;
        if (strcmp(cripto->nome, "Bitcoin") == 0) {
            investidor->saldo_bitcoin += quantidade;
        } else if (strcmp(cripto->nome, "Ethereum") == 0) {
            investidor->saldo_ethereum += quantidade;
        } else if (strcmp(cripto->nome, "Ripple") == 0) {
            investidor->saldo_ripple += quantidade;
        }
        char data[20];
        gerarData(data);
        salvarTransacao(transacoes, numTransacoes, investidor->cpf, "COMPRA", valor, taxa, cripto->nome);
        printf("Compra realizada com sucesso!\n");
    } else {
        printf("Compra cancelada!\n");
    }
}

void venderCriptomoedas(Investidor *investidor, Criptomoeda criptomoedas[], int numCriptomoedas, Transacao transacoes[], int *numTransacoes, char senha[]) {
    printf("\nCriptomoedas disponiveis:\n");
    for (int i = 0; i < numCriptomoedas; i++) {
        printf("%d. %s (Cotacao: %.2f | Taxa Venda: %.2f%%)\n", i + 1, criptomoedas[i].nome, criptomoedas[i].cotacao, criptomoedas[i].taxa_venda);
    }
    int opcao;
    printf("Escolha a criptomoeda: ");
    scanf("%d", &opcao);
    if (opcao < 1 || opcao > numCriptomoedas) {
        printf("Opcao invalida!\n");
        return;
    }
    Criptomoeda *cripto = &criptomoedas[opcao - 1];
    float quantidade;
    printf("Digite a quantidade de %s para vender: ", cripto->nome);
    scanf("%f", &quantidade);
    float saldo;
    if (strcmp(cripto->nome, "Bitcoin") == 0) {
        saldo = investidor->saldo_bitcoin;
    } else if (strcmp(cripto->nome, "Ethereum") == 0) {
        saldo = investidor->saldo_ethereum;
    } else if (strcmp(cripto->nome, "Ripple") == 0) {
        saldo = investidor->saldo_ripple;
    } else {
        printf("Criptomoeda invalida!\n");
        return;
    }
    if (quantidade <= 0 || quantidade > saldo) {
        printf("Quantidade invalida ou saldo insuficiente!\n");
        return;
    }
    printf("Digite sua senha para confirmar: ");
    char senhaDigitada[20];
    scanf("%s", senhaDigitada);
    if (strcmp(senhaDigitada, senha) != 0) {
        printf("Senha incorreta!\n");
        return;
    }
    float valorVenda = quantidade * cripto->cotacao;
    float taxa = valorVenda * (cripto->taxa_venda / 100);
    float valorLiquido = valorVenda - taxa;
    printf("\nResumo da Venda:\n");
    printf("Criptomoeda: %s\n", cripto->nome);
    printf("Quantidade: %.8f\n", quantidade);
    printf("Valor de Venda: R$ %.2f\n", valorVenda);
    printf("Taxa: R$ %.2f (%.2f%%)\n", taxa, cripto->taxa_venda);
    printf("Valor Liquido: R$ %.2f\n", valorLiquido);
    printf("Confirmar venda? (s/n): ");
    char confirmacao;
    scanf(" %c", &confirmacao);
    if (confirmacao == 's' || confirmacao == 'S') {
        investidor->saldo_reais += valorLiquido;
        if (strcmp(cripto->nome, "Bitcoin") == 0) {
            investidor->saldo_bitcoin -= quantidade;
        } else if (strcmp(cripto->nome, "Ethereum") == 0) {
            investidor->saldo_ethereum -= quantidade;
        } else if (strcmp(cripto->nome, "Ripple") == 0) {
            investidor->saldo_ripple -= quantidade;
        }
        char data[20];
        gerarData(data);
        salvarTransacao(transacoes, numTransacoes, investidor->cpf, "VENDA", valorVenda, taxa, cripto->nome);
        printf("Venda realizada com sucesso!\n");
    } else {
        printf("Venda cancelada!\n");
    }
}

void atualizarCotacoes(Criptomoeda criptomoedas[], int numCriptomoedas) {
    srand(time(NULL));
    for (int i = 0; i < numCriptomoedas; i++) {
        float variacao = ((rand() % 11) - 5) / 100.0; // Variação entre -5% e +5%
        criptomoedas[i].cotacao *= (1 + variacao);
        printf("Nova cotacao de %s: %.2f (Variacao: %.2f%%)\n", criptomoedas[i].nome, criptomoedas[i].cotacao, variacao * 100);
    }
}

// Funções para administrador
int loginAdmin(char senha[]) {
    char senhaAdmin[] = "admin123";
    return strcmp(senha, senhaAdmin) == 0;
}

void cadastrarInvestidor(Investidor investidores[], int *numInvestidores) {
    if (*numInvestidores >= MAX_INVESTIDORES) {
        printf("Limite de investidores atingido!\n");
        return;
    }
    Investidor novo;
    printf("\nDigite o nome do investidor: ");
    scanf("%s", novo.nome);
    printf("Digite o CPF (apenas numeros): ");
    scanf("%s", novo.cpf);
    printf("Digite a senha: ");
    scanf("%s", novo.senha);
    novo.saldo_reais = 0;
    novo.saldo_bitcoin = 0;
    novo.saldo_ethereum = 0;
    novo.saldo_ripple = 0;
    investidores[*numInvestidores] = novo;
    (*numInvestidores)++;
    printf("Investidor cadastrado com sucesso!\n");
}

void excluirInvestidor(Investidor investidores[], int *numInvestidores) {
    char cpf[12];
    printf("\nDigite o CPF do investidor a ser excluido: ");
    scanf("%s", cpf);
    int encontrado = -1;
    for (int i = 0; i < *numInvestidores; i++) {
        if (strcmp(investidores[i].cpf, cpf) == 0) {
            encontrado = i;
            break;
        }
    }
    if (encontrado == -1) {
        printf("Investidor nao encontrado!\n");
        return;
    }
    printf("Investidor encontrado:\n");
    printf("Nome: %s\n", investidores[encontrado].nome);
    printf("CPF: %s\n", investidores[encontrado].cpf);
    printf("Confirmar exclusao? (s/n): ");
    char confirmacao;
    scanf(" %c", &confirmacao);
    if (confirmacao == 's' || confirmacao == 'S') {
        for (int i = encontrado; i < *numInvestidores - 1; i++) {
            investidores[i] = investidores[i + 1];
        }
        (*numInvestidores)--;
        printf("Investidor excluido com sucesso!\n");
    } else {
        printf("Exclusao cancelada!\n");
    }
}

void cadastrarCriptomoeda(Criptomoeda criptomoedas[], int *numCriptomoedas) {
    if (*numCriptomoedas >= MAX_CRIPTOMOEDAS) {
        printf("Limite de criptomoedas atingido!\n");
        return;
    }
    Criptomoeda nova;
    printf("\nDigite o nome da criptomoeda: ");
    scanf("%s", nova.nome);
    printf("Digite a cotacao inicial: ");
    scanf("%f", &nova.cotacao);
    printf("Digite a taxa de compra (%%): ");
    scanf("%f", &nova.taxa_compra);
    printf("Digite a taxa de venda (%%): ");
    scanf("%f", &nova.taxa_venda);
    criptomoedas[*numCriptomoedas] = nova;
    (*numCriptomoedas)++;
    printf("Criptomoeda cadastrada com sucesso!\n");
}

void excluirCriptomoeda(Criptomoeda criptomoedas[], int *numCriptomoedas) {
    char nome[50];
    printf("\nDigite o nome da criptomoeda a ser excluida: ");
    scanf("%s", nome);
    int encontrado = -1;
    for (int i = 0; i < *numCriptomoedas; i++) {
        if (strcmp(criptomoedas[i].nome, nome) == 0) {
            encontrado = i;
            break;
        }
    }
    if (encontrado == -1) {
        printf("Criptomoeda nao encontrada!\n");
        return;
    }
    printf("Criptomoeda encontrada:\n");
    printf("Nome: %s\n", criptomoedas[encontrado].nome);
    printf("Cotacao: %.2f\n", criptomoedas[encontrado].cotacao);
    printf("Taxa de Compra: %.2f%%\n", criptomoedas[encontrado].taxa_compra);
    printf("Taxa de Venda: %.2f%%\n", criptomoedas[encontrado].taxa_venda);
    printf("Confirmar exclusao? (s/n): ");
    char confirmacao;
    scanf(" %c", &confirmacao);
    if (confirmacao == 's' || confirmacao == 'S') {
        for (int i = encontrado; i < *numCriptomoedas - 1; i++) {
            criptomoedas[i] = criptomoedas[i + 1];
        }
        (*numCriptomoedas)--;
        printf("Criptomoeda excluida com sucesso!\n");
    } else {
        printf("Exclusao cancelada!\n");
    }
}

void consultarSaldoInvestidor(Investidor investidores[], int numInvestidores) {
    char cpf[12];
    printf("\nDigite o CPF do investidor: ");
    scanf("%s", cpf);
    int encontrado = -1;
    for (int i = 0; i < numInvestidores; i++) {
        if (strcmp(investidores[i].cpf, cpf) == 0) {
            encontrado = i;
            break;
        }
    }
    if (encontrado == -1) {
        printf("Investidor nao encontrado!\n");
        return;
    }
    consultarSaldo(investidores[encontrado]);
}

void consultarExtratoInvestidor(Transacao transacoes[], int numTransacoes) {
    char cpf[12];
    printf("\nDigite o CPF do investidor: ");
    scanf("%s", cpf);
    consultarExtrato(transacoes, numTransacoes, cpf);
}

void atualizarCotacoesAdmin(Criptomoeda criptomoedas[], int numCriptomoedas) {
    atualizarCotacoes(criptomoedas, numCriptomoedas);
}

// Funções auxiliares
void gerarData(char data[]) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(data, "%02d/%02d/%04d %02d:%02d:%02d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

void salvarTransacao(Transacao transacoes[], int *numTransacoes, char cpf[], char tipo[], float valor, float taxa, char criptomoeda[]) {
    if (*numTransacoes >= MAX_TRANSACOES) {
        printf("Limite de transacoes atingido!\n");
        return;
    }
    Transacao nova;
    strcpy(nova.cpf, cpf);
    strcpy(nova.tipo, tipo);
    nova.valor = valor;
    nova.taxa = taxa;
    strcpy(nova.criptomoeda, criptomoeda);
    gerarData(nova.data);
    transacoes[*numTransacoes] = nova;
    (*numTransacoes)++;

    // Salvar em arquivo
    FILE *arquivo = fopen("extrato.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    fprintf(arquivo, "CPF: %s | Data: %s | Tipo: %s | Valor: %.2f | Taxa: %.2f", cpf, nova.data, tipo, valor, taxa);
    if (strcmp(tipo, "COMPRA") == 0 || strcmp(tipo, "VENDA") == 0) {
        fprintf(arquivo, " | Criptomoeda: %s", criptomoeda);
    }
    fprintf(arquivo, "\n");
    fclose(arquivo);
}