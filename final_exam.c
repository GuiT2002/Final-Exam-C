#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ESTUDANTES 100

typedef struct {
    char nome[50];
    int matricula;
    float notas[3];
    int ausencias;
} Estudante;

// Função para ler os dados dos estudantes
void lerEstudantes(Estudante estudantes[], int *numEstudantes) {
    printf("Digite o número de estudantes: ");
    scanf("%d", numEstudantes);
    getchar(); // Limpa o buffer do teclado
    
    for (int i = 0; i < *numEstudantes; i++) {
        printf("\nEstudante %d\n", i + 1);
        
        printf("Nome: ");
        fgets(estudantes[i].nome, 50, stdin);
        
        printf("Matrícula: ");
        scanf("%d", &estudantes[i].matricula);
        
        printf("Notas (separadas por espaço): ");
        scanf("%f %f %f", &estudantes[i].notas[0], &estudantes[i].notas[1], &estudantes[i].notas[2]);
        
        printf("Número de ausências: ");
        scanf("%d", &estudantes[i].ausencias);
        
        getchar(); // Limpa o buffer do teclado
    }
}

// Função para calcular a média das notas
float calcularMedia(float notas[]) {
    float soma = 0;
    for (int i = 0; i < 3; i++) {
        soma += notas[i];
    }
    return soma / 3;
}

// Função para arredondar a nota para o múltiplo de 0.5 mais próximo
float arredondarNota(float nota) {
    return roundf(nota * 2) / 2;
}

// Função para calcular a situação do estudante (aprovado, reprovado ou recuperação)
void calcularSituacao(Estudante estudante, float mediaFinal, int *aprovados, int *reprovados, int *recuperacao) {
    float media = calcularMedia(estudante.notas);
    float presenca = 100 - (estudante.ausencias * 100 / 72); // Calcula o percentual de presença assumindo 72 horas de aula no semestre
    
    if (presenca < 75 || mediaFinal < 3) {
        (*reprovados)++;
        printf("Matrícula: %d, Média Final: %.1f, Situação: Reprovado\n", estudante.matricula, mediaFinal);
    } else if (mediaFinal >= 6) {
        (*aprovados)++;
        printf("Matrícula: %d, Média Final: %.1f, Situação: Aprovado\n", estudante.matricula, mediaFinal);
    } else if (mediaFinal >= 3 && mediaFinal <= 5.5) {
        (*recuperacao)++;
        printf("Matrícula: %d, Média Final: %.1f, Situação: Recuperação\n", estudante.matricula, mediaFinal);
    }
}

// Função para calcular a média final de cada estudante e apresentar os resultados
void calcularMediaFinal(Estudante estudantes[], int numEstudantes) {
    int aprovados = 0, reprovados = 0, recuperacao = 0;
    
    for (int i = 0; i < numEstudantes; i++) {
        float media = calcularMedia(estudantes[i].notas);
        float mediaFinal = arredondarNota(media);
        
        calcularSituacao(estudantes[i], mediaFinal, &aprovados, &reprovados, &recuperacao);
    }
    
    printf("\nQuantidade de estudantes:\n");
    printf("Aprovados: %d\n", aprovados);
    printf("Reprovados: %d\n", reprovados);
    printf("Recuperação: %d\n", recuperacao);
}

int main() {
    Estudante estudantes[MAX_ESTUDANTES];
    int numEstudantes;
    
    lerEstudantes(estudantes, &numEstudantes);
    calcularMediaFinal(estudantes, numEstudantes);
    
    return 0;
}


