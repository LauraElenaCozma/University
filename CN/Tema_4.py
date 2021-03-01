import numpy as np
import sympy as sp
import matplotlib.pyplot as plt

################################################### Exercitiul 1 ###################################################

def diferente_finite_centrale(X, Y):
    '''
    Functie care returneaza aproximarea celei de-a doua derivate a functiei
    folosind metoda diferentelor finite centrale
    :param X: X = [X0, X1, ..., Xn], X1 X2 .... Xn-1 discretizarea domeniului functiei
    :param Y: [Y0=f(X0), Y1=F(X1), ..., Yn=f(Xn)]
    :return: aproximarea celei de-a doua derivate a functiei
    '''

    df_2 = np.zeros(len(X))
    df_2[0] = df_2[-1] = np.nan

    '''
    Calculul lui f''(x) conform formulei (f(x+h)-2f(x)+f(x-h))/(h^2)
    Deoarece h = X[i+1]-X[i], f(x+h) = f(X[i+1]), iar f(x-h) = f(X[i-1]), i reprezentand iteratia curenta
    '''
    for i in range(1, len(X) - 1):
        h = X[i + 1] - X[i]
        df_2[i] = (Y[i + 1] - 2 * Y[i] + Y[i - 1]) / (h ** 2)
    return df_2

def f_df_to_float(expresie, x):
    '''
    Functie care calculeaza f''(x) si returneaza f(x) si f''(x)
    :param expresie: functia initiala data
    :param x: variabila declarata simbolic pentru calculul derivatei
    :return: f(x) si f''(x)
    '''

    # Calculeaza derivata de ordinul 2
    df = expresie.diff()
    df_2 = df.diff()

    # Converteste expresiile cu lambdify pentru a putea evalua expresiile simbolice care returneaza float-uri
    expresie = sp.lambdify(x, expresie)
    df_2 = sp.lambdify(x, df_2)
    return expresie, df_2

def eroare_trunchiere(y_exp, y_aprox):
    '''
    Calculeaza erorile de trunchiere dintre y_exp si y_aprox
    '''
    assert y_exp.shape == y_aprox.shape, 'Vectorul de valori si cel prezis nu au aceeasi dimensiune'
    return np.abs(y_exp - y_aprox)


def eroare_max_trunchiere(y_exp, y_aprox):
    '''
    Calculeaza maximul dintre erorile de trunchiere dintre y_exp si y_aprox
    '''
    assert y_exp.shape == y_aprox.shape, 'Vectorul de valori si cel prezis nu au aceeasi dimensiune'
    return np.max(eroare_trunchiere(y_exp, y_aprox))


def exercitiul_1():
    '''
    Sa se aproximeze a doua derivata a functiei (1) folosind metoda diferentelor finite.

    1.  Sa se reprezinte grafic derivata a doua exacta a functiei (1)  ̧si aproximarea numerica obtinuta.
    Numarul de puncte al discretizarii intervalului, N, se va alege cel mai mic posibil astfel incat
    eroarea maxima de trunchiere sa satisfaca relatia ‖et‖∞≤1e−5.

    2.  Sa se reprezinte intr-o figura noua eroarea de trunchiere.
    '''

    # Declara intervalul, impreuna cu o discretizare a intervalului
    interval = [-np.pi/2, np.pi]
    x_domain = np.linspace(interval[0], interval[1], 100)

    # Foloseste libraria sympy ca sa declari simbolic variabila 'x'.
    x = sp.symbols('x')
    functie = sp.cos((-0.3) * x)

    # Calculeaza f(x) si f''(x) folosind expresii simbolice
    f, df_2 = f_df_to_float(functie, x)

    # Calculeaza numarul de puncte al discretizarii intervalului, N care sa aiba eroarea de trunchiere maxima minima
    N = 1
    while 1:
        x_client = np.zeros(N + 2)
        x_client[1:-1] = np.linspace(interval[0], interval[1], N)
        # Calculeaza distanta dintre doua puncte
        h = x_client[2] - x_client[1]
        # Ultima si prima valoare din x_client sunt valoarile anterioare si posterioare capetelor intevalului
        x_client[0] = x_client[1] - h
        x_client[-1] = x_client[-2] + h

        # Calculeaza valorile functiei f pe discretizarea aleasa
        y_client = f(x_client)

        # Calculeaza valorile exacte si valorile aproximarii derivatei de ord 2 pe discretizarea aleasa
        y_aprox = diferente_finite_centrale(x_client, y_client)
        y_df_2 = df_2(x_client)

        print("N=" + str(N) + "  eroare=" + str(eroare_max_trunchiere(y_df_2[1:-1], y_aprox[1:-1])))
        if eroare_max_trunchiere(y_df_2[1:-1], y_aprox[1:-1]) <= 1e-5: # La prima eroare maxima care indeplineste conditia ne oprim
            break
        N += 1

    y_dif_centrale = diferente_finite_centrale(x_client, y_client)
    y_df_2 = df_2(x_domain)
    plt.figure(1)
    plt.plot(x_domain, y_df_2, c='k', linewidth=2, label='derivata exacta')
    plt.plot(x_client[1:-1], y_dif_centrale[1:-1], c='orange', linewidth=2, linestyle='--',
             label='diferente finite centrale')
    plt.grid(True)
    plt.axhline(0, c='black', linewidth=1)
    plt.axvline(0, c='black', linewidth=1)
    plt.xlabel('x')
    plt.ylabel('y = f(x)')
    plt.title('Diferente finite centrale pentru f\'\'(x), N={}'.format(N))
    plt.legend()
    plt.show()

    '''
    Calculeaza eroarea de aproximare pentru a doua derivata in fiecare punct pentru 
    metoda diferentelor finite centrale. Afiseaza intr-o noua figura erorile obtinute.
    '''
    y_df_2 = df_2(x_client)
    plt.figure(2)
    plt.plot(x_client[1:-1], np.abs(y_df_2[1:-1] - y_dif_centrale[1:-1]), c='orange', label='Err dif fin centrale')
    plt.grid(True)
    plt.axhline(0, c='black', linewidth=1)
    plt.axvline(0, c='black', linewidth=1)
    plt.xlabel('x')
    plt.ylabel('Eroare trunchiere')
    plt.title('Eroarea de trunchiere, N={}'.format(N))
    plt.legend()
    plt.show()

