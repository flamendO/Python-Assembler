def est_premier(n):
    if n <= 1:
        return False
    for i in range(2, n):
        if n % i == 0:
            return False
    return True

nombres_premiers = []
n = 2
while len(nombres_premiers) < 10:
    if est_premier(n):
        nombres_premiers.append(n)
    n += 1

print("Les 10 premiers nombres premiers sont", nombres_premiers)
