import numpy as np
import matplotlib.pyplot as plt
import copy
import math

##################################################################################################################

###### Metode utilizate in cadrul exercitiul 1 ########

def func_1():
    A = np.array([[49, -21], [-21, 73]])
    b = np.array([-4, -10])
    return A, b


def metoda_pasului_descendent(A, b, point):
    """
    Determinarea punctului de minim al functiei f(x) = 1/2 * x.T * A * x - x.T * b cu ajutorul
    metodei pasului descendent.
    :param A, b: folositi in scrierea functiei date
    :param point: coordonatele punctului de start
    :return: drum_x, drum_y: punctele determinate de-a lungul drumului prin metoda
    pasului descendent pana s-a ajuns la minim
            k: numarul de iteratii
    """
    k = 0
    """
    Cazul din enunt este 2-dimensional, astfel vom pastra coodonatele x si y determinate in 2 vectori
    """
    drum_x = np.array([point[0]])
    drum_y = np.array([point[1]])
    r = b - np.matmul(A, point)

    while dist_euclidiana(r) > 10 ** (-10):
        # Calculeaza learning rate
        alpha = np.matmul(r.T, r) / np.matmul(np.matmul(r.T, A), r)
        # Actulizeaza coordonatele punctului
        point = point + alpha * r
        # Adauga noile coordonate vectorilor care tin drumul
        drum_x = np.append(drum_x, point[0])
        drum_y = np.append(drum_y, point[1])
        # Actualizeaza r si numarul de pasi
        k = k+1
        r = b - np.matmul(A, point)

    return drum_x, drum_y, k


def metoda_gradientilor_conjugati(A, b, point):
    """
    Determinarea punctului de minim al functiei f(x) = 1/2 * x.T * A * x - x.T * b cu ajutorul
    metodei gradientilor conjugati.
    :param A, b: folositi in scrierea functiei date
    :param point: coordonatele punctului de start
    :return: drum_x, drum_y: punctele determinate de-a lungul drumului prin metoda
    pasului descendent pana s-a ajuns la minim
            k: numarul de iteratii
    """
    k = 0
    """
    Cazul din enunt este 2-dimensional, astfel vom pastra coodonatele x si y determinate in 2 vectori
    """
    drum_x = np.array([point[0]])
    drum_y = np.array([point[1]])

    # Initializam directia si r0
    d = r0 = b - np.matmul(A, point)

    while dist_euclidiana(r0) > 10 ** (-10):
        # Calculeaza learning rate
        alpha = np.matmul(r0.T, r0) / np.matmul(np.matmul(d.T, A), d)
        # Actualizeaza coordonatele punctului
        point = point + alpha * d
        # Adauga noile coordonate vectorilor care tin drumul
        drum_x = np.append(drum_x, point[0])
        drum_y = np.append(drum_y, point[1])
        # Actualizeaza r0, beta si directia
        r1 = r0 - alpha * np.matmul(A, d)
        beta = np.matmul(r1.T, r1) / np.matmul(r0.T, r0)
        d = r1 + beta * d
        r0 = r1
        k = k + 1
    return drum_x, drum_y, k

def dist_euclidiana(x):
    """
    Functie care calculeaza distanta euclidiana.
    Utilizata in conditia de oprire in cazul metodei pasului descendent si al gradientilor conjugati
    """
    return math.sqrt(np.dot(x, x))


"""
    Metode utilizate in construirea graficului curbelor de nivel 
    al functiei patratice definite de matricea A si vectorul b.
"""

def grid_discret(A, b, size=50):
    """
    Construieste un grid discret si evaleaza f in fiecare punct al gridului
    """
    # size ->  Numar de puncte pe fiecare axa
    x1 = np.linspace(-4, 6, size)  # Axa x1
    x2 = np.linspace(-6, 4, size)  # Axa x2
    X1, X2 = np.meshgrid(x1, x2)  # Creeaza un grid pe planul determinat de axele x1 si x2

    X3 = np.zeros((size, size))
    for i in range(size):
        for j in range(size):
            x = np.array(
                [X1[i, j], X2[i, j]])  # x e vectorul ce contine coordonatele unui punct din gridul definit mai sus
            X3[i, j] = .5 * x @ A @ x - x @ b  # Evaluam functia in punctul x

    return X1, X2, X3


