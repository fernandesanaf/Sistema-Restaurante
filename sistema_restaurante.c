#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Declaração das constantes
#define msgEscolherOpcao " Escolha uma das opções para continuar: "
#define quantidade 15
#define tamanhoNome 30

// Protótipos das funções/procedimentos
void sair();
void opcaoInvalida();
void fazerPedido();
void fecharConta();
void cardapioComidas();
void cardapioBebidas();
void cardapioSobremesas();

// Declaração de structs
typedef struct
{
    int id[quantidade];
    char nome[tamanhoNome];
} dadosPedido;

int main()
{
    setlocale(LC_ALL, "portuguese-brazilian");

    int opcoes_inicio = 1;

    do
    {
        if (opcoes_inicio >= 0 && opcoes_inicio <= 2)
        {
            printf("\n===========================================\n");
            printf(" Olá! Seja bem vindo ao nosso sistema!\n O que deseja fazer?");
            printf("\n===========================================\n");
            printf(" 1 - Fazer pedido\n 2 - Fechar a conta\n 0 - Sair");
            printf("\n===========================================\n");
        }
        printf("%s", msgEscolherOpcao);
        scanf("%d", &opcoes_inicio);
        printf("\n");

        switch (opcoes_inicio)
        {
        case 0:
            sair();
            break;
        case 1:
            fazerPedido();
            break;
        case 2:
            fecharConta();
            break;
        default:
            opcaoInvalida();
            break;
        }

        // obs dev: pensei em adicionar a opção "excluir pedido"
        // obs dev: se der tempo, talvez colocar a opção de "editar pedido"
        // Motivo: trabalhar com exclusão e edição de itens no arquivo
    } while (opcoes_inicio != 0);

    return 0;
}

// Função para encerrar o programa
void sair()
{
    printf(" Você encerrou o programa!\n Agradecemos pela preferência :)\n");
    exit(0);
}

// Função que diz que a opção escolhida é inválida
void opcaoInvalida()
{
    printf(" Opção inválida!\n\n");
}

// Função para o cliente fazer um pedido
void fazerPedido()
{
    int opcoes_pedidos = 1;

    do
    {
        if (opcoes_pedidos >= 0 && opcoes_pedidos <= 2)
        {
            printf("\n==========================================\n");
            printf(" FAZER PEDIDO ");
            printf("\n==========================================\n");
            printf(" 1 - Voltar\n 2 - Cardápio de comidas\n 3 - Cardápio de Bebidas\n 4 - Cardápio de Sobremesas\n 0 - Sair");
            printf("\n==========================================\n");
        }
        printf("%s", msgEscolherOpcao);
        scanf("%d", &opcoes_pedidos);
        printf("\n");

        switch (opcoes_pedidos)
        {
        case 0:
            sair();
            break;
        case 1:
            main();
            break;
        case 2:
            cardapioComidas();
            break;
        case 3:
            cardapioBebidas();
            break;
        case 4:
            cardapioSobremesas();
            break;
        default:
            opcaoInvalida();
            break;
        }
    } while (opcoes_pedidos != 0);
}

// Funções criadas para imprimir os dados dos cardápios
// obs dev: talvez tenha uma forma de fazer isso usando apenas uma função, e passando o arquivo por parâmetro
void cardapioComidas()
{
    printf(" Listar as opções do cardápio de comidas");
}
void cardapioBebidas()
{
    printf(" Listar as opções do cardápio de bebidas");
}
void cardapioSobremesas()
{
    printf(" Listar as opções do cardápio de sobremesas");
}

void dadosDoPedido()
{
    // função para coletar ids do pedido e nome do cliente
    // utilizar a struct que criei, para coletar os dados do pedido
}

// Função para o cliente pedir a conta
void fecharConta()
{
    // obs dev: nessa função, temos que consultar o arquivo de pedidos
    printf(" Listar todos os pedidos do cliente e exibir o valor total da conta\n\n");
    sair();
}