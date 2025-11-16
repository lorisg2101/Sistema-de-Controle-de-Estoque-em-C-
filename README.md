# Sistema de Controle de Estoque em C

## Descrição

Este é um programa em C para gerenciar o estoque de produtos de forma simples. Ele permite cadastrar produtos, consultar informações, atualizar, remover, registrar entradas e saídas de estoque, gerar relatórios e estatísticas, e salvar os dados em arquivo para persistência.

Cada produto possui os seguintes dados:

* Código
* Nome
* Descrição
* Preço unitário
* Quantidade em estoque

## Funcionalidades

1. Cadastrar produto
2. Consultar produto por código
3. Buscar produto por nome
4. Buscar produto por faixa de preço
5. Atualizar produto
6. Remover produto
7. Registrar entrada de estoque
8. Registrar saída de estoque
9. Relatório: produtos com estoque baixo
10. Relatório: todos os produtos
11. Estatísticas do estoque
12. Sair

## Persistência de Dados

* Todos os produtos cadastrados são salvos no arquivo `produtos.txt`.
* Ao iniciar o programa, os produtos do arquivo são carregados automaticamente.

## Requisitos

* Compilador C (ex: MinGW no Windows, gcc no Linux).
* Console do Windows configurado para UTF-8 para exibir corretamente os acentos.

## Como Executar

1. Compile o código:
gcc estoque.c -o estoque.exe

2. Execute o programa:
./estoque.exe

3. Siga o menu para cadastrar e gerenciar os produtos.
