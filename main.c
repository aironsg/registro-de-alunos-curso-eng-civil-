#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

/*
* NOME DA DISCIPLINA: ALGORITMOS E LÓGICA DE PROGRAMAÇÃO
    Unidade: 4 – APLICAÇÕES DE PROGRAMAÇÃO
    Aula: 4 – Registros e arquivos
    Curso: Eng.civil
 */

// Definindo a estrutura Aluno
typedef struct {
    char nome[50];
    float mediaDisciplina1;
    float mediaDisciplina2;
    float mediaGeral;
    char classificacao[20];
} Aluno;

// Função para calcular a média geral
float calcularMediaGeral(float mediaDisciplina1, float mediaDisciplina2) {
    return (mediaDisciplina1 + mediaDisciplina2) / 2;
}

// Função para comparação das médias para ordenação
int compararMedias(const void *a, const void *b) {
    Aluno *alunoA = (Aluno *)a;
    Aluno *alunoB = (Aluno *)b;
    if (alunoB->mediaGeral > alunoA->mediaGeral) return 1;
    if (alunoB->mediaGeral < alunoA->mediaGeral) return -1;
    return 0;
}

// Função para solicitar os dados do aluno
void solicitarDadosAluno(Aluno *aluno) {
    printf("Digite o nome do aluno: ");
    fgets(aluno->nome, 50, stdin);
    aluno->nome[strcspn(aluno->nome, "\n")] = '\0';

    // Solicitação e validação da média da disciplina 1
    do {
        printf("Digite a média da disciplina 1 (0-10): ");
        scanf("%f", &aluno->mediaDisciplina1);
        if (aluno->mediaDisciplina1 < 0 || aluno->mediaDisciplina1 > 10) {
            printf("Nota inválida! Insira uma nota entre 0 e 10.\n");
        }
    } while (aluno->mediaDisciplina1 < 0 || aluno->mediaDisciplina1 > 10);

    // Solicitação e validação da média da disciplina 2
    do {
        printf("Digite a média da disciplina 2 (0-10): ");
        scanf("%f", &aluno->mediaDisciplina2);
        if (aluno->mediaDisciplina2 < 0 || aluno->mediaDisciplina2 > 10) {
            printf("Nota inválida! Insira uma nota entre 0 e 10.\n");
        }
    } while (aluno->mediaDisciplina2 < 0 || aluno->mediaDisciplina2 > 10);

    getchar(); // Limpa o buffer
}

// Função para salvar os dados do aluno em um arquivo
void salvarDadosEmArquivo(Aluno aluno, FILE *arquivo) {
    fprintf(arquivo, "Nome do Aluno: %s\n", aluno.nome);
    fprintf(arquivo, "Média Disciplina 1: %.2f\n", aluno.mediaDisciplina1);
    fprintf(arquivo, "Média Disciplina 2: %.2f\n", aluno.mediaDisciplina2);
    fprintf(arquivo, "Média Geral: %.2f\n", aluno.mediaGeral);
    fprintf(arquivo, "Classificação: %s\n\n", aluno.classificacao);
}

// Função principal
int main() {
    // Configurando o locale para suportar caracteres acentuados
    setlocale(LC_ALL, "Portuguese_Brazil.1252");
    system("chcp 65001"); // Define a página de código para UTF-8

    int quantidadeAlunos;

    printf("Digite o número de alunos que serão registrados: ");
    scanf("%d", &quantidadeAlunos);
    getchar(); // Limpa o buffer

    // Alocando memória dinamicamente para suportar qualquer quantidade de alunos
    Aluno *alunos = malloc(quantidadeAlunos * sizeof(Aluno));
    if (alunos == NULL) {
        printf("Erro de alocação de memória!\n");
        return 1;
    }

    // Solicitando dados para cada aluno
    for (int i = 0; i < quantidadeAlunos; i++) {
        printf("\nAluno %d:\n", i + 1);
        solicitarDadosAluno(&alunos[i]);

        alunos[i].mediaGeral = calcularMediaGeral(alunos[i].mediaDisciplina1, alunos[i].mediaDisciplina2);
    }

    // Ordenando os alunos pela média geral
    qsort(alunos, quantidadeAlunos, sizeof(Aluno), compararMedias);

    // Atribuindo classificações
    for (int i = 0; i < quantidadeAlunos; i++) {
        if (i == 0 || alunos[i].mediaGeral == alunos[i - 1].mediaGeral) {
            strcpy(alunos[i].classificacao, "Primeiro Lugar");
        } else {
            sprintf(alunos[i].classificacao, "Posição %d", i + 1);
        }
    }

    // Criando ou abrindo o arquivo para salvar os dados
    FILE *arquivo = fopen("alunos.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        free(alunos);
        return 1;
    }

    // Salvando os dados de cada aluno no arquivo
    for (int i = 0; i < quantidadeAlunos; i++) {
        salvarDadosEmArquivo(alunos[i], arquivo);
    }

    // Calculando e escrevendo a média geral da turma
    float mediaGeralTurma = 0;
    for (int i = 0; i < quantidadeAlunos; i++) {
        mediaGeralTurma += alunos[i].mediaGeral;
    }
    mediaGeralTurma /= quantidadeAlunos;

    fprintf(arquivo, "Média Geral da Turma: %.2f\n", mediaGeralTurma);

    // Fechando o arquivo
    fclose(arquivo);
    printf("Dados dos alunos e média geral da turma salvos com sucesso!\n");

    // Perguntando ao usuário se deseja abrir o arquivo
    char opcao;
    printf("Deseja abrir o arquivo 'alunos.txt' para visualizar os dados? (s/n): ");
    scanf(" %c", &opcao);

    if (opcao == 's' || opcao == 'S') {
        system("cls"); // Limpa a tela no Windows

        // Reabrindo o arquivo para leitura
        arquivo = fopen("alunos.txt", "r");
        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo para leitura!\n");
            free(alunos);
            return 1;
        }

        // Mostrando o conteúdo do arquivo
        char linha[100];
        while (fgets(linha, sizeof(linha), arquivo) != NULL) {
            printf("%s", linha);
        }

        // Fechando o arquivo após a leitura
        fclose(arquivo);
    } else {
        printf("Programa encerrado.\n");
    }

    // Liberando a memória alocada
    free(alunos);

    return 0;
}
