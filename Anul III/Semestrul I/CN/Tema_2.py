import numpy as np
import math
import copy

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


#######################################################################################

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


#############################################################################################


def calcul_inversa(a):
    """
    Calcularea inversei unei matrici a folosind metoda Gauss cu pivotare totala
    :return: a^(-1)
    """

    """
    Aplicam meg cu pivotare totala pentru calcularea inversei pentru a avea erori
    cat mai mici (daca este cazul)
    """

    """ Verifica daca matricea A este patratica """
    assert a.shape[0] == a.shape[1], 'Matricea sistemului nu este patratica'

    """ Verificare daca matricea e inversabila (determinantul e diferit de 0) """
    if np.linalg.det(a) == 0:
        raise AssertionError('Matricea nu e inversabila')

    n = a.shape[0]
    I = np.identity(n)
    A_inv = np.zeros(a.shape)

    """ 
    Stim ca A*A_inv = I
    Despartim matricile A_inv si I in coloane si calculam folosind meg fiecare coloana
    din A_inv.
    """
    for k in range(n):
        A_inv[:, k] = meg_pivotare_totala(a, I[:, k])

    return A_inv

#############################################################################################

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



#############################################################################################

def met_Cholesky(a):
    """
    Functie care aplica descompunerea Cholesky pe matricea a
    Vom afla matricea L, astfel incat L*L_transpus = a
    """

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

    L = np.zeros(a.shape)
    n = a.shape[0]
    alpha = a[0, 0]
    if alpha <= 0:
        raise AssertionError('Matricea nu e pozitiv definita. Nu se poate aplica metoda Cholesky')

    L[0,0] = math.sqrt(alpha)
    #Am calculat L[0][0], calculam elementele de pe prima coloana
    for i in range(1, n):
        L[i,0] = a[i, 0]/L[0, 0]

    for k in range(1, n):
        alpha = a[k, k] - np.dot(L[k, :k], L[k, :k])
        if alpha <= 0:
            raise AssertionError('Matricea nu e pozitiv definita. Nu se poate aplica metoda Cholesky')
        #calculam elementele de pe diagonala principala, dupa care restul elementelor
        L[k, k] = math.sqrt(alpha)

        for i in range(k+1,n):
            L[i,k] = 1/L[k,k] * (a[i,k] - np.dot(L[i, :k], L[k, :k]))

    return L




def exercitiul_1():
    """
    Sa se verifice daca sistemul (1) admite solutie unica si in caz afirmativ sa se determine solutia folosind metoda
    Gauss cu pivotare totala.
    """

    print('Exercitiul 1\n')
    A = np.array([
        [0., -7., 4., 7.],
        [-10., -8., -4., -8.],
        [-10., -1., -1., 0.],
        [-7., -1., -5., -9.]
    ])
    b = np.array([38., -160., -51., -126.]).T

    """
    Pentru a verifica daca sistemul are solutie unica, se verifica daca determinantul matricii A este diferit de 0.
    Am calculat determinantul folosind np.linalg.det(A) in cadrul functiei meg_pivotare_totala().
    In cazul in care nu se respecta conditia, se va afisa un mesaj corespunzator si se va opri executia functiei.
    In acest caz determinantul este -138, deci sistemul are solutie unica.
    """

    x_sol = meg_pivotare_totala(A, b)
    print('====> Solutia sistemului Ax = b:')
    print(x_sol)
    b_check = np.matmul(A, x_sol)
    print('Verificarea rezultatului:')
    print(b_check)


def exercitiul_2():
    """
    Verificati daca matricea B este inversabila si in caz afirmativ aplicati metoda Gauss
    pentru determinarea inversei.
    """
    print('Exercitiul 2\n')
    B = np.array([
        [0., -7., -6., -2.],
        [-4., -2., -4., 6.],
        [4., -3., -10., 1.],
        [9., 1., 3., 9.]
    ])

    """
    O matrice este inversabila daca determinantul este diferit de 0. Verificarea se va face
    in calcul_inversa(B).
    """
    print('Inversa lui B este')
    B_inv = calcul_inversa(B)
    print(B_inv)
    print('Verificare B*B_inv = I')
    #Rotunjim rezultatul la 7 zecimale pentru a vedea daca este In
    print(np.ma.round(np.matmul(B, B_inv),7))


def exercitiul_3():
    """
    Sa se verifice daca sistemul (3) admite solutie unica ¸si in caz afirmativ sa se determine
    solutia folosind factorizarea LU cu pivotare partiala.
    """
    print('Exercitiul 3\n')
    A = np.array([
        [0., -1., -6., -7.],
        [-7., 6., -6., 5.],
        [5., 7., 2., 7.],
        [-1., -5., 5., -7.]
    ])
    b = np.array([-76., 3., 95., -40])

    """
    Pentru a verifica daca sistemul are solutie unica, se verifica daca determinantul matricii A este diferit de 0.
    Am calculat determinantul folosind np.linalg.det(A) in cadrul functiei factorizare_LU().
    """
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
    print('Verificarea rezultatului:')
    b_check = np.matmul(A, x_sol)
    print(b_check)


def exercitiul_4():
    """
    Sa se verifice daca matricea C admite factorizare Cholesky si in caz afirmativ sa se determine aceasta.
    """
    print('Exercitiul 4\n')
    A = np.array([
        [4., 20., -12., 10.],
        [20., 104., -58., 68.],
        [-12., -58., 62., 14.],
        [10., 68., 14., 191.]
    ])
    """ 
    Pentru a admite descompunerea Cholesky, matricea trebuie sa fie simetrica si pozitiv definita. 
    Verificarea se va face in functia met_Cholesky
    """
    L = met_Cholesky(A)
    print('Matricea L:')
    print(L)
    print('Matricea L transpus:')
    print(L.T)
    print('Verificare LL_transpus = A:')
    A_check_cholesky = np.matmul(L, L.T)
    print(A_check_cholesky)



exercitiul_1()
print('____________________________________________________________________')
exercitiul_2()
print('____________________________________________________________________')
exercitiul_3()
print('____________________________________________________________________')
exercitiul_4()