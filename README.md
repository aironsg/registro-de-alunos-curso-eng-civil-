# Programa de Classificação de Alunos

## Descrição

Este programa foi desenvolvido para classificar alunos com base em suas médias em duas disciplinas. Utilizando as estruturas `struct` em C, o programa armazena os dados dos alunos, calcula suas médias gerais, classifica-os e salva as informações em um arquivo de texto.

## Funcionalidades

- Solicitação de dados dos alunos (nome e médias das disciplinas).
- Cálculo da média geral de cada aluno.
- Ordenação dos alunos com base na média geral.
- Classificação dos alunos conforme suas médias.
- Salvamento dos dados em um arquivo de texto.
- Verificação das notas para garantir que estejam entre 0 e 10.
- Opção de abrir o arquivo criado após o cadastramento dos dados.

## Estrutura de Dados

O programa utiliza uma `struct` chamada `Aluno` para armazenar os dados:

```c
typedef struct {
    char nome[50];
    float mediaDisciplina1;
    float mediaDisciplina2;
    float mediaGeral;
    char classificacao[20];
} Aluno;

