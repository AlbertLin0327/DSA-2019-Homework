G = [0, 37, 0, 10, 27, 0, 20, 1, 30, 2, 3, 8, 21, 32, 35, 0, 32, 22, 7, 0, 0, 20, 7, 26, 10, 37, 6, 0, 36, 11, 27, 15, 3, 10, 17, 9, 2, 10]

S1 = [19, 18, 8, 17, 18, 27, 34, 35]
S2 = [12, 32, 2, 35, 17, 6, 16, 7]

def hash_f(key, T):
    result = 0
    for i, c in enumerate(key):
        result += T[i % 8] * ord(c)
    return result % 38

def perfect_hash(key):
    return (G[hash_f(key, S1)] + G[hash_f(key, S2)]) % 38

K = ["auto", "bool", "case", "char", "const", "continue","default", "do", "double", "else", "enum", "extern", "float", "for","goto", "if", "int", "long", "register", "return", "short", "signed","sizeof", "static", "struct", "switch", "template", "union","unsigned", "void", "volatile", "while"]

for word in K:
    print("hash the word:", word, "->", perfect_hash(word))
