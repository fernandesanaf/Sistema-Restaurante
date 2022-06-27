#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Declaração das constantes
#define msgEscolherOpcao " Escolha uma das opções para continuar: "
#define quantidade 30
#define tamanhoNome 30

// Protótipos das Funções/procedimentos
void sair();
void opcaoInvalida();
void fazerPedido();
void verCardapio();
void dadosDoPedido();
void historicoPedidos();

// Declaração de structs
typedef struct
{
    int id[quantidade];
    char nomeCliente[tamanhoNome];
    int quant[quantidade];
} dadosPedido;

typedef struct
{
    int id;
    char prato[30];
    float valor;
} dadosCardapio;

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
            printf(" 1 - Fazer pedido\n 2 - Ver histórico de compras\n 0 - Sair");
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
            historicoPedidos();
            break;
        default:
            opcaoInvalida();
            break;
        }
    } while (opcoes_inicio != 0);

    return 0;
}

// Função para encerrar o programa
void sair()
{
    system("cls");
    printf("\n Você encerrou o programa!\n Agradecemos pela preferência :)\n");
    exit(0);
}

// Função que diz que a opção escolhida é inválida
void opcaoInvalida()
{
    printf(" opção inválida!\n\n");
}

// Função para o cliente fazer um pedido
void fazerPedido()
{
    system("cls");
    int opcoes_pedidos = 1;

    do
    {
        if (opcoes_pedidos >= 0 && opcoes_pedidos <= 4)
        {
            printf("\n==========================================\n");
            printf(" FAZER PEDIDO ");
            printf("\n==========================================\n");
            printf(" 1 - Ver Cardápio\n 2 - Voltar\n 0 - Sair");
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
            verCardapio();
            break;
        case 2:
            system("cls");
            main();
            break;
        default:
            opcaoInvalida();
            break;
        }
    } while (opcoes_pedidos != 0);
}

// Funções criadas para imprimir os dados dos cardápios
void verCardapio()
{
    system("cls");
    int i, j;
    dadosCardapio cardapio;

    FILE *itensCardapio = fopen("cardapio.txt", "r");
    if (itensCardapio == NULL)
    {
        printf(" Erro ao tentar abrir o Cardápio.\n Tente novamente mais tarde!\n");
        main();
    }
    else
    {
        i = 1;
        while (fscanf(itensCardapio, "%d;", &cardapio.id) != EOF)
        {
            if (i == 1)
            {
                printf("\n==========================================\n");
                printf("           Cardápio de comidas");
                printf("\n==========================================\n");
                printf(" %-6s%-29s%-6s\n", "nº", "Nome", "Valor");
            }
            else if (i == 11)
            {
                printf("\n==========================================\n");
                printf("           Cardápio de bebidas");
                printf("\n==========================================\n");
                printf(" %-6s%-29s%-6s\n", "nº", "Nome", "Valor");
            }
            else if (i == 21)
            {
                printf("\n==========================================\n");
                printf("          Cardápio de sobremesas");
                printf("\n==========================================\n");
                printf(" %-6s%-29s%-6s\n", "nº", "Nome", "Valor");
            }

            fscanf(itensCardapio, "%d;", &cardapio.id);
            // Lê tudo o que tem na linha, após o primeiro ";"
            fscanf(itensCardapio, "%[^\n]", &cardapio.prato);

            printf(" %-6d", cardapio.id);

            // strtok(), neste caso, é usado para separar os itens que estéo entre os ";"
            char *token = strtok(cardapio.prato, ";");
            j = 0;
            while (j < 2)
            {
                if (j == 0)
                {
                    // Ao entrar no laço pela primeira vez, imprimo o nome do prato
                    printf("%-29s", cardapio.prato);
                }
                else
                {
                    // Ao entrar no laço pela segunda vez, transformo a string em float, através da Função atof(), e imprimo esse float
                    cardapio.valor = atof(token);
                    printf("%.2f\n", cardapio.valor);
                }
                // o que já foi lido e printado, é anulado, para prosseguir com as leituras
                token = strtok(NULL, ";");
                j++;
            }
            i++;
        }
        printf("\n\n");
    }
    fclose(itensCardapio);

    dadosDoPedido();
}

