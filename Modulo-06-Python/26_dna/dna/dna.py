#: Importa as bibliotecas necessárias e os argumentos de linha de comando.
from csv import reader, DictReader
from sys import argv

# Verifica se há argumentos suficientes na linha de comando.
if len(argv) < 3:
    print("usage error, dna.py sequence.txt database.csv")
    exit()

# Lê a sequência de DNA do arquivo.
with open(argv[2]) as dnafile:
    dnareader = reader(dnafile)
    for row in dnareader:
        dnalist = row

# Armazena a sequência de DNA em uma string.
dna = dnalist[0]
# Cria um dicionário onde armazenaremos as sequências que pretendemos contar.
sequences = {}

# Extrai as sequências do banco de dados e as armazena em uma lista.
with open(argv[1]) as peoplefile:
    people = reader(peoplefile)
    for row in people:
        dnaSequences = row
        dnaSequences.pop(0)
        break

# Copia a lista em um dicionário onde os genes são as chaves.
for item in dnaSequences:
    sequences[item] = 1

# Itera pela sequência de DNA, quando encontra repetições dos valores do dicionário de sequências, conta-os.
for key in sequences:
    l = len(key)
    tempMax = 0
    temp = 0
    for i in range(len(dna)):
        # Após ter contado uma sequência, pula para o final dela para evitar contar novamente.
        while temp > 0:
            temp -= 1
            continue

        # Se o segmento de DNA corresponder à chave e houver uma repetição, começamos a contar.
        if dna[i: i + l] == key:
            while dna[i - l: i] == dna[i: i + l]:
                temp += 1
                i += l

            # Compara o valor com a sequência mais longa anterior e, se for mais longa, a substitui.
            if temp > tempMax:
                tempMax = temp

    # Armazena as sequências mais longas no dicionário usando a chave correspondente.
    sequences[key] += tempMax

# Abre e itera pelo banco de dados de pessoas, tratando cada uma como um dicionário para poder comparar com o dicionário de sequências.
with open(argv[1], newline='') as peoplefile:
    people = DictReader(peoplefile)
    for person in people:
        match = 0
        # Compara as sequências com cada pessoa e imprime o nome antes de sair do programa se houver uma correspondência.
        for dna in sequences:
            if sequences[dna] == int(person[dna]):
                match += 1
        if match == len(sequences):
            print(person['name'])
            exit()

    print("No match")
