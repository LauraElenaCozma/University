import numpy as np
import matplotlib.pyplot as plt

"""
    1. Definim o functie exacta dupa care se vor genera date
    2. Definim o metoda prin care vom genera date perturbate
    3. Definim o metoda prin care sa vizualizam datele
    4. Implementam o metoda de regresie (liniara)
    5. Definim o metoda prin care sa vedem curba rezultata
"""
def view_data(f1_, f2_, show=True):
    plt.figure()
    plt.scatter(f1_, f2_, marker='o', c='green', label='known data')
    plt.legend()
    plt.xlabel('feature 1')
    plt.ylabel('feature 2')
    plt.grid()
    plt.title('Date regresie')
    if show:
        plt.show()

def view_regression(coef, method='linear', show=True):
    if method.lower() == 'linear':
        domain = np.linspace(1, 3, 100)
        values = coef[0] * domain + coef[1]
    plt.plot(domain, values, label='linear')
    plt.legend()
    if show:
        plt.show()

def poli1(x_, a=1, b=2):
    y = a * x_ + b
    return y

def generate_toy_data(method='linear', num_samples=30, low=1, high=3):
    """
    Distributia uniforma iti ia pct dintr-un interval low high de size
    Permite tuturor punctelor sa apara in acel interval
    """
    feature_1 = np.random.uniform(low=low, high=high, size=num_samples)
    feature_1 = np.sort(feature_1)

    if method.lower() == 'linear':
        feature_2 = poli1(feature_1)
    else:
        pass

    #Avem nevoie de o perturbare, pentru a nu fi discretizarile de pe o dreapta
    if method.lower() == 'linear':
        """
        size=cat de mare sa fie vectorul
        loc=media
        scale=deviatia standard
        """
        feature_2 += np.random.normal(size=len(feature_2), loc=0, scale=0.3)
    return feature_1, feature_2

def regresie_liniara(f1_, f2_):
    #a11 = np.dot(f1_, f1_)
    a11 = f1_ @ f1_
    #a11 = np.sum(np.power(f1_, 2))
    a12 = np.sum(f1_)
    a22 = len(f1_)

    matrix = np.array([
        [a11, a12],
        [a12, a22]
    ])
    w = np.array([
        [f1_ @ f2_],
        [np.sum(f2_)]
    ])

    #Solve matrix * coef = w
    coef = np.linalg.solve(matrix, w)
    return coef

f1, f2 = generate_toy_data()
view_data(f1, f2, show=False)

coef = regresie_liniara(f1, f2)
view_regression(coef, show=True)