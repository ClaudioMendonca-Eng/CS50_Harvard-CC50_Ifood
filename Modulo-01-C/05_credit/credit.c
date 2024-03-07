#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Solicitar o número do cartão de crédito ao usuário
    long card_number;
    do
    {
        card_number = get_long("Número: ");
    }
    while (card_number <= 0);

    // Variáveis para armazenar a soma dos dígitos
    int sum1 = 0, sum2 = 0;

    // Variável para acompanhar a posição do dígito atual
    int position = 1;

    // Copia do número do cartão para não modificar o original
    long temp = card_number;

    // Loop através dos dígitos do número do cartão
    while (temp > 0)
    {
        // Pega o dígito atual
        int digit = temp % 10;

        // Multiplica cada segundo dígito por 2
        if (position % 2 == 0)
        {
            digit *= 2;

            // Se o produto tem dois dígitos, adiciona os dígitos
            sum1 += digit / 10 + digit % 10;
        }
        else
        {
            // Soma os dígitos que não foram multiplicados por 2
            sum2 += digit;
        }

        // Move para o próximo dígito
        temp /= 10;
        position++;
    }

    // Soma total dos dígitos
    int total_sum = sum1 + sum2;

    // Verifica se o número é válido de acordo com o algoritmo de Luhn
    if (total_sum % 10 == 0)
    {
        // Identifica a bandeira do cartão VISA
        if ((position - 1 == 16 && (card_number / 1000000000000000 == 4)) ||
            (position - 1 == 13 && (card_number / 1000000000000 == 4)))
        {
            printf("VISA\n");
        }
        else if (position - 1 == 16 && (card_number / 100000000000000 >= 51 && card_number / 100000000000000 <= 55))
        {
            printf("MASTERCARD\n");
        }
        else if ((position - 1 == 15 && (card_number / 10000000000000 == 34 || card_number / 10000000000000 == 37)))
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

}
