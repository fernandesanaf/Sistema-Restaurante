#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Declara��o das constantes
#define msgEscolherOpcao " Escolha uma das op��es para continuar: "
#define quantidade 15
#define tamanhoNome 30

// Prot�tipos das fun��es/procedimentos
void sair();
void opcaoInvalida();
void fazerPedido();
void fecharConta();
void cardapioComidas();
void cardapioBebidas();
void cardapioSobremesas();

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
            printf(" Ol�! Seja bem vindo ao nosso sistema!\n O que deseja fazer?");
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

        // obs dev: pensei em adicionar a op��o "excluir pedido"
        // obs dev: se der tempo, talvez colocar a op��o de "editar pedido"
        // Motivo: trabalhar com exclus�o e edi��o de itens no arquivo
    } while (opcoes_inicio != 0);

    return 0;
}

// Fun��o para encerrar o programa
void sair()
{
    printf(" Voc� encerrou o programa!\n Agradecemos pela prefer�ncia :)\n");
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
            printf(" 1 - Voltar\n 2 - Card�pio de comidas\n 3 - Card�pio de Bebidas\n 4 - Card�pio de Sobremesas\n 0 - Sair");
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

// Fun��es criadas para imprimir os dados dos card�pios
// obs dev: talvez tenha uma forma de fazer isso usando apenas uma fun��o, e passando o arquivo por par�metro
void cardapioComidas()
{
    int i, j, idProduto[10];
    char nome_cliente[30];
    dadosCardapio comida;

    FILE *comidas = fopen("comidas.txt", "r");
    if (comidas == NULL)
    {
        printf(" Erro ao tentar abrir o card�pio de comidas.\n Tente novamente mais tarde!\n");
        main();
    }
    else
    {
        printf("\n==========================================\n");
        printf(" Card�pio de Comidas");
        printf("\n==========================================\n");
        printf(" n� - Nome - Valor");
        printf("\n==========================================\n");

        i = 0;
        while (fscanf(comidas, "%d;", &comida.id) != EOF)
        {
            fscanf(comidas, "%d;", &comida.id);
            fscanf(comidas, "%[^\n]", &comida.prato);

            printf(" %d - ", comida.id);

            char *token = strtok(comida.prato, ";");
            j = 0;
            while (j < 2)
            {
                if (j == 0)
                {
                    printf("%s - ", comida.prato);
                }
                else
                {
                    comida.valor = atof(token);
                    printf("%.2f\n", comida.valor);
                }
                token = strtok(NULL, ";");
                j++;
            }
            i++;
        }
        printf("==========================================\n\n");
    }
    printf(" Agora precisamos de algumas informa��es para completar seu pedido: ");
    printf("\n Nome-Sobrenome (no formato indicado, e sem acento): ");
    fflush(stdin);
    scanf("%s", &nome_cliente);

    FILE *pedidosCliente = fopen(nome_cliente, "w");
    if (pedidosCliente == NULL)
    {
        printf(" Erro ao tentar anotar o pedido:(\n Tente novamente mais tarde!\n");
        main();
    }
    else
    {
        for (i = 0; i < 10; i++)
        {
            idProduto[i] = 0;
        }
        i = 0;
        do
        {
            printf(" Informe o n�mero do produto (ou digite zero para finalizar): ");
            scanf("%d", &idProduto[i]);
            if (idProduto[i - 1] != 0)
            {
                // fprintf(feminino, "%d ", pessoa[i].id);
                fprintf(pedidosCliente, "%d", i);
                fprintf(pedidosCliente, "%[^\n]", nome_cliente);
                fprintf(pedidosCliente, "%d", comida.id);
                fprintf(pedidosCliente, "%.2f", comida.valor);
            }
            else
            {
                printf("\nPedido realizado com sucesso! ");
            }

            printf("\nNome do Cliente: %c \n Prato escolhido: %d \n Valor do Prato: %.2f\n", nome_cliente, comida.id, comida.valor);
            //deu errado ainda
            // printar:
            // id_pedido
            // nome_cliente
            // id_prato
            // valor_prato

            i++;
        } while (idProduto[i - 1] != 0 && i < 10);
    }

    fclose(comidas);
    fclose(pedidosCliente);
}
void cardapioBebidas()
{
    int i, j, idProduto[10];
    char nome_cliente[30];
    dadosCardapio bebida;

    FILE *bebidas = fopen("bebidas.txt", "r");
    if (bebidas == NULL)
    {
        printf(" Erro ao tentar abrir o card�pio de comidas.\n Tente novamente mais tarde!\n");
        main();
    }
    else
    {
        printf("\n==========================================\n");
        printf(" Card�pio de Bebidas");
        printf("\n==========================================\n");
        printf(" n� - Nome - Valor");
        printf("\n==========================================\n");

        i = 0;
        while (fscanf(bebidas, "%d;", &bebida.id) != EOF)
        {
            fscanf(bebidas, "%d;", &bebida.id);
            fscanf(bebidas, "%[^\n]", &bebida.prato);

            printf(" %d - ", bebida.id);

            char *token = strtok(bebida.prato, ";");
            j = 0;
            while (j < 2)
            {
                if (j == 0)
                {
                    printf("%s - ", bebida.prato);
                }
                else
                {
                    bebida.valor = atof(token);
                    printf("%.2f\n", bebida.valor);
                }
                token = strtok(NULL, ";");
                j++;
            }
            i++;
        }
        printf("==========================================\n\n");
    }
    printf(" Agora precisamos de algumas informa��es para completar seu pedido: ");
    printf("\n Nome-Sobrenome (no formato indicado, e sem acento): ");
    fflush(stdin);
    scanf("%s", &nome_cliente);

    FILE *pedidosCliente = fopen(nome_cliente, "w");
    if (pedidosCliente == NULL)
    {
        printf(" Erro ao tentar anotar o pedido:(\n Tente novamente mais tarde!\n");
        main();
    }
    else
    {
        for (i = 0; i < 10; i++)
        {
            idProduto[i] = 0;
        }
        i = 0;
        do
        {
            printf(" Informe o n�mero do produto (ou digite zero para finalizar): ");
            scanf("%d", &idProduto[i]);
            if (idProduto[i - 1] != 0)
            {
                // fprintf(feminino, "%d ", pessoa[i].id);
                fprintf(pedidosCliente, "%d", i);
                fprintf(pedidosCliente, "%[^\n]", nome_cliente);
                fprintf(pedidosCliente, "%d", bebida.id);
                fprintf(pedidosCliente, "%.2f", bebida.valor);
            }
            else
            {
                printf("\nPedido realizado com sucesso! ");
            }

            printf("\nNome do Cliente: %c \n Prato escolhido: %d \n Valor do Prato: %.2f\n", nome_cliente, bebida.id, bebida.valor);
            //deu errado ainda
            // printar:
            // id_pedido
            // nome_cliente
            // id_prato
            // valor_prato

            i++;
        } while (idProduto[i - 1] != 0 && i < 10);
    }

    fclose(bebidas);
    fclose(pedidosCliente);
}
void cardapioSobremesas()
{
    int i, j, idProduto[10];
    char nome_cliente[30];
    dadosCardapio sobremesa;

    FILE *sobremesas = fopen("sobremesas.txt", "r");
    if (sobremesas == NULL)
    {
        printf(" Erro ao tentar abrir o card�pio de sobremesas.\n Tente novamente mais tarde!\n");
        main();
    }
    else
    {
        printf("\n==========================================\n");
        printf(" Card�pio de sobremesas");
        printf("\n==========================================\n");
        printf(" n� - Nome - Valor");
        printf("\n==========================================\n");

        i = 0;
        while (fscanf(sobremesas, "%d;", &sobremesa.id) != EOF)
        {
            fscanf(sobremesas, "%d;", &sobremesa.id);
            // L� tudo o que tem na linha, ap�s o primeiro ";"
            fscanf(sobremesas, "%[^\n]", &sobremesa.prato);

            printf(" %d - ", sobremesa.id);

            // strtok(), neste caso, � usado para separar os itens que est�o entre os ";"
            char *token = strtok(sobremesa.prato, ";");
            j = 0;
            while (j < 2)
            {
                if (j == 0)
                {
                    // Ao entrar no la�o pela primeira vez, imprimo o nome do prato
                    printf("%s - ", sobremesa.prato);
                }
                else
                {
                    // Ao entrar no la�o pela segunda vez, transformo a string em float, atrav�s da fun��o atof(), e imprimo esse float
                    sobremesa.valor = atof(token);
                    printf("%.2f\n", sobremesa.valor);
                }
                // o que j� foi lido e printado, � anulado, para prosseguir com as leituras
                token = strtok(NULL, ";");
                j++;
            }
            i++;
        }
        printf("==========================================\n\n");
    }

    printf(" Agora precisamos de algumas informa��es para completar seu pedido: ");
    printf("\n Nome-Sobrenome (no formato indicado, e sem acento): ");
    fflush(stdin);
    scanf("%s", &nome_cliente);

    FILE *pedidosCliente = fopen(nome_cliente, "w");
    if (pedidosCliente == NULL)
    {
        printf(" Erro ao tentar anotar o pedido:(\n Tente novamente mais tarde!\n");
        main();
    }
    else
    {
        // zerando o vetor, para evitar buffer
        for (i = 0; i < 10; i++)
        {
            idProduto[i] = 0;
        }

        i = 0;
        do
        {
            printf(" Informe o n�mero do produto (ou digite zero para finalizar): ");
            scanf("%d", &idProduto[i]);
            if (idProduto[i - 1] != 0)
            {
                // fprintf(feminino, "%d ", pessoa[i].id);
                fprintf(pedidosCliente, "%d", i);
                fprintf(pedidosCliente, "%[^\n]", nome_cliente);
                fprintf(pedidosCliente, "%d", sobremesa.id);
                fprintf(pedidosCliente, "%.2f", sobremesa.valor);
            }
            else
            {
                printf("\nPedido realizado com sucesso! ");
            }

            // printar:
            // id_pedido
            // nome_cliente
            // id_prato
            // valor_prato

            i++;
        } while (idProduto[i - 1] != 0 && i < 10);
    }

    fclose(sobremesas);
    fclose(pedidosCliente);
}

void dadosDoPedido()
{
    // fun��o para coletar ids do pedido e nome do cliente
    // utilizar a struct que criei, para coletar os dados do pedido
}

// Fun��o para o cliente pedir a conta
void fecharConta()
{
    // obs dev: nessa fun��o, temos que consultar o arquivo de pedidos
    printf(" Listar todos os pedidos do cliente e exibir o valor total da conta\n\n");
    sair();
}