def linii_nivel_cu_drum(A, b, pointX, pointY, title, levels=10):
    """
    Construieste liniile de nivel ale functiei f
    """

    # Construieste gridul asociat functiei
    (X1, X2, X3) = grid_discret(A, b)

    # Ploteaza liniile de nivel ale functiei f
    plt.figure()
    plt.contour(X1, X2, X3, levels=levels)  # levels = numarul de linii de nivel

    # Etichete pe axe
    plt.xlabel('x1')
    plt.ylabel('x2')

    # Titlu
    plt.title(title)

    # Ploteaza drumul dat ca parametru
    plt.plot(pointX, pointY, linewidth=3, label='Drumul determinat')
    # Ploteaza punctele
    plt.scatter(pointX, pointY, marker='.', s=25, label='Punctele ce determina drumul')
    plt.legend()
    # Afiseaza figura
    plt.show()


def exercitiul_1():
    """
    Sa se verifice daca functia (1) admite un punct de minim unic ¸si in caz afirmativ sa se determine acesta folosind
    1. Metoda pasului descendent;
    2. Metoda gradientilor conjugati.
    Sa se reprezinte pe graficul curbelor de nivel aproximarea obtinuta la fiecare iteratie pentru cele doua metode.
    """
    print('_________________________Exercitiul 1 ________________________')

    # Afla A si b date in enunt
    A, b = func_1()

    """ Pentru a admite un punct de minim, matricea trebuie sa fie simetrica si pozitiv definita. """
    """ Verificare simetrie: A trebuie sa fie egal cu A transpus (va admite o eroare de calcul de 1e-8) """
    if not np.all(np.abs(A - A.T) < 1e-8):
        raise AssertionError('Matricea nu e simetrica')

    """ Verificare pozitiv definita: folosind criteriul lui Sylvester, toti minorii de colt > 0 """
    n = A.shape[0]
    for k in range(n):
        if np.linalg.det(A[:k + 1, :k + 1]) <= 0:
            raise AssertionError('Matricea nu e pozitiv definita')

    # Alegem ca punct de plecare punctul (1, 1), un punct de pe grafic.
    p_start = [1, 1]
    """ Metoda pasului descendent """
    pointX_pas_desc, pointY_pas_desc, pasi = metoda_pasului_descendent(A, b, p_start)
    print('Numarul de pasi: ' + str(pasi))
    print('Punctul de minim determinat prin metoda pasului descendent:')
    print('x = ' + str(round(pointX_pas_desc[pointX_pas_desc.shape[0]-1], 5)))
    print('y = ' + str(round(pointY_pas_desc[pointY_pas_desc.shape[0]-1], 5)))

    linii_nivel_cu_drum(A, b, pointX_pas_desc, pointY_pas_desc, 'Minimul functiei prin metoda pasului descendent')

    """ Metoda gradientilor conjugati """
    pointX_grad_conj, pointY_grad_conj, pasi = metoda_gradientilor_conjugati(A, b, p_start)
    print('Numarul de pasi: ' + str(pasi))
    print('Punctul de minim determinat prin metoda gradientilor conjugati:')
    print('x = ' + str(round(pointX_grad_conj[pointX_grad_conj.shape[0] - 1], 5)))
    print('y = ' + str(round(pointY_grad_conj[pointY_grad_conj.shape[0] - 1], 5)))

    linii_nivel_cu_drum(A, b, pointX_grad_conj, pointY_grad_conj, 'Minimul functiei prin metoda gradientilor conjugati')


################################################################################################################

###### Metode utilizate in cadrul exercitiul 2 #############

def func_2(x):
    return 2 * np.sin(5 * x) + 3 * np.cos((-4) * x) + 2.45 * x     #x >= -pi, x <= pi

def construire_vector_Newton(x_point, x_val):
    """
    Metoda care construieste un vector cu elementele:
    1, x-x0, (x-x0)(x-x1), (x-x0)(x-x1)(x-x2),...
    :param x_point: punctul x de care depind valorile vectorului
    :param x_val: elemenetele x0, x1,....
    """
    n = x_val.shape[0]
    X = np.zeros(n)
    X[0] = 1
    for i in range(1, n):
        # La calculul fiecarui X[i] ne folosim de valoarea lui X[i-1]
        X[i] = X[i-1] * (x_point - x_val[i-1])
    return X

