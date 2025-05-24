# PROJETO 04
Projeto Crypto
 
# OBJETIVO DO PROJETO
O objetivo do projeto é desenvolver uma Exchange de Criptomoedas, onde o usuário poderá realizar operações de saque e depósito em reais, compra e venda de criptoativos, consulta de saldo e extratos, além da atualização das cotações dessas criptomoedas.

Além do modo usuário, o sistema também conta com um modo administrador, que permite ao responsável da plataforma acessar funcionalidades exclusivas, como visualizar os saldos de todos os usuários, redefinir valores de saldos e cotações, e realizar manutenção nos dados registrados no sistema. Esse modo é protegido por um login específico e separado do acesso comum de usuário.


# FORMA DE COMPILAÇÃO E EXECUÇÃO
Inicialização:
O sistema inicia com valores padrão para as criptomoedas:
Bitcoin: R$ 200.000,00 (taxa 1%)
Ethereum: R$ 10.000,00 (taxa 0.8%)
Ripple: R$ 2,00 (taxa 0.5%)
Não há persistência entre execuções (dados ficam apenas em memória)

Login:
Investidores: CPF e senha cadastrados (ex: "12345678901"/"senha123")
Administrador: senha fixa "admin123"

Fluxo Principal:
O usuário faz login com CPF e senha
O sistema verifica as credenciais
Se válidas, mostra o menu correspondente (investidor ou admin)
Cada operação é processada e registrada

Extratos são salvos em "extrato.txt"

# BREVE EXPLICAÇÃO SOBRE A FORMA DE USO DO PROGRAMA
Para Investidores:
    Consultar Saldo - Mostra os valores atuais em:
        Reais (BRL)
        Bitcoin (BTC)
        Ethereum (ETH)
        Ripple (XRP)

    Consultar Extrato - Exibe o histórico completo com:
        Data e hora exatas
        Tipo de operação
        Valores e taxas aplicadas
        Saldo após cada transação

    Depositar Dinheiro - Adiciona valores à conta em BRL:
        Digite o valor desejado
        Confirmação automática

    Sacar Dinheiro - Retira valores da conta:
        Exige confirmação de senha
        Bloqueia se saldo for insuficiente

    Comprar Criptomoedas - Conversão de BRL para criptos:
        Mostra cotações atualizadas
        Calcula taxas automaticamente
        Confirmação antes da execução

    Vender Criptomoedas - Conversão de criptos para BRL:
        Exibe valor líquido após taxas
        Requer confirmação dupla

    Atualizar Cotações - Simula variações de mercado:
        Oscilações entre -5% e +5%
        Atualização em tempo real

Para Administradores:
Acesso exclusivo com a senha "admin123", contendo ferramentas para:
    Cadastrar Investidor - Registra novos usuários com:
        Nome completo
        CPF (apenas números)
        Senha de acesso

    Excluir Investidor - Remove cadastros por CPF:
        Mostra dados antes de confirmar
        Exclusão definitiva

    Gerenciar Criptomoedas - Adiciona/remove ativos:
        Define nome e símbolo
        Configura cotação inicial
        Ajusta taxas de compra/venda

    Consultas Avançadas - Acesso completo a:
        Saldos de qualquer investidor
        Extratos detalhados por CPF
        Atualização Forçada - Modifica cotações manualmente

# LISTA COM NOMES E MATRÍCULAS DOS PARTICIPANTES DO GRUPO
Lucas Belo Gaspardo - RA: 22.224.007-9
Leonardo Fernandes E. Silva - RA: 52.224.003-5
Luis Guilherme Camillo Teixeira - RA: 22.224.006-1