#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>
#include <ctype.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Uso: recuperar forensicfilename.raw\n"); // Impressão do uso correto do programa
        return 1;
    }

    // Abertura do arquivo de imagem forense
    FILE *raw = fopen(argv[1], "r");
    if (raw == NULL)
    {
        printf("Não foi possível abrir %s.\n", argv[1]); // Mensagem de erro se o arquivo não puder ser aberto
        return 2;
    }

    // Declaração de variáveis e inicialização
    FILE *jpeg;
    BYTE block[512];
    bool foundjpeg = false; // Variável para indicar se um JPEG foi encontrado
    int readblock; // Variável para armazenar o número de blocos lidos
    int jpegnum = 0; // Variável para numerar os arquivos JPEG gerados

    // Loop para ler o arquivo de imagem forense em blocos de 512 bytes
    while (fread(block, sizeof(block), 1, raw) == 1)
    {
        // Verifica se o bloco atual é o início de um arquivo JPEG
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
        {
            char filename[8];

            // Gera o nome do arquivo JPEG com base no número sequencial
            sprintf(filename, "%03.3i.jpg", jpegnum);

            // Mensagem indicando o processamento do arquivo atual
            printf("Processando arquivo: %s\n", filename);

            // Fecha o arquivo JPEG anterior se encontrado, senão marca como encontrado
            if (foundjpeg == true)
            {
                fclose(jpeg);
            }
            else
            {
                foundjpeg = true;
            }

            // Abre um novo arquivo JPEG para escrita
            jpeg = fopen(filename, "w");
            fwrite(block, sizeof(block), 1, jpeg); // Escreve o bloco atual no arquivo JPEG
            jpegnum++; // Incrementa o número do arquivo JPEG
        }
        else
        {
            // Se já foi encontrado um arquivo JPEG, continua escrevendo no mesmo
            if (foundjpeg == true)
            {
                fwrite(block, sizeof(block), 1, jpeg);
            }
        }
    }

    // Fecha o arquivo de imagem forense e o último arquivo JPEG
    fclose(raw);
    fclose(jpeg);
}
