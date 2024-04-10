from cs50 import get_string
from math import floor

AE1 = "34"
AE2 = "37"
MC1 = "51"
MC2 = "52"
MC3 = "53"
MC4 = "54"
MC5 = "55"
Visa = "4"
brand = "INVALID\n"

# obter e limpar a entrada do usuário
cartao = get_string("Número do Cartão*: ")
cartao = cartao.strip()
count = len(cartao)

# comparar os primeiros 2 dígitos com os códigos salvos e atribuir uma marca
if (count == 13):
    if (cartao[:1] == Visa):
        brand = "VISA"

elif (count == 15):
    if (cartao[:2] == AE1 or cartao[:2] == AE2):
        brand = "AMEX"

elif (count == 16):
    if (cartao[:2] == MC1 or cartao[:2] == MC2 or cartao[:2] == MC3 or cartao[:2] == MC4 or cartao[:2] == MC5):
        brand = "MASTERCARD"

    elif (cartao[:1] == Visa):
        brand = "VISA"

# se o número de dígitos estiver correto, verifica se o Algoritmo de Luhn é respeitado, caso contrário, retorna INVÁLIDO
if (brand != "INVALID\n"):
    cartao = int(cartao)
    ultimo = 0
    tempx = 0
    secToLast = 0

    # ele pega números ímpares e pares começando pelo final e os soma
    while (cartao > 0):
        ultimo += cartao % 10

        # elimina o último dígito para podermos acessar o primeiro número par do final
        cartao /= 10
        cartao = floor(cartao)

        tempx = (cartao % 10) * 2

        # se o número par * 2 for 10 ou maior, ele pega os dígitos individuais e os adiciona ao restante dos ímpares
        if (tempx >= 10):
            secToLast += tempx % 10
            tempx /= 10
            secToLast += floor(tempx)

        # se o número par * 2 for 9 ou menos, ele simplesmente o adiciona aos outros
        else:
            secToLast += tempx

        cartao /= 10
        cartao = floor(cartao)

    # se validar o Algoritmo, imprime a marca
    if ((ultimo + secToLast) % 10 == 0):
        print(brand)

    else:
        print("INVALID\n")

# novamente, imprime inválido se o número de dígitos não estiver correto desde o início
else:
    print(brand)
