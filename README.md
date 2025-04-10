# PROJETO 02
Projeto Crypto
 
# OBJETIVO DO PROJETO
O objetivo do projeto é desenvolver uma Exchange de Criptomoedas, onde o usuário poderá realizar operações de saque e depósito em reais, compra e venda de criptoativos, consulta de saldo e extratos, além da atualização das cotações dessas criptomoedas.

# FORMA DE COMPILAÇÃO E EXECUÇÃO
Inicialização   
    Ao executar, o programa chama ler_arquivo() para carregar os dados do arquivo dados.txt (saldo, extrato e cotações).
    Se o arquivo não existir, gravar_dados() cria um novo com valores padrão.
Login
    O usuário digita CPF e senha, que são comparados com as variáveis globais cpf e senha.
    Se corretos, o menu principal é exibido.
Menu Principal (Loop Principal)
    O switch no main.c direciona para cada função conforme a opção digitada:
    Depositar/Sacar (depositar(), sacar())
        Obtém a data/hora atual com obter_data_hora_atual().
        Atualiza saldo_real (+ para depósito, - para saque).
        Registra a transação no array extrato.
        Chama gravar_dados() para salvar no arquivo.
    Comprar/Vender Cripto (comprar_cripto(), vender_cripto())
        Mostra as cotações atuais (variáveis cotacao_bit, cotacao_ethe, etc.).
        Calcula o valor com taxas (ex: 2% para comprar BTC).
        Atualiza os saldos (ex: diminui saldo_real e aumenta saldo_bitcoin).
        Registra no extrato e chama gravar_dados().
    Atualizar Cotações (atualizar_cot())
        Gera variações aleatórias (entre -5% e +5%) para cotacao_bit, cotacao_ethe, etc.
        Atualiza o arquivo com gravar_dados().
Persistência dos Dados
    Sempre que uma função altera saldos ou extrato, gravar_dados() é chamada para:
        Abrir dados.txt em modo escrita ("w").
        Salvar todos os saldos e cotações.
        Escrever cada transação do extrato no formato:
            DATA HORA | TIPO | VALOR | MOEDA | COTAÇÃO | TAXA | SALDO_ATUAL
Saída
    Ao escolher "Sair", gravar_dados() é chamada uma última vez para garantir que nada seja perdido.

# BREVE EXPLICAÇÃO SOBRE A FORMA DE USO DO PROGRAMA
Para usar o programa, primeiro faça login com o CPF e senha. Após acessar, você verá um menu com 8 opções:

1. Consultar Saldo - Mostra quanto você tem em Real (BRL), Bitcoin (BTC), Ethereum (ETH) e Ripple (XRP), com os valores convertidos para BRL.
2. Ver Extrato - Exibe todo o histórico de transações, incluindo depósitos, saques, compras e vendas de criptomoedas, com data/hora, valores e saldos atualizados.
3. Depositar Dinheiro - Permite adicionar mais dinheiro em BRL à sua conta. Basta digitar o valor desejado.
4. Sacar Dinheiro - Retira um valor em BRL da sua conta, desde que você tenha saldo suficiente.
5. Comprar Criptomoedas - Aqui você pode converter seu BRL em Bitcoin (com taxa de 2%), Ethereum (taxa 1%) ou Ripple (taxa 1%). Digite o valor em BRL que quer investir.
6. Vender Criptomoedas - Venda suas criptomoedas para receber BRL: Bitcoin tem taxa de 3%, Ethereum 2% e Ripple 1%. Escolha a moeda e a quantidade.
7. Atualizar Cotações - Atualiza os preços das criptomoedas com variações aleatórias de até 5% para simular o mercado real.
0. Sair - Encerra o programa e salva automaticamente todos os seus dados.

Todas as suas transações ficam guardadas no arquivo dados.txt na mesma pasta do programa.

# LISTA COM NOMES E MATRÍCULAS DOS PARTICIPANTES DO GRUPO
Lucas Belo Gaspardo - RA: 22.224.007-9
Leonardo Fernandes E. Silva - RA: 52.224.003-5
Luis Guilherme Camillo Teixeira - RA: 22.224.006-1
