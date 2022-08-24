from pprint import pprint

lista = [1, 1, 3, 5, 8, 13, 21, 34]
eliminar = 3

pprint(lista)

lista[eliminar-1] = lista[-1]
lista.pop()

pprint(lista)