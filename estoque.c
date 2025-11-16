// Inclusão de bibliotecas e definição de constantes
#include <stdio.h>
#include <string.h>
#include <windows.h>

#define MAX 50

// Declaração de variáveis
typedef struct // A struct Produto agrupa vários dados (código, nome, preço etc.) em um único tipo.
{
    int codigo;
    char nome[30];
    char descricao[100];
    float preco;
    int quantidade;
} Produto;

Produto produtos[MAX]; //"MAX" está relacionado ao "#define MAX 50", permitindo apenas 50 códigos nesse caso.
int totalProdutos = 0;

// Incrementando as funções de persistência de dados
// Salva os dados registrados
void salvarDados()
{
    FILE *arquivo = fopen("produtos.txt", "w");

    // Se não for possível abrir ou criar o arquivo o programa retorna NULL e exibe uma mensagem de erro.
    if (arquivo == NULL)
    {
        printf("Erro ao salvar dados.\n");
        return;
    }

    for (int i = 0; i < totalProdutos; i++)
    {
        fprintf(arquivo, "%d;%s;%s;%.2f;%d\n",
                produtos[i].codigo, produtos[i].nome,
                produtos[i].descricao, produtos[i].preco,
                produtos[i].quantidade);
    }

    fclose(arquivo);
}

// Carrega e exibe os dados do arquivo
void carregarDados()
{
    FILE *arquivo = fopen("produtos.txt", "r");
    if (arquivo == NULL)
    {
        printf("Nenhum arquivo de dados encontrado. Um novo será criado.\n");
        return;
    }

    while (totalProdutos < MAX &&
           fscanf(arquivo, "%d;%29[^;];%99[^;];%f;%d\n",
                  &produtos[totalProdutos].codigo,
                  produtos[totalProdutos].nome,
                  produtos[totalProdutos].descricao,
                  &produtos[totalProdutos].preco,
                  &produtos[totalProdutos].quantidade) == 5)
    {
        totalProdutos++;
    }

    fclose(arquivo);
    printf("%d produtos carregados com sucesso.\n", totalProdutos);
}

