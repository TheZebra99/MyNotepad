import numpy as np


print('Введите первый вектор нового базиса:')
e1 = [float(x) for x in input().split()]
print('Введите второй вектор нового базиса:')
e2 = [float(x) for x in input().split()]
perehoda = np.matrix([e1, e2]).transpose()
print('Матрица перехода:')
print(perehoda)

invert = np.linalg.inv(perehoda)
print('Обратная матрица к матрице перехода:')
print(invert)

print('Введите первую строку тензора t:')
e1 = [float(x) for x in input().split()]
print('Введите вторую строку тензора t:')
e2 = [float(x) for x in input().split()]
t = np.matrix([e1, e2])

print('Введите первую строку тензора r:')
e1 = [float(x) for x in input().split()]
print('Введите вторую строку тензора r:')
e2 = [float(x) for x in input().split()]
r = np.matrix([e1, e2])

print('Введите первую строку тензора s:')
e1 = [float(x) for x in input().split()]
print('Введите вторую строку тензора s:')
e2 = [float(x) for x in input().split()]
s = np.matrix([e1, e2])

safter = np.matrix([[0, 0], [0, 0]])
rafter = np.matrix([[0, 0], [0, 0]])
tafter = np.matrix([[0, 0], [0, 0]])
for i in range(2):
    for j in range(2):
        for a in range(2):
            for b in range(2):
                safter[i, j] += invert[i, a] * invert[j, b] * s[a, b]
                rafter[j, i] += perehoda[a, i] * invert[j, b] * r[b, a]
                tafter[j, i] += perehoda[a, i] * perehoda[b, j] * t[b, a]

print('t в новом базисе:')
print(tafter)
print('r в новом базисе:')
print(rafter)
print('s в новом базисе:')
print(safter)
input()
