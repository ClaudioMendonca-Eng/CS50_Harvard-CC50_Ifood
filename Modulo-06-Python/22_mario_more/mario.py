from cs50 import get_int

# Pede entrada do usuário ate que receba uma válida
height = 0
while (height > 8 or height < 1):
    height = get_int("Height:\n")

# Imprime uma pirâmide de hashes
for i in range(1, height +1):
    print(" " * (height -i), end="")
    print("#" * i, end="  ")
    print("#" * i)