################################################### Exercitiul 2 ###################################################

def integrare(f, x, metoda='dreptunghi'):
    '''
    Calculeaza valoarea aproximativa a integralei I(f) conform formulelor de cuadratura sumate
    a dreptunghiului, trapezului si Simpson.
    :param f: functia de integrat
    :param x: o diviziune a intervalului [a, b]
    :param metoda: sir de caractere ['dreptunghi', 'trapez', 'Simpson']
    :return: aproximarea numerica a integralei I(f)
    '''

    '''
    Verifica care din cele 3 metode este cea aleasa
    Calculeaza I conform formulelor pentru fiecare metoda
    '''
    if metoda.lower() == 'dreptunghi':
        m = int((len(x) - 1) / 2)
        h = (x[-1] - x[0]) / (2 * m)
        sum = 0
        for i in range(m):
            sum += f(x[2*i+1])
        I = 2 * h * sum
    elif metoda.lower() == 'trapez':
        m = (len(x) - 1)
        h = (x[-1] - x[0]) / m
        sum = 0
        for i in range(1, m):
            sum += f(x[i])
        I = (h / 2) * (f(x[0]) + 2 * sum + f(x[m]))
    elif metoda.capitalize() == 'Simpson':
        m = int((len(x) - 1) / 2)
        h = (x[-1] - x[0]) / (2 * m)
        sum1 = 0
        for i in range(m):
            sum1 += f(x[2*i+1])
        sum2 = 0
        for i in range(1, m):
            sum2 += f(x[2*i])
        I = (h / 3) * (f(x[0]) + 4 * sum1 + 2 * sum2 + f(x[2*m]))
    else:
        raise ValueError("Metoda aleasa nu e ok. Exista un typo")

    return I


def func_2(x):
    return (1/np.sqrt(2 * np.pi)) * (np.exp(- (x**2) / 2))

def exercitiul_2():
    '''
    (a)  Creati functia integrare care calculeaza valoarea aproximativa a integralei I(f) =∫abf(x)dx
    conform formulelor de cuadratura sumate a dreptunghiului, trapezului  ̧si Simpson.
    (b)  Sa se aproximeze valoarea integralei I(f) =∫baf(x)dx pentru functia func_2, folosind cele 3 metode
    mentionate mai sus, [a,b] = [-10, 10].
    '''

    print('\n-------------  Exercitiul 2  -------------')
    interval = [-10, 10]
    # Impartim intervalul intr-o diviziune echidistanta; numar impar potrivit pentru calculul lui m din formule
    x = np.linspace(interval[0], interval[1], 101)

    # Calculam aproximarea valorii integralei pentru fiecare dintre cele 3 metode
    aprox_drept_sumata   = integrare(func_2, x)
    aprox_trap_sumata    = integrare(func_2, x, 'trapez')
    aprox_Simpson_sumata = integrare(func_2, x, 'Simpson')

    print('Aproximarea valorii integralei folosind cuadratura sumata a dreptunghiului: ' + str(aprox_drept_sumata))
    print('Aproximarea valorii integralei folosind cuadratura sumata a trapezului: ' + str(aprox_trap_sumata))
    print('Aproximarea valorii integralei folosind cuadratura sumata Simpson: ' + str(aprox_Simpson_sumata))


###################################################################################################################

exercitiul_1()
exercitiul_2()

