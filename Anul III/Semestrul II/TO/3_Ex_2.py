import numpy as np
from numpy import linalg as la
import matplotlib.pyplot as plt
from scipy import optimize
import cvxpy as cp

""" Cozma Laura-Elena, 344 """
"""
Initializam:
- n, dimensiunea0
- a, parametrul functiei
- x0, punctul de pornire pentru metoda gradient
- eps, eroarea
"""
n = 3
a = np.random.rand(n)
print('Punctul de start x0')
x0 = np.array([1, 2, 3])
print(x0)
eps = 10e-3

""" Valorile pentru constrangeri """
a_proj = np.ones(n)
b_proj = 1

""" Definim functia f """


def f(x):
    return 1 / 2 * (a.T @ x) ** 2 + 1 / 2 * x.T @ x


""" Minimul functiei.  Rezolvare folosing CVXPY """
Q = a @ a.T + np.identity(n)
z = cp.Variable(n)
objective = cp.Minimize(0.5 * cp.quad_form(z, Q))
constraints = [a_proj.T @ z == b_proj]
prob = cp.Problem(objective, constraints)
result = prob.solve(solver='CVXOPT')
f_min = prob.value
print("Valoarea minima a functiei este: " + str(f_min))

""" Definim criteriile de oprire: norma si valoare absoluta """


def crit_stop_norm(x1, x0):
    return la.norm(x1 - x0)


def crit_stop_err_absoluta(x):
    return f(x) - f_min


""" Definim formula pentru calculul proiectiei """
def proj(y):
    """ Se observa ca multimea este de tip hiperplan, cu a = [1 1 ... 1]^T, b = 1, a.T@x=b """
    return y - ((a_proj.T @ y - b_proj) / (la.norm(a_proj) ** 2)) * a_proj


""" MGP cu pas constant alpha = 1/L """
def MGP_pas_constant(x0, crit_stop):
    """
    Metoda ce calculeaza MG Proiectat cu pas constant alpha = 1/L, criteriu de oprire alegandu-se prin parametru
    :param x0: punctul de start pentru MGP
           crit_stop: ia valorile 'eroare_absoluta' sau 'norma', definind criteriul de stop
    :return: x, solutia gasita de metoda gradient, nr de pasi, un array cu pasii facuti si valorile
    la fiecare pas ale criteriului de stop
    """

    """ Calculam primul gradient si criteriul de stop """
    Q = a @ a.T + np.identity(n)
    grad0 = Q @ x0

    k_cst = 1

    """ Calculam pasul alpha=1/L"""
    Lips = np.max(la.eigvals(Q))
    alpha = 1 / Lips

    x_new = proj(x0 - alpha * grad0)

    if crit_stop == 'norma':
        criteriu_stop = crit_stop_norm(x_new, x0)
        all_crit_stop = [criteriu_stop]
        all_k = [k_cst]

    elif crit_stop == 'eroare_absoluta':
        criteriu_stop = crit_stop_err_absoluta(x0)
        all_crit_stop = [criteriu_stop]
        all_k = [k_cst]
        if criteriu_stop < eps:
            return x0, k_cst, all_k, all_crit_stop
        else:
            k_cst += 1
            criteriu_stop = crit_stop_err_absoluta(x_new)
            all_crit_stop.append(criteriu_stop)
            all_k.append(k_cst)

    else:
        raise ValueError("Metoda aleasa nu e buna. Exista un typo")

    while (criteriu_stop > eps):
        x = x_new
        """ Calculam noile valori ale gradientului si criteriului de oprire """
        grad = Q @ x

        """ Actualizam x """
        y = x - alpha * grad
        x_new = proj(y)

        k_cst = k_cst + 1
        if crit_stop == 'eroare_absoluta':
            criteriu_stop = crit_stop_err_absoluta(x_new)
        elif crit_stop == 'norma':
            criteriu_stop = crit_stop_norm(x_new, x)
        else:
            raise ValueError("Metoda aleasa nu e buna. Exista un typo")

        all_crit_stop.append(criteriu_stop)
        all_k.append(k_cst)

    return x_new, k_cst, all_k, all_crit_stop


print('\n\nMetoda gradient cu pas constant alpha=1/L folosind norma drept criteriu de oprire')
x_cst_norm, pasi_cst_norm, k_cst_norm, crt_cst_norm = MGP_pas_constant(x0, 'norma')
print('Solutia gasita:')
print(x_cst_norm)
print('Valoarea functiei in solutia gasita:')
print(f(x_cst_norm))
print('Numarul de pasi:')
print(pasi_cst_norm)

