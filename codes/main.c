#include "funcoes.h"

int main() {
    Investidor investidores[MAX_INVESTIDORES];
    Criptomoeda criptomoedas[MAX_CRIPTOMOEDAS] = {
        {"Bitcoin", 200000.0, 1.0, 1.0},
        {"Ethereum", 10000.0, 0.8, 0.8},
        {"Ripple", 2.0, 0.5, 0.5}
    };
    Transacao transacoes[MAX_TRANSACOES];
    int numInvestidores = 0;
    int numCriptomoedas = 3;
    int numTransacoes = 0;

    int opcao;
    do {
        printf("\nSistema de Investimentos\n");
        printf("1. Login Investidor\n");
        printf("2. Login Administrador\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            char cpf[12], senha[20];
            printf("\nLogin Investidor\n");
            printf("CPF: ");
            scanf("%s", cpf);
            printf("Senha: ");
            scanf("%s", senha);
            int indice = loginInvestidor(investidores, numInvestidores, cpf, senha);
            if (indice != -1) {
                printf("\nBem-vindo, %s!\n", investidores[indice].nome);
                int opcaoInvestidor;
                do {
                    printf("\nMenu Investidor\n");
                    printf("1. Consultar Saldo\n");
                    printf("2. Consultar Extrato\n");
                    printf("3. Depositar Reais\n");
                    printf("4. Sacar Reais\n");
                    printf("5. Comprar Criptomoedas\n");
                    printf("6. Vender Criptomoedas\n");
                    printf("7. Atualizar Cotacoes\n");
                    printf("0. Logout\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &opcaoInvestidor);

                    switch (opcaoInvestidor) {
                        case 1:
                            consultarSaldo(investidores[indice]);
                            break;
                        case 2:
                            consultarExtrato(transacoes, numTransacoes, investidores[indice].cpf);
                            break;
                        case 3:
                            depositarReais(&investidores[indice], transacoes, &numTransacoes);
                            break;
                        case 4:
                            sacarReais(&investidores[indice], transacoes, &numTransacoes, investidores[indice].senha);
                            break;
                        case 5:
                            comprarCriptomoedas(&investidores[indice], criptomoedas, numCriptomoedas, transacoes, &numTransacoes, investidores[indice].senha);
                            break;
                        case 6:
                            venderCriptomoedas(&investidores[indice], criptomoedas, numCriptomoedas, transacoes, &numTransacoes, investidores[indice].senha);
                            break;
                        case 7:
                            atualizarCotacoes(criptomoedas, numCriptomoedas);
                            break;
                        case 0:
                            printf("Logout realizado!\n");
                            break;
                        default:
                            printf("Opcao invalida!\n");
                    }
                } while (opcaoInvestidor != 0);
            } else {
                printf("CPF ou senha incorretos!\n");
            }
        } else if (opcao == 2) {
            char senha[20];
            printf("\nLogin Administrador\n");
            printf("Senha: ");
            scanf("%s", senha);
            if (loginAdmin(senha)) {
                printf("\nBem-vindo, Administrador!\n");
                int opcaoAdmin;
                do {
                    printf("\nMenu Administrador\n");
                    printf("1. Cadastrar Investidor\n");
                    printf("2. Excluir Investidor\n");
                    printf("3. Cadastrar Criptomoeda\n");
                    printf("4. Excluir Criptomoeda\n");
                    printf("5. Consultar Saldo de Investidor\n");
                    printf("6. Consultar Extrato de Investidor\n");
                    printf("7. Atualizar Cotacoes\n");
                    printf("0. Logout\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &opcaoAdmin);

                    switch (opcaoAdmin) {
                        case 1:
                            cadastrarInvestidor(investidores, &numInvestidores);
                            break;
                        case 2:
                            excluirInvestidor(investidores, &numInvestidores);
                            break;
                        case 3:
                            cadastrarCriptomoeda(criptomoedas, &numCriptomoedas);
                            break;
                        case 4:
                            excluirCriptomoeda(criptomoedas, &numCriptomoedas);
                            break;
                        case 5:
                            consultarSaldoInvestidor(investidores, numInvestidores);
                            break;
                        case 6:
                            consultarExtratoInvestidor(transacoes, numTransacoes);
                            break;
                        case 7:
                            atualizarCotacoesAdmin(criptomoedas, numCriptomoedas);
                            break;
                        case 0:
                            printf("Logout realizado!\n");
                            break;
                        default:
                            printf("Opcao invalida!\n");
                    }
                } while (opcaoAdmin != 0);
            } else {
                printf("Senha incorreta!\n");
            }
        } else if (opcao != 0) {
            printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    printf("Sistema encerrado.\n");
    return 0;
}