def construire_matrice_Newton(X):
    """
    Matricea de dim X.shape[0] trebuie sa fie de forma:
    1 0        0   ..........................  0
    1 x1-x0    0  ...........................  0
    .........................................
    1 xn-1-x0 (xn-1-x0)(xn-1-x1)............

    :param X: vectorul cu valorile x0, x1, x2.....
    :return: matricea construita
    """
    n = X.shape[0]
    A = np.zeros([n, n])
    for i in range(n):
        for j in range(n):
            if j == 0:
                A[i][j] = 1                             # prima coloana contine valoarea 1
            elif i >= j:
                A[i][j] = A[i][j-1] * (X[i] - X[j-1])   # punem valorile de sub diagonala principala, restul fiind 0
            else:
                break                                   # matricea deja contine 0, trecem la urmatoarea linie
    return A


def metoda_Newton(X, Y, x_point):
    """
    Pornind de la polinomul de grad N:
    Pn(x) = c0 + c1(x-x0) + c2(x-x0)(x-x1) + ..... + cn(x-x0)(x-x1)..(x-xn-1)
    Aflam matricea A cu ajutorul metodei construire_matrice_Newton.
    Rezolvam sistemul A*coef = Y.
    Stiind coeficientii, inlocuim valorile in Pn(x) si aplicam punctului x_point.
    :param X: X = [X0, X1, ..., Xn]
    :param Y: [Y0=f(X0), Y1=F(X1), ..., Yn=f(Xn)]
    :param x_point: Punctul in care doresti o valoare aproximata a functiei
    :return: Valoarea aproximata calculata folosind polinomul Lagrange in pointx determinat cu metoda Newton
    """

    """
    Construieste matricea corespunzatoarea metodei Newton folosindu-ne de valorile lui X    
    """
    A = construire_matrice_Newton(X)
    """
    Gaseste coeficientii polinomului rezolvand sistemul rezultat (matricea anterioara impreuna cu valorile lui Y).
    """
    coef = subs_asc(A, Y)
    """
    Construieste vectorul de tipul 1 (x-x0) (x-x0)(x-x1)...... si il aplicam punctului x_point
    """
    x_vector = construire_vector_Newton(x_point, X)
    """
    Face produsul scalar al lui x_vector cu coeficientii, iar rezultatul este chiar polinomul in punctul x_point
    """
    return np.dot(coef, x_vector)


def eroare_trunchiere(y_exp, y_aprox):
    """
    Calculeaza erorile de trunchiere dintre y_exp si y_aprox
    """
    assert y_exp.shape == y_aprox.shape, 'Vectorul de valori si cel prezis nu au aceeasi dimensiune'
    return np.abs(y_exp - y_aprox)

def eroare_max_trunchiere(y_exp, y_aprox):
    """
    Calculeaza maximul dintre erorile de trunchiere dintre y_exp si y_aprox
    """
    assert y_exp.shape == y_aprox.shape, 'Vectorul de valori si cel prezis nu au aceeasi dimensiune'
    return np.max(eroare_trunchiere(y_exp, y_aprox))

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
def exercitiul_2():
    """
    Sa se aproximeze functia (2) cu polinomul Lagrange PN (x) determinat folosind metoda Newton.
    1. Sa se reprezinte grafic functia exacta (2), nodurile de interpolare alese si aproximarea numerica obtinuta.
    Se va alege cel mai mic N astfel ıncat eroarea maxima de trunchiere sa satisfaca relatia ||e^t||∞ ≤ 1e − 5.
    2. Sa se reprezinte ıntr-o figura noua eroarea de trunchiere.
    """

    print('_________________________Exercitiul 2 ________________________')

    # Intervalul dat
    interval = [-np.pi, np.pi]

    x_domain = np.linspace(interval[0], interval[1], 100)  # Discretizare domeniu (folosit pentru plotare)
    y_values = func_2(x_domain)  # Valorile functiei exacte in punctele din discretizare

    # Afisarea graficului functiei exacte pentru punctul 1
    plt.figure(0)
    plt.plot(x_domain, y_values, c='k', linewidth=2, label='Functie exacta')
    plt.xlabel('x')
    plt.ylabel('y = f(x)')
    plt.grid()

    """
    Gradul maxim al polinomului.
    Deoarece metoda Newton nu va atige eroarea de 1e-5 pe aceasta functie, calculeaza minimul erorilor pana la N = 99. 
    La N = 99 se vor face 100 de puncte pe grafic, discretizarea intervalului aleasa la inceput.
    """
    N = 1
    errors = np.zeros(99)
    while N < 100:
        x_client = np.linspace(interval[0], interval[1], N + 1)  # Discretizare interval (nodurile date de client)
        y_client = func_2(x_client)                              # Valorile functiei in nodurile date de client
        y_metoda_newton = np.zeros(len(x_domain))                # Vom stoca valorile aproximate prin met Newton
        for i in range(len(x_domain)):
            # Pentru fiecare x din domeniu, calculam y aproximat
            y_metoda_newton[i] = metoda_Newton(x_client, y_client, x_domain[i])
        errors[N-1] = eroare_max_trunchiere(y_values, y_metoda_newton)
        print("N=" + str(N) + " eroare=" + str(eroare_max_trunchiere(y_values, y_metoda_newton)))
        if errors[N-1] <= 1e-5:
            break
        N += 1

    N_err_min = np.argmin(errors) + 1
    print("Eroarea maxima minima = " + str(errors[N_err_min]))
    x_client = np.linspace(interval[0], interval[1], N_err_min + 1)
    y_client = func_2(x_client)
    # Afisarea nodurilor de interpolare
    plt.scatter(x_client, y_client, marker='.', c='red', s=150, label='Noduri de interpolare')
    # Calculare discretizare polinom
    y_metoda_newton = np.zeros(len(x_domain))  # Folosit pentru a stoca valorile aproximate
    for i in range(len(x_domain)):
        y_metoda_newton[i] = metoda_Newton(x_client, y_client, x_domain[i])
    # Afisare grafic aproximare
    plt.plot(x_domain, y_metoda_newton, c='b', linewidth=1, linestyle='-.', label='Metoda Newton')
    plt.title('Metoda Newton, N={}'.format(N_err_min))
    plt.legend()
    plt.show()

    # Afisarea graficului erorii de trunchiere pentru punctul 2
    plt.figure(1)
    plt.plot(x_domain, eroare_trunchiere(y_values, y_metoda_newton), c='k', linewidth=2, label='Graficul erorii')
    plt.xlabel('x')
    plt.ylabel('Eroare trunchiere')
    plt.grid()
    plt.title('Eroarea de trunchiere, N={}'.format(N_err_min))
    plt.legend()
    plt.show()


