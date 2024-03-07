#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Solicite o valor inicial ao usuário
    int tamanhoInicio;
    do
    {
        tamanhoInicio = get_int("Tamanho inicial: ");
    }
    while (tamanhoInicio < 9);

    // TODO: Solicite o valor final ao usuário
    int tamanhoFinal;
    do
    {
        tamanhoFinal = get_int("Tamanho final: ");
    }
    while (tamanhoFinal < tamanhoInicio);

    // TODO: Calcule o número de anos até o limite
    int anos = 0;
    while (tamanhoInicio < tamanhoFinal)
    {
        int nascimento = tamanhoInicio / 3;
        int morte = tamanhoInicio / 4;
        tamanhoInicio = tamanhoInicio + nascimento - morte;
        anos++;
    }

    // TODO: Imprima o número de anos
    printf("Years: %i\n", anos);

}
