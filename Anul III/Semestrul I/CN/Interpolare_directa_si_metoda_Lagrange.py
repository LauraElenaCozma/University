import numpy as np
import matplotlib.pyplot as plt


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

def meg_pivotare_totala(a, b):
    """
    Metoda Gauss cu pivotare totala
    Se da sistemul Ax = b
    :return: rezultatul sistemului
    """

    """ Verifica daca matricea A este patratica + compatibilitatea cu vectorul b"""
    assert a.shape[0] == a.shape[1], 'Matricea sistemului nu este patratica'
    assert a.shape[0] == b.shape[0], 'Matricea sistemului si vectorul b nu se potrivesc'

    """ Verificare daca sistemul are solutie unica """
    if np.linalg.det(a) == 0:
        raise AssertionError('Sistemul nu are solutie unica')


    a_ext = np.concatenate((a, b[:, None]), axis = 1)
    n = b.shape[0]
    idx = np.array([i for i in range(n)])

    for k in range(n-1):
        """ Aflam pozitia pivotului de pe coloana k + verificare compatibilitate sistem"""
        """ Verificam daca in submatricea care incepe cu linia si coloana k exista elemente nenule"""
        if not a_ext[k:, k:n].any():
            raise AssertionError('Sistem incompatibil sau sistem compatibil nedeterminat')
        else:
            """ Alegem pozitia pivotul"""
            p = np.unravel_index(np.argmax(np.abs(a_ext[k:, k:n])),a_ext[k:, k:n].shape)
            p = (p[0] + k, p[1] + k)   #pe prima pozitie este linia, iar pe a doua este coloana

        """ Schimba linia 'k' cu 'p' daca linia pivotului nu este k."""
        if k != p[0]:
            a_ext[[p[0], k], :] = a_ext[[k, p[0]], :]  #interschimba liniile

        """ Schimba coloana 'k' cu 'p' daca coloana pivotului nu este k. Marcam schimbarea in idx"""
        if k != p[1]:
            a_ext[:, [p[1], k]] = a_ext[:, [k, p[1]]]  #interschimba coloanele
            idx[p[1]], idx[k] = idx[k], idx[p[1]]

        """ Zero sub pozitia pivotului pe coloana. """
        for j in range(k + 1, n):
            m = a_ext[j, k] / a_ext[k, k]
            a_ext[j, :] -= m * a_ext[k, :]

    """ Verifica compatibilitate again."""
    """ Elementul din dreapta jos trebuie sa fie diferit de 0"""
    if a_ext[n-1, n-1] == 0:
        raise AssertionError('Sistem incompatibil sau sistem compatibil nedeterminat')

    """ Gaseste solutia numerica folosind metoda substitutiei descendente. """
    x_num = subs_desc(a_ext[:, :-1], a_ext[:, -1])
    """ Permutam solutiile conform idx """
    x_num_ = np.empty(x_num.shape)
    for i in range(n):
        x_num_[idx[i]] = x_num[i]
    return x_num_

def array_puteri_x(x, n):
    x_array = np.zeros(n)
    #np.vander(X, len(X), increasing=True)
    power_x = 1
    for i in range(n):
        x_array[i] = power_x
        power_x *= x
    return x_array

