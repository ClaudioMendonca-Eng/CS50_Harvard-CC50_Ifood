#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float troco;

    // Solicitar ao usuário o valor do troco até obter um valor não negativo
    do
    {
        troco = get_float("Troco devido: ");
    }

    while (troco < 0);

    // Converter os reais em centavos e arredondar
    int centavos = round(troco * 100);

    // Inicializar contadores para cada tipo de moeda
    int moedas25 = 0, moedas10 = 0, moedas5 = 0, moedas1 = 0;

    // Calcular o número mínimo de moedas
    while (centavos >= 25)
    {
        centavos -= 25;
        moedas25++;
    }

    while (centavos >= 10)
    {
        centavos -= 10;
        moedas10++;
    }

    while (centavos >= 5)
    {
        centavos -= 5;
        moedas5++;
    }

    while (centavos >= 1)
    {
        centavos -= 1;
        moedas1++;
    }

    // Imprimir o número mínimo de moedas
    printf("%d\n", moedas25 + moedas10 + moedas5 + moedas1);

}
