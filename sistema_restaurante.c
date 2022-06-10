#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        if (opcoes_pedidos >= 0 && opcoes_pedidos <= 4)
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
    int i, j, idProduto[10];
    char nome_cliente[30];
    dadosCardapio sobremesa;

    FILE *sobremesas = fopen("sobremesas.txt", "r");
    if (sobremesas == NULL)
    {
        printf(" Erro ao tentar abrir o cardápio de sobremesas.\n Tente novamente mais tarde!\n");
        main();
    }
    else
    {
        printf("\n==========================================\n");
        printf(" Cardápio de sobremesas");
        printf("\n==========================================\n");
        printf(" nº - Nome - Valor");
        printf("\n==========================================\n");

        i = 0;
        while (fscanf(sobremesas, "%d;", &sobremesa.id) != EOF)
        {
            fscanf(sobremesas, "%d;", &sobremesa.id);
            // Lê tudo o que tem na linha, após o primeiro ";"
            fscanf(sobremesas, "%[^\n]", &sobremesa.prato);

            printf(" %d - ", sobremesa.id);

            // strtok(), neste caso, é usado para separar os itens que estão entre os ";"
            char *token = strtok(sobremesa.prato, ";");
            j = 0;
            while (j < 2)
            {
                if (j == 0)
                {
                    // Ao entrar no laço pela primeira vez, imprimo o nome do prato
                    printf("%s - ", sobremesa.prato);
                }
                else
                {
                    // Ao entrar no laço pela segunda vez, transformo a string em float, através da função atof(), e imprimo esse float
                    sobremesa.valor = atof(token);
                    printf("%.2f\n", sobremesa.valor);
                }
                // o que já foi lido e printado, é anulado, para prosseguir com as leituras
                token = strtok(NULL, ";");
                j++;
            }
            i++;
        }
        printf("==========================================\n\n");
    }

    printf(" Agora precisamos de algumas informações para completar seu pedido: ");
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
            printf(" Informe o número do produto (ou digite zero para finalizar): ");
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