# Implementeaza metoda directa de interpolare Lagrange
def interpolare_directa(X, Y, pointx):
    """ Metoda directa de calculare a polinomului de interpolare Lagrange.
    :param X: X = [X0, X1, ..., Xn]
    :param Y: [Y0=f(X0), Y1=F(X1), ..., Yn=f(Xn)]
    :param pointx: Punct in care doresti o valoare aproximata a functiei
    :return: aprox_value: Valoarea aproximata calculata folosind polinomul Lagrange in pointx
    """

    """
    1. Creaza o metoda care returneaza un vector care contine elementul 'x' ridicat la puteri consecutive
    pornind de la 0 si pana la n.
    """
    n = np.shape(X)[0]
    """
    2. Folosindu-te de metoda de mai sus, scrie elementele matricei folosite in metoda directa de aflare a polinomului 
    de interpolare Lagrange.
    """
    a = np.zeros([n, n])
    for i in range(n):
        a[i,:] = array_puteri_x(X[i], n)
    """
    3. Gaseste coeficientii polinomului rezolvand sistemul rezultat (matricea de la punctul 2 si valorile Y).
    """
    x_sol = meg_pivotare_totala(a, Y)
    """
    4. Foloseste metoda de la pasul 1 pentru ca crea un vector ce contine punctul in care doresti aproximarea ridicat la 
    puteri consecutive pornind de la 0 si pana la n.
    """
    f_in_punct = array_puteri_x(pointx, n)
    """
    5. Folosindu-te de vectorul de la pasul 4 si coeficientii de la pasul 3, afla valoarea aproximata i.e. P(x_aprox),
    unde P este polinomul de interpolare Lagrange rezultat din metoda directa.
    """
    aprox_value = np.dot(x_sol, f_in_punct)

    return aprox_value

def numarator_L(n, k, x, X_array):
    funct = 1
    for i in range(n):
        if i != k:
            funct = funct * (x - X_array[i])

    return funct

def metoda_lagrange(X, Y, pointx):
    """ Metoda Lagrange de calcularea a polinomului de interpolare Lagrange.
    :param X: X = [X0, X1, ..., Xn]
    :param Y: [Y0=f(X0), Y1=F(X1), ..., Yn=f(Xn)]
    :param pointx: Punct in care doresti o valoare aproximata a functiei
    :return: aprox_value: Valoarea aproximata calculata folosind polinomul Lagrange in pointx
    """
    n = np.shape(X)[0]
    aprox_value = 0
    for k in range(n):
        num_L = numarator_L(n, k, pointx, X)
        numitor_L = numarator_L(n, k, X[k], X)
        aprox_value += Y[k] * (num_L)/(numitor_L)

    return aprox_value

# ======================================================================================================================
# Date exacte
# ======================================================================================================================
# Functie cunoscuta
def aplication_function(x):
    """ Functia din exercitiu. """
    y = np.sin(2*x) - 2*np.cos(3*x)

    return y

toy_function = aplication_function  # Al doilea exemplu

# Intervalul dat
interval = [-np.pi, np.pi]  # [a, b]

x_domain = np.linspace(interval[0], interval[1], 100)  # Discretizare domeniu (folosit pentru plotare)
y_values = toy_function(x_domain)  # Valorile functiei exacte in punctele din discretizare

# Afisare grafic figure
plt.figure(0)
plt.plot(x_domain, y_values, c='k', linewidth=2, label='Functie exacta')
plt.xlabel('x')
plt.ylabel('y = f(x)')
plt.grid()

# ======================================================================================================================
# Datele clientului
# ======================================================================================================================

# Nodurile de interpolare
N = 20  # Gradul maxim al polinomului

x_client = np.linspace(interval[0], interval[1], N+1)  # Discretizare interval (nodurile date de client)
y_client = toy_function(x_client)  # Valorile functiei in nodurile date de client

# Afisare date client pe grafic
plt.scatter(x_client, y_client, marker='*', c='red', s=200, label='Date client')

# Calculare discretizare polinom
y_interp_direct = np.zeros(len(x_domain))  # Folosit pentru a stoca valorile aproximate
y_interp_lagrange = np.zeros(len(x_domain))  # Folosit pentru a stoca valorile aproximate
for i in range(len(x_domain)):
    y_interp_direct[i] = interpolare_directa(x_client, y_client, x_domain[i])  # TODO: Trebuie sa scrieti voi metoda
    y_interp_lagrange[i] = metoda_lagrange(x_client, y_client, x_domain[i])  # TODO: Trebuie sa scrieti voi metoda


# Afisare grafic aprixomare
plt.plot(x_domain, y_interp_direct, c='r', linewidth=1, linestyle='--', label='Metoda directa')
plt.plot(x_domain, y_interp_lagrange, c='b', linewidth=1, linestyle='-.', label='Metoda Lagrange')
plt.title('Interpolare Lagrange, N={}'.format(N))
plt.legend()
plt.show()
