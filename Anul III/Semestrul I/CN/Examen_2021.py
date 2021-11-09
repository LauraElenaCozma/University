import numpy as np
import matplotlib.pyplot as plt
import math
import copy

def FactLLT(a):
    """
    Functie care aplica descompunerea Cholesky pe matricea a
    Vom afla matricea L, astfel incat L*L_transpus = a
    """
    """Pasul 1"""
    """ Verifica daca matricea A este patratica """
    assert a.shape[0] == a.shape[1], 'Matricea sistemului nu este patratica'

    """ Pentru a admite descompunerea Cholesky, matricea trebuie sa fie simetrica si pozitiv definita. """
    """ Verificare simetrie: A trebuie sa fie egal cu A transpus (va admite o eroare de calcul de 1e-8) """
    if not np.all(np.abs(a - a.T) < 1e-8):
        raise AssertionError('Matricea nu e simetrica')

    """ Verificare pozitiv definita: folosind criteriul lui Sylvester, toti minorii de colt > 0 """
    n = a.shape[0]
    for k in range(n):
        if np.linalg.det(a[:k + 1, :k + 1]) <= 0:
            raise AssertionError('Matricea nu e pozitiv definita')
    # copiem in S a
    S = copy.copy(a)
    L = np.zeros(a.shape)
    n = a.shape[0]

    for k in range(n-1):
        """ Determinam elementele diagonale ale matricei L"""
        L[k, k] = np.sqrt(S[0, 0])
        #print(L)
        """ Determina coloana k a matricei L"""
        for i in range(k+1, n):
            L[i, k] = S[i-k, 0]/np.sqrt(S[0, 0])
        #print(L)
        #print(S)
        """ Reducem complementul Schur"""
        for i in range(k+1, n):
            for j in range(k+1, n):
                S[i-k, j-k] = S[i-k, j-k] - ((S[i-k, 0] * S[0, j-k])/S[0, 0])
        #print("S=")
        #print(S)
    """ Pasul 4"""
    L[n-1][n-1] = np.sqrt(S[0][0])
    return L



def subs_desc(a, b):
    """ Metoda substitutiei descendente """

    """ Verifica daca matricea A este patratica + compatibilitatea cu vectorul b"""
    assert a.shape[0] == a.shape[1], 'Matricea sistemului nu este patratica'
    assert a.shape[0] == b.shape[0], 'Matricea sistemului si vectorul b nu se potrivesc'

    """ Initializeaza vectorul solutiei numerice."""
    n = b.shape[0] - 1
    x_num = np.zeros(shape=n+1)

    """ Determina solutia numerica."""
    x_num[n] = b[n] / a[n, n]        # Scrie ultima componenta a solutiei numerice
    # Parcurgem liniile de la final si aflam xk la fiecare pas
    for k in range(n-1, -1, -1):
        s = np.dot(a[k, k + 1:], x_num[k + 1:])
        x_num[k] = (b[k] - s) / a[k, k]

    return x_num

def subs_asc(a, b):
    """ Metoda substitutiei ascendente """

    assert a.shape[0] == a.shape[1], 'Matricea sistemului nu este patratica'
    assert a.shape[0] == b.shape[0], 'Matricea sistemului si vectorul b nu se potrivesc'

    """ Initializeaza vectorul solutiei numerice."""
    n = b.shape[0]
    x_num = np.zeros(shape=n)

    """ Determina solutia numerica."""
    x_num[0] = b[0] / a[0, 0]  # Scrie prima componenta a solutiei numerice

    # Parcurgem liniile de la inceput si aflam xk la fiecare pas
    for k in range(1, n):
        s = np.dot(a[k, :k], x_num[:k])
        x_num[k] = (b[k] - s) / a[k, k]

    return x_num


A = np.array([
    [25., 15., -5.],
    [15., 18., 0.],
    [-5., 0., 11.]
])

b = np.array([1., 2., 3.])
L = FactLLT(A)
print('Matricea L:')
print(L)
print('Matricea L transpus:')
print(L.T)
print('Verificare LL_transpus = A:')
A_check_cholesky = np.matmul(L, L.T)
print(A_check_cholesky)