#################################################################################################################

###### Metode utilizate in cadrul exercitiul 1

def func_3(x):
    return (-1) * np.sin((-6) * x) + 6 * np.cos(5 * x) + 1.74 * x  #x >= -pi, x <= pi

def func_3_deriv(x):
    """
    Derivata functiei func_3
    """
    return 6 * np.cos((-6) * x) - 30 * np.sin(5 * x) + 1.74


def spline_coef_b(X, Y, f_deriv):
    """
    Metoda care calculeaza coeficientii b din cadrul metodei spline cubice.
    :param X: X = [X0, X1, ..., Xn]
    :param Y: [Y0=f(X0), Y1=F(X1), ..., Yn=f(Xn)]
    :param f_deriv: derivata functiei care trebuie aproximata
    :return: b - array de coeficienti b
    """
    n = X.shape[0]
    A = np.zeros([n, n])
    W = np.zeros(n)
    """
    Aflam valorile lui A si W conform formulei din curs din ecuatia Ab = W.    
    A are forma:
    1 0 0 0 0 ..... 0
    0 1 4 1 0 ..... 0
    0 0 1 4 1 ..... 0
    .................
    0 0 0 0 0 ..... 1
    """
    for i in range(n):
        if i == 0:
            A[i, i] = 1             # Pentru eficienta am folosit acelasi for pentru A si W
            W[i] = f_deriv(X[0])
        elif i == n-1:
            A[i][i] = 1
            W[i] = f_deriv(X[n-1])
        else:
            A[i, i] = 4
            A[i, i-1] = 1
            A[i, i+1] = 1
            h = X[i+1] - X[i]
            W[i] = (3/h) * (Y[i+1] - Y[i-1])

    # Folosind metoda LU, aflam b din ecuatia Ab = W.
    # Aceasta se poate aplica, verificarile facandu-se in metoda factorizare_LU
    L, U, P = factorizare_LU(A)
    b = rezolvare_sistem(L, U, P, W)
    return b

