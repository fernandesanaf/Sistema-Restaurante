#include <stdio.h>
#include <stdlib.h>
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
    float preco;
} Comidas;

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
        if (opcoes_pedidos >= 0 && opcoes_pedidos <= 2)
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
    //dadosCardapio comida;

    FILE *comidas = fopen("./comidas.txt", "r");

    if (comidas == NULL)
    {
        printf("Erro ao abrir o arquivo comidas.txt");
        return 1;
    }
    else
    {
        printf("\n===============================");
        printf("\n       Cardapio: ");
        printf("\n===============================\n");

        i = 0;
        while (fscanf(comida, "%d", &comida[i].id) != EOF)
        {

            fscanf(comidas, "%d;", &comida.id);
            // Lê tudo o que tem na linha, após o primeiro ";"
            fscanf(comida, "%[^\n]", &comida.prato);

            printf(" %d - ", comida.id);

            // strtok(), neste caso, é usado para separar os itens que estão entre os ";"
            char *token = strtok(comida.prato, ";");
            j = 0;

            while(j<2){
                if (j == 0)
                {
                    // Ao entrar no laço pela primeira vez, imprimo o nome do prato
                    printf("%s - ", comida.prato);
                }
                else
                {
                    // Ao entrar no laço pela segunda vez, transformo a string em float, através da função atof(), e imprimo esse float
                    comida.valor = atof(token);
                    printf("%.2f\n", comida.valor);
                }
                // o que já foi lido e printado, é anulado, para prosseguir com as leituras
                token = strtok(NULL, ";");
                j++;
            }
            i++;
        }
        printf("\n===============================\n");
    }
    fclose(comidas);

    return 0;
}
void cardapioBebidas()
{
    printf(" Listar as op��es do card�pio de bebidas");
}
void cardapioSobremesas()
{
    printf(" Listar as op��es do card�pio de sobremesas");
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