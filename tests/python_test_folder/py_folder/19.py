nombre = 12345
somme = 0
while nombre > 0:
    somme += nombre % 10
    nombre //= 10
print("La somme des chiffres du nombre est", somme)