print('\n\nMetoda gradient cu pas constant alpha=1/L folosind eroarea absoluta drept criteriu de oprire')
x_cst_err_abs, pasi_cst_err_abs, k_cst_err_abs, crt_cst_err_abs = MGP_pas_constant(x0, 'eroare_absoluta')
print('Solutia gasita:')
print(x_cst_err_abs)
print('Valoarea functiei in solutia gasita:')
print(f(x_cst_err_abs))
print('Numarul de pasi:')
print(pasi_cst_err_abs)

""" MGP cu pas ales prin backtracking """


def MGP_backtracking(x0, crit_stop):
    """
    Metoda ce calculeaza MG Proiectat cu pas ales prin backtracking, criteriu de oprire alegandu-se prin parametru
    :param x0: punctul de start pentru MG
           crit_stop: ia valorile 'eroare_absoluta' sau 'norma', definind criteriul de stop
    :return: x, solutia gasita de metoda gradient, nr de pasi, un array cu pasii facuti si valorile
    la fiecare pas ale criteriului de stop
    """
    Q = a @ a.T + np.identity(n)
    grad0 = Q @ x0

    c = 0.5
    r = 0.5
    """ Calculam pasul alpha"""
    alpha = 2
    x_new = proj(x0 - alpha * grad0)
    """ Micsoram alpha pana respecta inegalitatea """
    while f(proj(x0 - alpha * grad0)) > (f(x0) - (c / alpha) * (la.norm(x_new - x0) ** 2)):
        alpha = r * alpha
        x_new = proj(x0 - alpha * grad0)

    if crit_stop == 'eroare_absoluta':
        criteriu_stop = crit_stop_err_absoluta(x_new)
    elif crit_stop == 'norma':
        criteriu_stop = crit_stop_norm(x_new, x0)
    else:
        raise ValueError("Metoda aleasa nu e buna. Exista un typo")

    k_bkt = 1
    all_crit_stop = [criteriu_stop]
    all_k = [k_bkt]

    while (criteriu_stop > eps):
        """ Actualizam x cu valoarea x_new calculata anterior """
        x = x_new
        grad = Q @ x
        """ Setam alpha initial """
        alpha = 2
        y = x - alpha * grad
        x_new = proj(y)
        """ Micsoram alpha pana respecta inegalitatea """
        while f(proj(x - alpha * grad)) > (f(x) - (c / alpha) * (la.norm(x_new - x) ** 2)):
            alpha = r * alpha
            y = x - alpha * grad
            x_new = proj(y)

        k_bkt = k_bkt + 1
        if crit_stop == 'eroare_absoluta':
            criteriu_stop = crit_stop_err_absoluta(x)
        elif crit_stop == 'norma':
            criteriu_stop = crit_stop_norm(x_new, x)
        else:
            raise ValueError("Metoda aleasa nu e buna. Exista un typo")

        all_crit_stop.append(criteriu_stop)
        all_k.append(k_bkt)

    return x_new, k_bkt, all_k, all_crit_stop


print('\n\nMetoda gradient folosind backtracking cu norma drept criteriu de oprire')
x_bkt_norm, pasi_bkt_norm, k_bkt_norm, crt_bkt_norm = MGP_backtracking(x0, 'norma')
print('Solutia gasita:')
print(x_bkt_norm)
print('Valoarea functiei in solutia gasita:')
print(f(x_bkt_norm))
print('Numarul de pasi:')
print(pasi_bkt_norm)

print('\n\nMetoda gradient folosind backtracking cu eroarea absoluta drept criteriu de oprire')
x_bkt_err_abs, pasi_bkt_err_abs, k_bkt_err_abs, crt_bkt_err_abs = MGP_backtracking(x0, 'eroare_absoluta')
print('Solutia gasita:')
print(x_bkt_err_abs)
print('Valoarea functiei in solutia gasita:')
print(f(x_bkt_err_abs))
print('Numarul de pasi:')
print(pasi_bkt_err_abs)

""" Afisarea graficelor """

""" Criteriul de oprire: norma """
plt.figure(0)
plt.plot(k_cst_norm, crt_cst_norm)
plt.plot(k_bkt_norm, crt_bkt_norm)
plt.title('Criteriu de oprire ||xk+1-xk|| <= eps')
plt.xlabel('k')
plt.ylabel('||xk+1-xk||')
plt.legend(['MGP pas constant', 'MGP backtracking'])
plt.show()

""" Criteriul de oprire: eroare absoluta """
plt.figure(1)
plt.plot(k_cst_err_abs, crt_cst_err_abs)
plt.plot(k_bkt_err_abs, crt_bkt_err_abs)
plt.title('Criteriu de oprire f(xk)-f* <= eps')
plt.xlabel('k')
plt.ylabel('f(xk)-f*')
plt.legend(['MGP pas constant', 'MGP backtracking'])
plt.show()
