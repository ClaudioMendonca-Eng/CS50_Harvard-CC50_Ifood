from cs50 import get_int

# Solicita altura da meia-pirâmide ao usuário
height = 0
while (height > 8 or height <1):
    height = get_int("Height:\n")

# mostra uma piramide em #
for i in range(1, height +1):
    print(" " * (height - i), end="")
    print("#" * (i))
