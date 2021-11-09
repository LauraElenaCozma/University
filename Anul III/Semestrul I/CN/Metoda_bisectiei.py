import numpy as np
import matplotlib.pyplot as plt
import math

def f(x):
    return (x ** 3 - 7 * (x ** 2) + 14 * x - 6)

#a - Graficul functiei
x = np.arange(0, 4, 0.1)
y = f(x)
plt.plot(x, y)
plt.show()

def find_solution(f, a, b, eps):
    assert eps > 0, 'Epsilon trebuie sa aiba valoare pozitiva'
    assert a < b, 'Capetele intervalului sunt puse incorect'
    assert np.sign(f(a)) * np.sign(f(b)) < 0, 'Nu respecta conditia metodei bisectiei'
    num_it = int(np.floor(math.log2((b - a) / eps)))        #calculam numarul de iteratii
    fa = f(a)                                               #calculam functia in capetele intervalului
    fb = f(b)
    if fa == 0:                                             #am gasit solutia in capatul a
        return a, 0
    elif fb == 0:                                           #am gasit solutia in capatul b
        return b, 0
    for k in range(num_it):
        x = (a + b) / 2                                     #calculam mijlocul si valoarea functiei in mijloc
        fx = f(x)
        if fx == 0:                                         #daca am ajuns la solutie o returnam
            return x, (k + 1)
        else:

            if (fa * fx) < 0:                               #solutia se afla in partea stanga
                b = x
            elif (fb * fx) < 0:                             #solutia se afla in partea dreapta
                a = x
        fa = f(a)                                           #actualizam valorile fa si fb
        fb = f(b)
    return x, num_it                                        #am ajuns la solutie la finalul iteratiilor


sol1 , num1 = find_solution(f, 0, 1, 0.1 ** (5))
sol2, num2 = find_solution(f, 1, 3.2, 0.1 ** (5))
sol3, num3 = find_solution(f, 3.2, 4, 0.1 ** (5))

plt.plot(x, y)
plt.plot(sol1, f(sol1), "ro")
plt.plot(sol2, f(sol2), "ro")
plt.plot(sol3, f(sol3), "ro")
plt.show()

