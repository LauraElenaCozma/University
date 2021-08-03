import numpy as np
from numpy import linalg as la
import matplotlib.pyplot as plt
from scipy import optimize

""" Cozma Laura-Elena, 344 """
"""
Initializam:
- n, dimensiunea
- a, parametrul functiei
- x0, punctul de pornire pentru metoda gradient
- eps, eroarea
"""
n = 2
a = np.random.rand(n)
print('Punctul de start x0')
x0 = np.random.rand(n)
print(x0)
eps = 10e-7


""" Definim functia f """
def f(x):
    return 1/2 * (a.T @ x)**2 + 1/2 * x.T @ x

""" 
Se observa ca minimul functiei f se atinge in 0
Functia e convexa cu a@a.t@x pozitiv definita. La optim a@a.t@x este 0
Deci f* va avea valoarea 0
"""
f_min = 0

""" Definim criteriile de oprire: norma si valoare absoluta """
def crit_stop_norm(grad):
    return la.norm(grad)

def crit_stop_err_absoluta(x):
    return f(x) - f_min


""" MG cu pas ideal """
def MG_pas_ideal(x0, crit_stop):
    """
    Metoda ce calculeaza MG cu pas ideal, criteriu de oprire alegandu-se prin parametru
    :param x0: punctul de start pentru MG
           crit_stop: ia valorile 'eroare_absoluta' sau 'norma', definind criteriul de stop
    :return: x, solutia gasita de metoda gradient, nr de pasi, un array cu pasii facuti si valorile
    la fiecare pas ale criteriului de stop
    """

    """ Calculam primul gradient si criteriul de stop """
    grad0 = (a@a.T + np.identity(n))@x0
    if crit_stop == 'eroare_absoluta':
        criteriu_stop = crit_stop_err_absoluta(x0)
    elif crit_stop == 'norma':
        criteriu_stop = crit_stop_norm(grad0)
    else:
        raise ValueError("Metoda aleasa nu e buna. Exista un typo")

    x = x0
    k_ideal = 1
    all_crit_stop = [criteriu_stop]
    all_k = [k_ideal]
    while (criteriu_stop > eps):
        """ Calculam noile valori ale gradientului si criteriului de oprire """
        Q = a @ a.T + np.identity(n)
        grad = Q @ x

        """ Actualizam alpha conform metodei cu pas ideal """
        alpha = (la.norm(grad) ** 2) / (grad.T @ Q @ grad)

        """ Actualizam x """
        x = x - alpha * grad

        k_ideal = k_ideal + 1
        if crit_stop == 'eroare_absoluta':
            criteriu_stop = crit_stop_err_absoluta(x)
        elif crit_stop == 'norma':
            criteriu_stop = crit_stop_norm(grad)
        else:
            raise ValueError("Metoda aleasa nu e buna. Exista un typo")

        all_crit_stop.append(criteriu_stop)
        all_k.append(k_ideal)

    return x, k_ideal, all_k, all_crit_stop


print('\n\nMetoda gradient cu pas ideal folosind norma drept criteriu de oprire')
x_ideal_norm, pasi_ideal_norm, k_ideal_norm, crt_ideal_norm = MG_pas_ideal(x0, 'norma')
print('Solutia gasita:')
print(x_ideal_norm)
print('Valoarea functiei in solutia gasita:')
print(f(x_ideal_norm))
print('Numarul de pasi:')
print(pasi_ideal_norm)

print('\n\nMetoda gradient cu pas ideal folosind eroarea absoluta drept criteriu de oprire')
x_ideal_err_abs, pasi_ideal_err_abs, k_ideal_err_abs, crt_ideal_err_abs = MG_pas_ideal(x0, 'eroare_absoluta')
print('Solutia gasita:')
print(x_ideal_err_abs)
print('Valoarea functiei in solutia gasita:')
print(f(x_ideal_err_abs))
print('Numarul de pasi:')
print(pasi_ideal_err_abs)




""" MG cu pas ales prin backtracking """
def MG_backtracking(x0, crit_stop):
    """
    Metoda ce calculeaza MG cu pas ales prin backtracking, criteriu de oprire alegandu-se prin parametru
    :param x0: punctul de start pentru MG
           crit_stop: ia valorile 'eroare_absoluta' sau 'norma', definind criteriul de stop
    :return: x, solutia gasita de metoda gradient, nr de pasi, un array cu pasii facuti si valorile
    la fiecare pas ale criteriului de stop
    """
    grad0 = (a@a.T + np.identity(n))@x0
    if crit_stop == 'eroare_absoluta':
        criteriu_stop = crit_stop_err_absoluta(x0)
    elif crit_stop == 'norma':
        criteriu_stop = crit_stop_norm(grad0)
    else:
        raise ValueError("Metoda aleasa nu e buna. Exista un typo")

    x = x0
    k_bkt = 1
    c = 0.5
    r = 0.5
    all_crit_stop = [criteriu_stop]
    all_k = [k_bkt]

    while (criteriu_stop > eps):
        grad = (a@a.T + np.identity(n))@x
        """ Setam alpha initial """
        alpha = 1
        """ Micsoram alpha pana respecta inegalitatea """
        while f(x - alpha * grad) > (f(x) - c * alpha * (la.norm(grad)**2)):
            alpha = r * alpha

        x = x - alpha * grad

        k_bkt = k_bkt + 1
        if crit_stop == 'eroare_absoluta':
            criteriu_stop = crit_stop_err_absoluta(x)
        elif crit_stop == 'norma':
            criteriu_stop = crit_stop_norm(grad)
        else:
            raise ValueError("Metoda aleasa nu e buna. Exista un typo")

        all_crit_stop.append(criteriu_stop)
        all_k.append(k_bkt)

    return x, k_bkt, all_k, all_crit_stop

print('\n\nMetoda gradient folosind backtracking cu norma drept criteriu de oprire')
x_bkt_norm, pasi_bkt_norm, k_bkt_norm, crt_bkt_norm = MG_backtracking(x0, 'norma')
print('Solutia gasita:')
print(x_bkt_norm)
print('Valoarea functiei in solutia gasita:')
print(f(x_bkt_norm))
print('Numarul de pasi:')
print(pasi_bkt_norm)

print('\n\nMetoda gradient folosind backtracking cu eroarea absoluta drept criteriu de oprire')
x_bkt_err_abs, pasi_bkt_err_abs, k_bkt_err_abs, crt_bkt_err_abs = MG_backtracking(x0, 'eroare_absoluta')
print('Solutia gasita:')
print(x_bkt_err_abs)
print('Valoarea functiei in solutia gasita:')
print(f(x_bkt_err_abs))
print('Numarul de pasi:')
print(pasi_bkt_err_abs)

""" Afisarea graficelor """

""" Criteriul de oprire: norma """
plt.figure(0)
plt.plot(k_ideal_norm, crt_ideal_norm)
plt.plot(k_bkt_norm, crt_bkt_norm)
plt.title('Criteriu de oprire ||\u2207f(xk)|| <= eps')
plt.xlabel('k')
plt.ylabel('||\u2207f(xk)||')
plt.legend(['MG pas ideal', 'MG backtracking'])
plt.show()

""" Criteriul de oprire: eroare absoluta """
plt.figure(1)
plt.plot(k_ideal_err_abs, crt_ideal_err_abs)
plt.plot(k_bkt_err_abs, crt_bkt_err_abs)
plt.title('Criteriu de oprire f(xk)-f* <= eps')
plt.xlabel('k')
plt.ylabel('f(xk)-f*')
plt.legend(['MG pas ideal', 'MG backtracking'])
plt.show()