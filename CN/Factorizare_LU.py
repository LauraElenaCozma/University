import numpy as np
import copy

"""Modifica codul de la subs_desc ca sa obtii subs_ascendenta"""
def subs_asc(a, b):
    assert a.shape[0] == a.shape[1], 'Matricea sistemului nu este patratica'
    assert a.shape[0] == b.shape[0], 'Matricea sistemului si vectorul b nu se potrivesc'

    """ Initializeaza vectorul solutiei numerice."""
    n = b.shape[0]
    x_num = np.zeros(shape=n)

    """ Determina solutia numerica."""
    x_num[0] = b[0] / a[0, 0]  # Scrie prima componenta a solutiei numerice
    # stim exact cate componente mai am de aflat, stiind ca este substitutie descendenta
    for k in range(1, n):  # Merge invers
        s = np.dot(a[k, :k], x_num[:k])
        x_num[k] = (b[k] - s) / a[k, k]

    return x_num

def subs_desc(a, b):
    """ (Optionala) Verifica daca matricea A este patratica + compatibilitatea cu vectorul b"""
    assert a.shape[0] == a.shape[1], 'Matricea sistemului nu este patratica'
    assert a.shape[0] == b.shape[0], 'Matricea sistemului si vectorul b nu se potrivesc'

    """ Initializeaza vectorul solutiei numerice."""
    n = b.shape[0] - 1
    x_num = np.zeros(shape=n+1)

    """ Determina solutia numerica."""
    x_num[n] = b[n] / a[n, n]        #Scrie ultima componenta a solutiei numerice
    #stim exact cate componente mai am de aflat, stiind ca este substitutie descendenta
    for k in range(n - 1, -1, -1):   #Merge invers
        s = np.dot(a[k, k + 1:], x_num[k + 1:])
        x_num[k] = (b[k] - s) / a[k, k]

    return x_num


def factorizare_LU(a):
    """
    Functie care calculeaza factorizarea LU cu pivotare partiala a lui A, afland P, L si U din PA = LU
    :param a: matricea careia i se calculeaza factorizarea LU
    :return: L, U si matricea permutarilor
    """

    """ Verifica daca matricea A este patratica """
    assert a.shape[0] == a.shape[1], 'Matricea sistemului nu este patratica'

    """ Verificare daca sistemul are solutie unica """
    if np.linalg.det(a) == 0:
        raise AssertionError('Sistemul nu are solutie unica')

    """
    Construim L, U si P. L initial este On, la care se va aduna la final In.
    P pleaca de la matricea identitate.
    U pleaca de la matricea a (am facut shallow copy pentru a putea folosi a pentru verificari).
    """
    L = np.zeros(a.shape)
    U = copy.copy(a)
    n = a.shape[0]
    P = np.identity(n)


    for k in range(n-1):
        """ Aflam pozitia pivotului de pe coloana k + verificare compatibilitate sistem"""
        if not U[k:, k].any():  # verificam daca exista cel putin o valoare nenula pe coloana k incepand cu pozitia k
            raise AssertionError('Matricea nu admite factorizarea LU')
        else:
            #aflam pozitia pivotului
            p = np.argmax(np.abs(U[k:, k]))
            p += k

        """ Schimba linia 'k' cu 'p' daca pivotul nu se afla pe diagonala pricipala."""
        if k != p:
            U[[p, k], :] = U[[k, p], :]  # interschimba liniile in U
            L[[p, k], :] = L[[k, p], :]  # interschimba liniile in L
            P[[p, k], :] = P[[k, p], :]  # interschimba liniile in P; semnalizam ca s-a produs o permutare a liniilor


        """ Zero sub pozitia pivotului pe coloana. """
        for j in range(k+1, n):
            m = U[j, k] / U[k, k]
            U[j, :] -= m * U[k, :]  #actualizam valorile din U
            L[j,k] = m              #actualizam L

    """ 
    Verifica compatibilitate again.
    Elementul din dreapta jos trebuie sa fie diferit de 0 pentru a fi un sistem compatibil determinat
    """
    if U[n-1, n-1] == 0:
        raise AssertionError('Sistem incompatibil sau sistem compatibil nedeterminat')

    # Adaugam matricea identitate la L
    L = L + np.identity(n)

    return L, U, P

def rezolvare_sistem(L, U, P, b):
    """
    Functie care pe baza unei factorizari LU rezolva sistemul Ax = b
    :param L: matrice inferior triunghiulara
    :param U: matrice superior triunghiulara
    :param P: matrice de permutari
    :param b: rezultatul ecuatiei Ax = b
    :return: solutia x_sol a sistemului Ax = b
    """

    """
    Deoarece PA = LU, atunci:
    Ax = b | *P la stanga
    PAx = Pb => LUx = Pb; aflam b_ = Pb
    """
    b_ = np.matmul(P,b)
    # Aflam Lx_num = b_, unde x_num = Ux
    x_num = subs_asc(L, b_)
    # Returnam solutia sistemului
    return subs_desc(U, x_num)



A = np.array([
   [2., 0., 0.],
   [2., 1., 0.],
   [3., 2., 1.]]);
b = np.array([2, 3, 6]).T

L, U, P = factorizare_LU(A)
print('Matricea L:')
print(L)
print('Matricea U:')
print(U)
print('====> Solutia sistemului este:')
x_sol = rezolvare_sistem(L, U, P, b)
print(x_sol)
print('Verificarea A:')
#Verificam daca PA = LU, adica daca A = P_inversa * L * U (matricile permutari P sunt inversabile)
P_inv = np.linalg.inv(P)
A_check = np.matmul(np.matmul(P_inv, L), U)
print(A_check)