#include <stdio.h>

#include <string.h>

#include <stdlib.h>

struct Aluno {
    char nome[50];
    char telefone[50];
    char curso[15];
    float nota1, nota2, media;
    char resultado_final[10];
};

void SortAlunosPorMediaDecrescente(struct Aluno lista_alunos[], int qtd_alunos) {

    struct Aluno temp;

    for (int i = 0; i < qtd_alunos; i++) {
        for (int j = i + 1; j < qtd_alunos; j++) {

            if (lista_alunos[i].media < lista_alunos[j].media) {
                temp = lista_alunos[i];
                lista_alunos[i] = lista_alunos[j];
                lista_alunos[j] = temp;
            }
        }
    }

} // Funcao para ordenar por media descrescente

float CalcMedia(float nota1, float nota2) {
    return (nota1 + nota2) / 2;
} // funcao para calcular a media

void Resultado(float media, char resultado_final[]) {
    if (media >= 7) {
        strcpy(resultado_final, "Aprovado");
    } else {
        strcpy(resultado_final, "Reprovado");
    }
} // funcao para definir o resultado final 

int main() {
    struct Aluno lista_alunos[100]; // vetor de alunos

    FILE * entrada;
    FILE * saida; // ponteiro para manipular arquivo

    entrada = fopen("DadosEntrada.csv", "r");
    saida = fopen("SituacaoFinal.csv", "w");

    int i = 0;

    if (entrada != NULL && saida != NULL) {
        char primeira_linha[1000]; // descartou a primeira linha (cabeçalho)
        fscanf(entrada, "%[^\n]\n", primeira_linha);

        while (fscanf(entrada, "%[^,],%[^,],%[^,],%f,%f\n",
                lista_alunos[i].nome,
                lista_alunos[i].telefone,
                lista_alunos[i].curso, &
                lista_alunos[i].nota1, &
                lista_alunos[i].nota2) != EOF) {
            lista_alunos[i].media = CalcMedia(lista_alunos[i].nota1, lista_alunos[i].nota2);
            Resultado(lista_alunos[i].media, lista_alunos[i].resultado_final);

            i++;

        }

        SortAlunosPorMediaDecrescente(lista_alunos, i);

        for (int k = 0; k < i; k++) {
            fprintf(saida,
                "%s,%.2f,%s\n", lista_alunos[k].nome, lista_alunos[k].media, lista_alunos[k].resultado_final);
        } // A lista já está ordenada por media

        printf("Arquivo gerado com sucesso.\n");

    } else {
        printf("Erro ao abrir o arquivo.\n");
    }

    fclose(entrada);
    fclose(saida);

    return 0;
}