def spline_cubica(X, Y, x_point):
    """
    Metoda de interpolare spline cubica.
    :param X: X = [X0, X1, ..., Xn]
    :param Y: [Y0=f(X0), Y1=F(X1), ..., Yn=f(Xn)]
    :param pointx: Punct in care doresti o valoare aproximata a functiei
    :return: aprox_value: Valoarea aproximata calculata interpolarea spline cubica in pointx
    """
    n = X.shape[0]
    a = np.zeros(n)
    b = spline_coef_b(X, Y, func_3_deriv)
    c = np.zeros(n)
    d = np.zeros(n)
    aprox_value = 0

    for i in range(n-1):
        a[i] = Y[i]         # Calculeaza coeficientii conform formulelor
        h = X[i+1]-X[i]
        c[i] = (3/(h**2)) * (Y[i+1] - Y[i]) - (b[i+1] + 2 * b[i])/h
        d[i] = ((-2) / (h ** 3)) * (Y[i + 1] - Y[i]) + ((b[i + 1] + b[i]) / (h ** 2))

    for i in range(n-1):
        if x_point >= X[i] and x_point <= X[i+1]: # Gaseste intervalul in care se afla punctul si calculeaza aprox_value
            aprox_value = a[i] + b[i] * (x_point - X[i]) + c[i] * ((x_point - X[i]) ** 2) + d[i] * ((x_point - X[i]) ** 3)
            break
    return aprox_value

"""
    Metode utilizate in rezolvarea ecuatiei A * b = W.
    Algoritmul utilizat este factorizarea LU.
"""

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


def exercitiul_3():
    """
    Sa se aproximeze functia (3) folosind interpolarea cu functii spline cubice.
    1. Sa se reprezinte grafic functia exacta (3), nodurile de interpolare alese si aproximarea numerica obtinuta.
    Se va alege cel mai mic N astfel ıncat eroarea maxima de trunchiere sa satisfaca relatia ||e^t||∞ ≤ 1e − 5.
    2. Sa se reprezinte ıntr-o figura noua eroarea de trunchiere.
    """
    print('_________________________Exercitiul 3 ________________________')
    # Intervalul dat
    interval = [-np.pi, np.pi]

    x_domain = np.linspace(interval[0], interval[1], 100)  # Discretizare domeniu (folosit pentru plotare)
    y_values = func_3(x_domain)  # Valorile functiei exacte in punctele din discretizare

    # Afisarea graficului functiei exacte pentru punctul 1
    plt.figure(0)
    plt.plot(x_domain, y_values, c='k', linewidth=2, label='Functie exacta')
    plt.xlabel('x')
    plt.ylabel('y = f(x)')
    plt.grid()

    """
    Gradul maxim al polinomului.
    Initial 1, dupa care crestem pana se atinge eroarea de trunchiere dorita
    Nodurile de interpolare vor fi N + 1.
    """
    N = 1
    while 1:
        x_client = np.linspace(interval[0], interval[1], N + 1)  # Discretizare interval (nodurile date de client)
        y_client = func_3(x_client)                              # Valorile functiei in nodurile date de client
        y_spline_cubica = np.zeros(len(x_domain))                # Vom stoca valorile aproximate prin met Newton
        for i in range(len(x_domain)):
            # Pentru fiecare x din domeniu, calculam y aproximat
            y_spline_cubica[i] = spline_cubica(x_client, y_client, x_domain[i])
        print(str(N) + " eroare=" + str(eroare_max_trunchiere(y_values, y_spline_cubica)))
        if eroare_max_trunchiere(y_values, y_spline_cubica) <= 1e-5:
            break
        N += 1

    # Afisarea nodurilor de interpolare
    plt.scatter(x_client, y_client, marker='.', c='red', s=150, label='Noduri de interpolare')
    # Calculare discretizare polinom
    y_spline_cubica = np.zeros(len(x_domain))  # Folosit pentru a stoca valorile aproximate
    for i in range(len(x_domain)):
        y_spline_cubica[i] = spline_cubica(x_client, y_client, x_domain[i])
    print(str(N) + " eroare=" + str(eroare_max_trunchiere(y_values, y_spline_cubica)))

    # Afisare grafic aproximare
    plt.plot(x_domain, y_spline_cubica, c='b', linewidth=1, linestyle='-.', label='Spline Cubica')
    plt.title('Metoda Spline Cubica, N={}'.format(N))
    plt.legend()
    plt.show()

    # ===============================================================================================================
    # Afisarea graficului erorii de trunchiere pentru punctul 1
    plt.figure(1)
    plt.plot(x_domain, eroare_trunchiere(y_values, y_spline_cubica), c='k', linewidth=2, label='Graficul erorii')
    plt.xlabel('x')
    plt.ylabel('Eroare trunchiere')
    plt.grid()
    plt.title('Eroarea de trunchiere, N={}'.format(N))
    plt.legend()
    plt.show()


exercitiul_1()
exercitiul_2()
exercitiul_3()