// Menu principal
int main()
{
    // Garante que acentos e caracteres especiais apareçam corretamente no terminal do Windows.
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int opcao;
    float valorTotal = 0;

    carregarDados();

    do
    {
        printf("-----------------------------------------\n");
        printf("SISTEMA DE CONTROLE DE ESTOQUE DE MERCADO\n");
        printf("1. Cadastrar produto\n");
        printf("2. Consultar produto por código\n");
        printf("3. Buscar produto por nome\n");
        printf("4. Buscar produto por faixa de preço\n");
        printf("5. Atualizar produto\n");
        printf("6. Remover produto\n");
        printf("7. Registrar entrada de estoque\n");
        printf("8. Registrar saída de estoque\n");
        printf("9. Relatório: produtos com estoque baixo\n");
        printf("10. Relatório: todos os produtos\n");
        printf("11. Estatísticas\n");
        printf("0. Sair\n");
        printf("--------------------------------------------------\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &opcao) != 1)
        {
            // Limpa entrada inválida
            while (getchar() != '\n')
                ;
            opcao = -1;
        }

        switch (opcao)
        {
        // 1 - Cadastrar produto
        case 1:
            if (totalProdutos < MAX)
            {
                int codigoDuplicado = 0;
                int novoCodigo;
                Produto novoProduto;

                printf("\n--- Cadastro de Produto ---\n");
                printf("Código: ");
                scanf("%d", &novoCodigo);

                for (int i = 0; i < totalProdutos; i++)
                {
                    if (produtos[i].codigo == novoCodigo)
                    {
                        codigoDuplicado = 1;
                        break;
                    }
                }

                if (codigoDuplicado)
                {
                    printf("Erro: já existe um produto com esse código!\n");
                    break;
                }

                novoProduto.codigo = novoCodigo;

                printf("Nome: ");
                scanf(" %[^\n]", novoProduto.nome);

                printf("Descrição: ");
                scanf(" %[^\n]", novoProduto.descricao);

                do
                {
                    printf("Preço: ");
                    if (scanf("%f", &novoProduto.preco) != 1)
                    {
                        while (getchar() != '\n')
                            ;
                        novoProduto.preco = -1;
                    }
                    if (novoProduto.preco < 0)
                        printf("Preço inválido! Digite um valor positivo.\n");
                } while (novoProduto.preco < 0);

                do
                {
                    printf("Quantidade em estoque: ");
                    if (scanf("%d", &novoProduto.quantidade) != 1)
                    {
                        while (getchar() != '\n')
                            ;
                        novoProduto.quantidade = -1;
                    }
                    if (novoProduto.quantidade < 0)
                        printf("Quantidade inválida! Digite um valor positivo.\n");
                } while (novoProduto.quantidade < 0);

                produtos[totalProdutos++] = novoProduto;
                printf("Produto cadastrado com sucesso!\n");
                salvarDados();
            }
            else
            {
                printf("Limite máximo de produtos atingido!\n");
            }
            break;

        // 2 - Consultar produto por código
        case 2:
        {
            int codigo, encontrado = 0;
            printf("\n--- Consultar Produto por Código ---\n");
            printf("Digite o código: ");
            scanf("%d", &codigo);

            for (int i = 0; i < totalProdutos; i++)
            {
                if (produtos[i].codigo == codigo)
                {
                    printf("Código: %d | Nome: %s | Descrição: %s | Preço: R$ %.2f | Quantidade: %d\n",
                           produtos[i].codigo, produtos[i].nome, produtos[i].descricao, produtos[i].preco, produtos[i].quantidade);
                    encontrado = 1;
                }
            }

            if (!encontrado)
                printf("Produto não encontrado!\n");
            break;
        }

        // 3 - Buscar por nome
        case 3:
        {
            char nomeBusca[30];
            int encontrado = 0;
            printf("\n--- Buscar Produto por Nome ---\n");
            printf("Digite o nome (ou parte dele): ");
            scanf(" %[^\n]", nomeBusca);

            for (int i = 0; i < totalProdutos; i++)
            {
                if (strstr(produtos[i].nome, nomeBusca))
                {
                    printf("Código: %d | Nome: %s | Descrição: %s | Preço: %.2f | Quantidade: %d\n",
                           produtos[i].codigo, produtos[i].nome, produtos[i].descricao, produtos[i].preco, produtos[i].quantidade);
                    encontrado = 1;
                }
            }

            if (!encontrado)
                printf("Nenhum produto encontrado com esse nome.\n");
            break;
        }

        // 4 - Buscar por faixa de preço
        case 4:
        {
            float min, max;
            int encontrado = 0;
            printf("\n--- Buscar Produto por Faixa de Preço ---\n");
            printf("Preço mínimo: ");
            scanf("%f", &min);
            printf("Preço máximo: ");
            scanf("%f", &max);

            if (min > max)
            {
                printf("Faixa de preço inválida! O valor mínimo deve ser menor que o máximo.\n");
                break;
            }

            for (int i = 0; i < totalProdutos; i++)
            {
                if (produtos[i].preco >= min && produtos[i].preco <= max)
                {
                    printf("Código: %d | Nome: %s | Descrição: %s | Preço: %.2f | Quantidade: %d\n",
                           produtos[i].codigo, produtos[i].nome, produtos[i].descricao, produtos[i].preco, produtos[i].quantidade);
                    encontrado = 1;
                }
            }

            if (!encontrado)
                printf("Nenhum produto nessa faixa de preço.\n");
            break;
        }

        // 5 - Atualizar produto
        case 5:
        {
            int codigo, encontrado = 0;
            printf("\n--- Atualizar Produto ---\n");
            printf("Digite o código: ");
            scanf("%d", &codigo);

            for (int i = 0; i < totalProdutos; i++)
            {
                if (produtos[i].codigo == codigo)
                {
                    printf("Produto atual: %s | Descrição: %s | Preço: %.2f | Qtde: %d\n",
                           produtos[i].nome, produtos[i].descricao, produtos[i].preco, produtos[i].quantidade);

                    printf("Novo nome: ");
                    scanf(" %[^\n]", produtos[i].nome);

                    printf("Nova descrição: ");
                    scanf(" %[^\n]", produtos[i].descricao);

                    do
                    {
                        printf("Novo preço: ");
                        if (scanf("%f", &produtos[i].preco) != 1)
                        {
                            while (getchar() != '\n')
                                ;
                            produtos[i].preco = -1;
                        }
                        if (produtos[i].preco < 0)
                            printf("Preço inválido! Digite um valor positivo.\n");
                    } while (produtos[i].preco < 0);

                    do
                    {
                        printf("Nova quantidade: ");
                        if (scanf("%d", &produtos[i].quantidade) != 1)
                        {
                            while (getchar() != '\n')
                                ;
                            produtos[i].quantidade = -1;
                        }
                        if (produtos[i].quantidade < 0)
                            printf(" Quantidade inválida! Digite um valor positivo.\n");
                    } while (produtos[i].quantidade < 0);

                    printf("Produto atualizado com sucesso!\n");
                    salvarDados();
                    encontrado = 1;
                }
            }
            if (!encontrado)
                printf("Produto não encontrado!\n");
            break;
        }

        // 6 - Remover produto
        case 6:
        {
            int codigo, encontrado = 0;
            char confirma;
            printf("\n--- Remover Produto ---\n");
            printf("Digite o código: ");
            scanf("%d", &codigo);

            for (int i = 0; i < totalProdutos; i++)
            {
                if (produtos[i].codigo == codigo)
                {
                    printf("Produto: %s | Descrição: %s | Preço: %.2f | Qtde: %d\n",
                           produtos[i].nome, produtos[i].descricao, produtos[i].preco, produtos[i].quantidade);
                    printf("Confirmar remoção (s/n)? ");
                    scanf(" %c", &confirma);
                    if (confirma == 's' || confirma == 'S')
                    {
                        for (int j = i; j < totalProdutos - 1; j++)
                        {
                            produtos[j] = produtos[j + 1];
                        }
                        totalProdutos--;
                        printf("Produto removido!\n");
                        salvarDados();
                    }
                    else
                    {
                        printf("Remoção cancelada.\n");
                    }
                    encontrado = 1;
                    break;
                }
            }

            if (!encontrado)
                printf("Produto não encontrado!\n");
            break;
        }

        // 7 - Registrar entrada
        case 7:
        {
            int codigo, qtd, encontrado = 0;
            printf("\n--- Registrar Entrada de Estoque ---\n");
            printf("Digite o código: ");
            scanf("%d", &codigo);

            for (int i = 0; i < totalProdutos; i++)
            {
                if (produtos[i].codigo == codigo)
                {
                    printf("Produto: %s | Qtde atual: %d\n", produtos[i].nome, produtos[i].quantidade);
                    do
                    {
                        printf("Quantidade a adicionar: ");
                        if (scanf("%d", &qtd) != 1)
                        {
                            while (getchar() != '\n')
                                ;
                            qtd = -1;
                        }
                        if (qtd <= 0)
                            printf(" Valor inválido! Digite um número positivo.\n");
                    } while (qtd <= 0);

                    produtos[i].quantidade += qtd;
                    printf("Nova quantidade: %d\n", produtos[i].quantidade);
                    salvarDados();
                    encontrado = 1;
                }
            }
            if (!encontrado)
                printf("Produto não encontrado!\n");
            break;
        }

        // 8 - Registrar saída
        case 8:
        {
            int codigo, qtd, encontrado = 0;
            printf("\n--- Registrar Saída de Estoque ---\n");
            printf("Digite o código: ");
            scanf("%d", &codigo);

            for (int i = 0; i < totalProdutos; i++)
            {
                if (produtos[i].codigo == codigo)
                {
                    printf("Produto: %s | Qtde atual: %d\n", produtos[i].nome, produtos[i].quantidade);
                    do
                    {
                        printf("Quantidade a remover: ");
                        if (scanf("%d", &qtd) != 1)
                        {
                            while (getchar() != '\n')
                                ;
                            qtd = -1;
                        }
                        if (qtd <= 0)
                            printf("Valor inválido! Digite um número positivo.\n");
                    } while (qtd <= 0);

                    if (qtd <= produtos[i].quantidade)
                    {
                        produtos[i].quantidade -= qtd;
                        printf("Nova quantidade: %d\n", produtos[i].quantidade);
                        salvarDados();
                    }
                    else
                    {
                        printf("Erro: estoque insuficiente!\n");
                    }
                    encontrado = 1;
                }
            }

            if (!encontrado)
                printf("Produto não encontrado!\n");
            break;
        }

        // 9 - Relatório: estoque baixo
        case 9:
        {
            int limite, encontrado = 0;
            printf("\n--- Relatório: Estoque Baixo ---\n");
            printf("Defina o limite mínimo: ");
            scanf("%d", &limite);

            for (int i = 0; i < totalProdutos; i++)
            {
                if (produtos[i].quantidade < limite)
                {
                    printf("%d - %s | Descrição: %s | Qtde: %d | Preço: %.2f\n",
                           produtos[i].codigo, produtos[i].nome, produtos[i].descricao, produtos[i].quantidade, produtos[i].preco);
                    encontrado = 1;
                }
            }

            if (!encontrado)
                printf("Nenhum produto com estoque abaixo de %d.\n", limite);
            break;
        }

        // 10 - Relatório geral
        case 10:
            printf("\n--- Relatório: Todos os Produtos ---\n");
            for (int i = 0; i < totalProdutos; i++)
            {
                printf("Código: %d | Nome: %s | Descrição: %s | Preço: %.2f | Qtde: %d | Total: R$ %.2f\n",
                       produtos[i].codigo, produtos[i].nome, produtos[i].descricao, produtos[i].preco, produtos[i].quantidade,
                       produtos[i].preco * produtos[i].quantidade);
            }
            break;

        // 11 - Estatísticas
        case 11:
            valorTotal = 0;
            for (int i = 0; i < totalProdutos; i++)
            {
                valorTotal += produtos[i].preco * produtos[i].quantidade;
            }
            printf("\n--- Estatísticas do Estoque ---\n");
            printf("Produtos cadastrados: %d\n", totalProdutos);
            printf("Valor total em estoque: R$ %.2f\n", valorTotal);
            break;

        case 0:
            salvarDados();
            printf("\nEncerrando o programa... Até logo!\n");
            break;

        default:
            printf("Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
