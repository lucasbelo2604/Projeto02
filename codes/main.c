#include "funcoes.h"
#include <string.h>
#include <ctype.h>

int main() {
    srand(time(NULL));
    ler_arquivo();

    int perfil;
    printf("Escolha o perfil de acesso:\n");
    printf("1. Investidor\n");
    printf("2. Administrador\n");
    printf("Opção: ");
    scanf("%d", &perfil);

    if (perfil == 1) {
        char cpf_usuario[15];
        int senha_usuario;

        printf("Por favor, informe o seu CPF: ");
        scanf("%s", cpf_usuario);
        printf("Por favor, informe a sua senha: ");
        scanf("%d", &senha_usuario);

        if (strcmp(cpf_usuario, cpf) == 0 && senha_usuario == senha) {
            int sair = 0;
            while (!sair) {
                menu();
                printf("Escolha uma das opções acima: ");
                char opcao[10];
                scanf("%s", opcao);

                if (strcmp(opcao, "1") == 0) {
                    consultar_saldo();
                    sair = voltar();
                } else if (strcmp(opcao, "2") == 0) {
                    consultar_extrato();
                    sair = voltar();
                } else if (strcmp(opcao, "3") == 0) {
                    depositar();
                    sair = voltar();
                } else if (strcmp(opcao, "4") == 0) {
                    sacar();
                    sair = voltar();
                } else if (strcmp(opcao, "5") == 0) {
                    comprar_cripto();
                    sair = voltar();
                } else if (strcmp(opcao, "6") == 0) {
                    vender_cripto();
                    sair = voltar();
                } else if (strcmp(opcao, "7") == 0) {
                    atualizar_cot();
                    sair = voltar();
                } else if (strcmp(opcao, "0") == 0) {
                    printf("Saindo, obrigado!\n");
                    sair = 1;
                } else {
                    printf("Opção inválida\n");
                }
            }
        } else {
            printf("Senha ou CPF inválidos\n");
        }

    } else if (perfil == 2) {
        char cpf_admin[15];
        int senha_admin;

        printf("Login do Administrador\nCPF: ");
        scanf("%s", cpf_admin);
        printf("Senha: ");
        scanf("%d", &senha_admin);

        if (strcmp(cpf_admin, "000.000.000-00") == 0 && senha_admin == 9999) {
            int opcao;
            int sair = 0;
            while (!sair) {
                menu_administrador();
                printf("Escolha uma das opções acima: ");
                scanf("%d", &opcao);

                switch (opcao) {
                    case 1: cadastrar_investidor(); sair = voltar(); break;
                    case 2: excluir_investidor(); sair = voltar(); break;
                    // case 3: cadastrar_cripto(); sair = voltar(); break;
                    // case 4: excluir_cripto(); sair = voltar(); break;
                    case 5: consultar_saldo_investidor(); sair = voltar(); break;
                    case 6: consultar_extrato_investidor(); sair = voltar(); break;
                    case 7: atualizar_cot(); sair = voltar(); break;
                    case 0: printf("Saindo, obrigado!\n"); sair = 1; break;
                    default: printf("Opção inválida\n");
                }
            }
        } else {
            printf("CPF ou senha de administrador inválidos!\n");
        }
    } else {
        printf("Opção de perfil inválida!\n");
    }

    return 0;
}
