#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Verifica se o programa foi executado com exatamente um argumento de linha de comando
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Verifica se todos os caracteres do argumento são dígitos
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // Converte o argumento da linha de comando de uma string para int
    int jump = atoi(argv[1]);

    // Solicita o texto simples ao usuário
    string plaintext = get_string("plaintext: ");

    printf("ciphertext: ");

    // Itera sobre cada caractere do texto simples
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        // Verifica se é uma letra maiúscula
        if (isupper(plaintext[i]))
        {
            // Rotaciona a letra preservando a capitalização e imprime
            printf("%c", (plaintext[i] - 'A' + jump) % 26 + 'A');
        }
        // Verifica se é uma letra minúscula
        else if (islower(plaintext[i]))
        {
            // Rotaciona a letra preservando a capitalização e imprime
            printf("%c", (plaintext[i] - 'a' + jump) % 26 + 'a');
        }
        else
        {
            // Se não for uma letra, imprime o caractere como está
            printf("%c", plaintext[i]);
        }
    }

    // Imprime uma nova linha
    printf("\n");

    // Retorna 0 indicando sucesso
    return 0;
}
