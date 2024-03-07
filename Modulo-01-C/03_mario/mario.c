#include <cs50.h>
#include <stdio.h>


int main(void)
{
	int x;
	do
	{
		x = get_int("Numero positivo: ");
	}

	while (x < 1 || x > 8);
	{
		for(int i = 0; i < x; i++)
    	{
			for (int f = (x-2); f >= i; f--)
			{
					printf(" ");
			}
			for (int j = 0; j <= i; j++)
			{
					printf("#");
			}
            for (int j = 0; j <= 1; j++)
			{
					printf(" ");
			}
            for (int j = 0; j <= i; j++)
			{
					printf("#");
			}
			printf("\n");
    	}
	}
}
