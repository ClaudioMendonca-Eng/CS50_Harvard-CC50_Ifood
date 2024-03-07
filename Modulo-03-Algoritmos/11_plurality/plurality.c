#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Número máximo de candidatos
#define MAX 9

// Estrutura para representar um candidato
typedef struct
{
    string name;  // Nome do candidato
    int votes;    // Contagem de votos do candidato
}
candidate;

// Array de candidatos
candidate candidates[MAX];

// Número de candidatos
int candidate_count;

// Protótipos de funções
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Verifica o uso inválido
    if (argc < 2)
    {
        printf("Uso: plurality [candidato ...]\n");
        return 1;
    }

    // Preenche o array de candidatos
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Número máximo de candidatos é %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Número de eleitores: ");

    // Loop sobre todos os eleitores
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Voto: ");

        // Verifica voto inválido
        if (!vote(name))
        {
            printf("Voto inválido.\n");
        }
    }

    // Exibe o vencedor da eleição
    print_winner();
}

// Atualiza a contagem de votos dado um novo voto
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Imprime o vencedor (ou vencedores) da eleição
void print_winner(void)
{
    int max_votes = 0;

    // Encontra o número máximo de votos
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > max_votes)
        {
            max_votes = candidates[i].votes;
        }
    }

    // Imprime os nomes dos candidatos com o máximo de votos
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == max_votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
}
