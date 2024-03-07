#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define ALPHABET_SIZE 26

// Função para verificar se a chave é válida
int is_valid_key(char *key);

// Função para criptografar o texto
void encrypt_text(char *plaintext, char *key);

int main(int argc, char *argv[])
{
    // Verificar o número de argumentos da linha de comando
    if (argc != 2)
    {
        printf("Uso: ./substitution chave\n");
        return 1;
    }

    // Verificar se a chave é válida
    if (!is_valid_key(argv[1]))
    {
        printf("A chave deve conter 26 caracteres alfabéticos únicos.\n");
        return 1;
    }

    // Solicitar o texto simples ao usuário
    printf("plaintext: ");
    char plaintext[1000];
    fgets(plaintext, sizeof(plaintext), stdin);

    // Remover a nova linha adicionada por fgets
    size_t length = strlen(plaintext);
    if (length > 0 && plaintext[length - 1] == '\n')
    {
        plaintext[length - 1] = '\0';
    }

    // Criptografar e imprimir o texto cifrado
    printf("ciphertext: ");
    encrypt_text(plaintext, argv[1]);
    printf("\n");

    return 0;
}

int is_valid_key(char *key)
{
    // Verificar se a chave tem o tamanho correto
    if (strlen(key) != ALPHABET_SIZE)
    {
        return 0;
    }

    // Verificar se cada caractere é alfabético e único
    int seen[ALPHABET_SIZE] = {0};
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        char c = key[i];

        if (!isalpha(c))
        {
            return 0;
        }

        int index = tolower(c) - 'a';

        if (seen[index])
        {
            return 0;
        }

        seen[index] = 1;
    }

    return 1;
}

void encrypt_text(char *plaintext, char *key)
{
    // Iterar sobre cada caractere no texto simples
    for (int i = 0; plaintext[i] != '\0'; i++)
    {
        char c = plaintext[i];

        // Verificar se o caractere é alfabético
        if (isalpha(c))
        {
            // Preservar o caso (maiúscula/minúscula) do caractere
            char base = isupper(c) ? 'A' : 'a';

            // Calcular o índice do caractere na chave
            int index = tolower(c) - 'a';

            // Substituir o caractere pelo caractere correspondente na chave
            printf("%c", isupper(c) ? toupper(key[index]) : tolower(key[index]));
        }
        else
        {
            // Reproduzir caracteres não alfabéticos inalterados
            printf("%c", c);
        }
    }
}

// check50 cs50/problems/2021/x/substitution
