"""
Cozma Laura-Elena, Manolache Andrei
Grupa 344
Paper 31_Boyd
Pentru partea experimentala, am comparat cele 2 histograme pentru L1 si L2 norm penalty loss
"""

import matplotlib.pyplot as plt
import numpy as np
from numpy import linalg as la
import random

from scipy import optimize

"""Generam datele, folosindu-ne de o functie genRand() care genereaza un numar intreg aleator intre -5 si 5"""


def genRand():
    startRandom = -5
    endRandom = 5
    return random.randrange(startRandom, endRandom)


"""Definim functia pe care vrem sa o minimizam pentru L1 norm """


def func_1(x):
    global A
    global b
    r = A @ x - b
    return np.sum(np.abs(r))


"""Definim functia pe care vrem sa o minimizam pentru L2 norm """


def func_2(x):
    global A
    global b
    r = A @ x - b
    return np.sum(np.power(r, 2))


"""Functie care calculeaza gradientul pentru L2 Norm"""


def gradient_l2(x):
    global A
    global b
    return 2 * A.T @ A @ x - 2 * A.T @ b


"""Functie care minimizeaza functia respectiva, folosind metoda gradientului cu pas ideal"""


def gradient_pas_ideal(Q, x, eps=1e-5):
    while True:
        """Calculeaza alpha, face update lui x, adauga noua eroare obtinuta"""
        grad = gradient_l2(x)

        alpha = (la.norm(grad) ** 2) / (grad.T @ Q @ grad)
        x = x - alpha * grad
        criteriu_stop = cond_oprire_norma_l2(x)

        if criteriu_stop < eps:
            break

    return x


"""Functie reprezentand conditia de opririre pt L1 Norm. Cat de aproape sunt de solutia exacta """


def cond_oprire_norma_l1(x_k):
    global A
    global b
    global x_sol_min_l1
    return np.sum(np.abs(x_k - x_sol_min_l1))


"""Functie reprezentand conditia de opririre pt L2 Norm. Cat de aproape sunt de solutia exacta """


def cond_oprire_norma_l2(x_k):
    global A
    global b
    global x_sol_min_l2
    r = x_k - x_sol_min_l2
    return np.sum(r @ r)


"""Functie care aplica metoda Reweigthed least squares pentru a determina minimul functiei """


def reweigthed_least_squares(A, b, eps):
    global max
    """Variabile contor pentru a returna cea mai buna solutie obtinuta"""
    min_diff = 1e10
    min_sol = []
    nr_max_it = 2000
    k = 0
    """Valoarea aleasa pentru regularizare"""
    delta = 1e-9
    """Construieste matricea diagonala de ponderi, initial este In"""
    n = b.size
    W = np.eye(n)
    while True:
        k += 1
        """Construieste solutia obtinuta la pasul curent"""
        x = np.linalg.inv(A.T @ W @ A) @ A.T @ W @ b
        """Updateaza matricea de ponderi"""
        for i in range(n):
            v2 = np.abs(b[i] - A[i] @ x)
            maxValue = max(v2, delta)
            W[i, i] = 1 / maxValue
        """Verifica daca am obtinut o solutie suficient de buna"""
        diff = cond_oprire_norma_l1(x)
        if diff < eps:
            return x

        if diff < min_diff:
            min_diff = diff
            min_sol = x

        if k > nr_max_it:
            return min_sol


"""Alegem dimensiunile m,n si generam A si b """
m = 150
n = 80
A = np.array([np.array([genRand() for i in range(0, n)]) for j in range(0, m)])
b = np.array([genRand() for _ in range(0, m)])
"""Setam eroarea, calculam pe Q si setam punctul de start"""
eps = 3
Q = 2 * A.T @ A
x0 = np.array([genRand() for _ in range(0, n)])

"""Calculeaza valoarea minima a functiei"""
x_start = np.array([genRand() for _ in range(0, n)])
x_sol_min_l1 = optimize.minimize(func_1, x_start, method="SLSQP").x
x_sol_min_l2 = optimize.minimize(func_2, x_start, method="SLSQP").x

print("X minim L1 este ---- ")
print(x_sol_min_l1)
print("-------------------")

print("X minim L2 este ---- ")
print(x_sol_min_l2)
print("-------------------")

""" Calculeaza solutia pentru fiecare norma """
x_sol_ideal_l1 = reweigthed_least_squares(A, b, eps)
x_sol_ideal_l2 = gradient_pas_ideal(Q, x0, eps)

bins = [i for i in np.arange(-0.35, 0.35, 0.01)]

"""Afiseaza histogramele pentru cele 2 aproximari obtinute """
plt.figure(0)
plt.hist(x_sol_ideal_l1 - x_sol_min_l1, bins=bins)
plt.title("L1 norm penalty")
plt.show()

plt.figure(1)
plt.hist(x_sol_ideal_l2 - x_sol_min_l2, bins=bins)
plt.title("L2 norm penalty")
plt.show()
