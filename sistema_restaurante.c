#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Declara��o das constantes
#define msgEscolherOpcao " Escolha uma das op��es para continuar: "
#define quantidade 30
#define tamanhoNome 30

// Prot�tipos das fun��es/procedimentos
void sair();
void opcaoInvalida();
void fazerPedido();
void historicoPedidos();
void verCardapio();

// Declara��o de structs
typedef struct
{
    int id[quantidade];
    char nome[tamanhoNome];
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
            printf(" Ol� Seja bem vindo ao nosso sistema!\n O que deseja fazer?");
            printf("\n===========================================\n");
            printf(" 1 - Fazer pedido\n 2 - Ver hist�rico de compras\n 0 - Sair");
            printf("\n===========================================\n");
        }
        printf("%s", msgEscolherOpcao);
        scanf("%d", &opcoes_inicio);
        printf("\n");

        switch (opcoes_inicio)
        {
        case 0:
            system("cls");
            sair();
            break;
        case 1:
            system("cls");
            fazerPedido();
            break;
        case 2:
            system("cls");
            historicoPedidos();
            break;
        default:
            opcaoInvalida();
            break;
        }
    } while (opcoes_inicio != 0);

    return 0;
}

// Fun��o para encerrar o programa
void sair()
{
    printf("\n Voc� encerrou o programa!\n Agradecemos pela prefer�ncia :)\n");
    exit(0);
}

// Fun��o que diz que a op��o escolhida � inv�lida
void opcaoInvalida()
{
    printf(" Op��o inv�lida!\n\n");
}

// Fun��o para o cliente fazer um pedido
void fazerPedido()
{
    int opcoes_pedidos = 1;

    do
    {
        if (opcoes_pedidos >= 0 && opcoes_pedidos <= 4)
        {
            printf("\n==========================================\n");
            printf(" FAZER PEDIDO ");
            printf("\n==========================================\n");
            printf(" 1 - Ver card�pio\n 2 - Voltar\n 0 - Sair");
            printf("\n==========================================\n");
        }
        printf("%s", msgEscolherOpcao);
        scanf("%d", &opcoes_pedidos);
        printf("\n");
        system("cls");

        switch (opcoes_pedidos)
        {
        case 0:
            sair();
            break;
        case 1:
            verCardapio();
            break;
        case 2:
            main();
            break;
        default:
            opcaoInvalida();
            break;
        }
    } while (opcoes_pedidos != 0);
}

// Fun��es criadas para imprimir os dados dos card�pios:
void verCardapio()
{
    int i, j, idProduto[10];
    dadosCardapio cardapio;

    FILE *itensCardapio = fopen("cardapio.txt", "r");
    if (itensCardapio == NULL)
    {
        printf(" Erro ao tentar abrir o card�pio de sobremesas.\n Tente novamente mais tarde!\n");
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
                printf("           Card�pio de comidas");
                printf("\n==========================================\n");
                printf(" %-6s%-29s%-6s\n", "n�", "Nome", "Valor");
            }
            else if (i == 11)
            {
                printf("\n==========================================\n");
                printf("           Card�pio de bebidas");
                printf("\n==========================================\n");
                printf(" %-6s%-29s%-6s\n", "n�", "Nome", "Valor");
            }
            else if (i == 21)
            {
                printf("\n==========================================\n");
                printf("          Card�pio de sobremesas");
                printf("\n==========================================\n");
                printf(" %-6s%-29s%-6s\n", "n�", "Nome", "Valor");
            }

            fscanf(itensCardapio, "%d;", &cardapio.id);
            // L� tudo o que tem na linha, ap�s o primeiro ";"
            fscanf(itensCardapio, "%[^\n]", &cardapio.prato);

            printf(" %-6d", cardapio.id);

            // strtok(), neste caso, � usado para separar os itens que est�o entre os ";"
            char *token = strtok(cardapio.prato, ";");
            j = 0;
            while (j < 2)
            {
                if (j == 0)
                {
                    // Ao entrar no la�o pela primeira vez, imprimo o nome do prato
                    printf("%-29s", cardapio.prato);
                }
                else
                {
                    // Ao entrar no la�o pela segunda vez, transformo a string em float, atrav�s da fun��o atof(), e imprimo esse float
                    cardapio.valor = atof(token);
                    printf("%.2f\n", cardapio.valor);
                }
                // o que j� foi lido e printado, � anulado, para prosseguir com as leituras
                token = strtok(NULL, ";");
                j++;
            }
            i++;
        }
        printf("\n\n");
    }

    dadosDoPedido();

    fclose(itensCardapio);
}
void dadosDoPedido()
{
    int i, idItem;
    dadosCardapio cardapio;
    dadosPedido pedido;

    // fun��o para coletar ids do pedido e nome do cliente
    // utilizar a struct que criei, para coletar os dados do pedido
    FILE *itensCardapio = fopen("cardapio.txt", "r");
    FILE *pedidosCliente = fopen("historicoPedidos.txt", "w");
    if (pedidosCliente == NULL)
    {
        printf(" Erro ao tentar anotar o pedido:(\n Tente novamente mais tarde!\n");
        main();
    }
    else
    {
        printf(" Agora precisamos de algumas informa��es para completar seu pedido: ");
        printf("\n Nome completo: ");
        fflush(stdin);
        scanf("%[^\n]", &pedido.nome);

        // zerando o vetor, para evitar buffer
        for (i = 0; i < quantidade; i++)
        {
            pedido.id[i] = 0;
        }

        i = 0;
        printf(" Informe o n�mero do produto que deseja, digite 0 (zero) para finalizar: \n Obs.: Se quiser duas ou mais vezes o mesmo produto, digite o c�digo mais de uma vez!\n");
        do
        {
            printf(" %d� produto: ", i + 1);
            scanf("%d", &pedido.id[i]);
            if (pedido.id[i - 1] != 0)
            {
                fscanf(itensCardapio, "%d;", &cardapio.id) == pedido.id[i];

                // fprintf(pedidosCliente, "%d", i);
                // fprintf(pedidosCliente, "%[^\n]", nome_cliente);
                // fprintf(pedidosCliente, "%d", cardapio.id);
                // fprintf(pedidosCliente, "%.2f", cardapio.valor);
            }

            // printar:
            // id_pedido
            // nome_cliente
            // id_prato
            // valor_prato

            i++;
        } while (pedido.id[i - 1] != 0 && i < 30);
    }

    fclose(pedidosCliente);
    fclose(itensCardapio);
}
// Fun��o para o cliente pedir a conta
void historicoPedidos()
{
    // obs dev: nessa fun��o, temos que consultar o arquivo de pedidos
    printf(" Listar todos os pedidos do restaurante.\n\n");
    sair();
}