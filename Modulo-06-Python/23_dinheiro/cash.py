from cs50 import get_float

# Pede a entrada do usuário até receber uma válida
dollars = 0
while (dollars <= 0):
    dollars = get_float("Troco devido: ")

coins = 0
cents = round(dollars * 100, 0)

# Conta as moedas até o troco devido ser 0
while (cents > 0):
    if (cents >= 25):
        cents -= 25
        coins += 1
    elif (cents >= 10):
        cents -= 10
        coins += 1
    elif (cents >= 5):
        cents -= 5
        coins += 1
    else:
        cents -= 1
        coins += 1

# Exibe o número total de moedas necessárias para dar o troco
print(f"Você deve {coins} moedas")