void dadosDoPedido()
{
    int i, j, k, cont;
    float valorTotal = 0;
    dadosCardapio cardapio;
    dadosPedido pedido;

    printf(" Agora precisamos de algumas informações para completar seu pedido: ");
    printf("\n Nome completo: ");
    fflush(stdin);
    scanf("%[^\n]", &pedido.nomeCliente);

    FILE *pedidosCliente = fopen("pedidos.txt", "a");

    i = 0;
    cont = 0;
    printf("\n Informe o número do produto e a quantidade que deseja pedir. \n Digite 0 (zero) para finalizar: \n");
    do
    {
        printf("\n %dº produto: ", i + 1);
        scanf("%d", &pedido.id[i]);
        if (pedido.id[i] != 0)
        {
            printf(" Quantidade: ", i + 1);
            scanf("%d", &pedido.quant[i]);
        }
        else
        {
            printf("\n Pedido realizado com sucesso!\n Dados do pedido:\n");
            printf("===========================================================\n");
            printf(" %-6s%-29s%-6s\t%s\n", "nº", "Nome", "Valor", "Quantidade");
        }

        i++;
        cont++;
    } while (pedido.id[i - 1] != 0);

    k = 1;
    for (i = 0; i < cont; i++)
    {
        FILE *itensCardapio = fopen("cardapio.txt", "r");
        if (itensCardapio == NULL || pedidosCliente == NULL)
        {
            printf(" Erro ao tentar anotar o pedido.\n Tente novamente mais tarde!\n");
            main();
        }
        else
        {
            do
            {
                fscanf(itensCardapio, "%d;", &cardapio.id);
                // Lê tudo o que tem na linha, após o primeiro ";"
                fscanf(itensCardapio, "%[^\n]", &cardapio.prato);

                if (cardapio.id == pedido.id[i])
                {
                    printf(" %-5d", cardapio.id);
                    char *token = strtok(cardapio.prato, ";");
                    j = 0;
                    while (j < 2)
                    {
                        if (j == 0)
                        {
                            printf(" %-29s", cardapio.prato);
                        }
                        else
                        {
                            cardapio.valor = atof(token);
                            printf("R$ %.2f\t", cardapio.valor);
                        }
                        token = strtok(NULL, ";");
                        j++;
                    }
                    valorTotal += (cardapio.valor * pedido.quant[i]);
                    printf("%d\n", pedido.quant[i]);
                    fclose(itensCardapio);
                    k++;
                }
            } while (cardapio.id != pedido.id[i] && k != cont);
        }
    }
    printf("===========================================================");
    printf("\n VALOR TOTAL DO PEDIDO: R$ %.2f\n\n", valorTotal);

    fclose(pedidosCliente);
    exit(0);
}
// Função para o cliente pedir a conta
void historicoPedidos()
{
    system("cls");
    // Funções para mostrar o arquivo de historico
    char aux;
    // obs dev: nessa Função, temos que consultar o arquivo de pedidos
    printf("\n Listar todos os pedidos do restaurante.\n\n");
    sair();
    FILE *historicoPedidos = fopen("historicoPedidos.txt", "r");
    if (historicoPedidos == NULL)
    {
        printf(" Erro ao tentar abrir o historico.\n Tente novamente mais tarde!\n");
        main();
    }
    else
    {
        printf("histórico");
        while (fscanf(historicoPedidos, "%d;", &aux) != EOF)
        {
            printf(" %c", aux);
        }
        printf("\n\n");
    }
    fclose(historicoPedidos);
}

// Fazer dois vetores e armazenar o id do produto e a quantidade