y = subs_asc(L, b)
b_1 = np.matmul(L, y)

# solutia sistemului
x = subs_desc(L.T, y)
print(x)



#################################################################
###########3 Exercitiul 2 ###################
def newton_raphson(f, df, x0, eps):
    """
    Conditii:
    f de clasa C2
    f', f'' nu se anuleaza pe [a,b]
    f(x0) * f"(x0) > 0 -- ca sa convearga la x*
    """
    assert eps > 0, 'Mesaj eroare'

    #Verifica ca se indeplinesc si celelalte conditii din teorema prezentata
    x_old = x0
    N = 0
    #Iteratiile algoritmului
    while True:
        x_new = x_old - f(x_old)/df(x_old)
        N += 1

        if np.abs(x_new - x_old) < eps:
            break

        x_old = x_new

    return x_new, N

def f(x):
    return (x**3) + 3 *  (x**2) -28 * x


def df(x):
    return 3 * (x**2) + 6 * x - 28

def ddf(x):
    return 6 * x + 6
"""
f e de clasa C2
Calculm radacinile ec 3x^2 + 6x - 28 = 0
radacinile sunt x (-3 + sqrt(93))/3 (-3 - sqrt(93))/3, deci aprox 2.21 si -4.21


Calculam f'(0) = -28 <0 deci este negativ
Calculam f'(-5) = 17 > 0 deci pozitiv
Calculam f'(3) = 17 >0 deci pozitiv 

deci f e s.c pe (-inf, -4.2] reunit cu [2.2, inf)
si s d in rest

Calculam radacina derivatei de ord 2
x + 1 = 0 deci x = -1

x   -inf                  -4.2      -1         2.2             +inf
f'             + + +        0      - - - -      0    + + +
f''            - -                     0             + +                     
f   

Trebuie sa alegem subintervale astffel incat f' si f" sa nu se anuleze
Semnele lui f sa fie schimbate in capete

f(-8) = -96
f(-5) = 90
cum pe [-8; -5] nu se anuleaza f' si f'' si f(-8)*f(-5) < 0
Calculam f"(-8) = -42 deci f(-8) * f"(-8) > 0

Deci primul pct ales e -8 in [-8, -5]. La stanga lui -4.2 nu se vor mai afla alte radacini

Pentru [2.2, inf)
f' si f" nu se anuleaza
Calculam f(3) = -30
f(5) = 60
f(3) * f(5) < 0

f"(5) = 36
f"(5) * f(5) > 0 deci punctul 5 poate fi ales drept pct de start pe subintervalul   [3, 5], La dreapta lui 2.2 nu mai sunt solutii

Pentru [-4.2, 2.2]
Stim ca f" se anuleaza in -1
f(-4) = 96
f(-1) = 30 
f(2.1) = -36.3
Deci pe [-4.2, -1] functia scade, dar nu taie axa 0x deci nu vom avea radacini
Cautam radacina pe [-1, 2.2]
f(-0.9) = 26.9 
f(2) = -36
Deci pe acest interval vom avea o radacina
Din tabel stim ca f" e pozitiv
Deci cautam f pozitiv
f"(-0.9) = 0.59
Deci f(-0.9)*f"(-0.9) > 0 deci putem alege punct de start -0.9 pe subintervalul [-0.9, 2]
"""

x_new_1, N_1 = newton_raphson(f, df, -8, 10 **(-3))
print(x_new_1)

x_new_2, N_2 = newton_raphson(f, df, 5, 10 **(-3))
print(x_new_2)

x_new_3, N_3 = newton_raphson(f, df, -0.9, 10 **(-3))
print(x_new_3)

x = np.linspace(-30, 30, 100000) #discretizam intervalul
y = f(x)              #aplicam f pe valorile lui x ca sa aflam valorile lui y
plt.plot(x, y)                #plotam functia
plt.axvline(0, c = 'black')   #afisam axele de coordonate
plt.ylim(-5, 5)
plt.axhline(0, c = 'black')

plt.scatter(x_new_1, 0)                #construim punctele obtinute pe grafic
plt.scatter(x_new_2, 0)
plt.scatter(x_new_3, 0)
plt.title('Graficul functiei')
plt.show()

