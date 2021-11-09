# Librariile necesare
import numpy as np
import matplotlib.pyplot as plt
import math
from mpl_toolkits import mplot3d


# Functii deja implementate necesare: Introduceti orice functie scrisa de voi care rezolva direct un sistem liniar
# ...


### Construieste graficul functiei patratice definite de matricea A si vectorul b


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


def grafic_f(A, b):
    """
    Construieste graficul functiei f
    """

    # Construieste gridul asociat functiei
    (X1, X2, X3) = grid_discret(A, b)

    # Defineste o figura 3D
    fig1 = plt.figure()
    ax = plt.axes(projection="3d")

    # Construieste graficul functiei f folosind gridul discret X1, X2, X3=f(X1,X2)
    ax.plot_surface(X1, X2, X3, rstride=1, cstride=1, cmap='winter', edgecolor='none')

    # Etichete pe axe
    ax.set_xlabel('x1')
    ax.set_ylabel('x2')
    ax.set_zlabel('f(x1,x2)')

    # Titlu
    ax.set_title('Graficul functiei f')

    # Afiseaza figura
    fig1.show()


def linii_nivel(A, b, levels=10):
    """
    Construieste liniile de nivel ale functiei f
    """

    # Construieste gridul asociat functiei
    (X1, X2, X3) = grid_discret(A, b)

    # Ploteaza liniile de nivel ale functiei f
    fig2 = plt.figure()
    plt.contour(X1, X2, X3, levels=levels)  # levels = numarul de linii de nivel

    # Etichete pe axe
    plt.xlabel('x1')
    plt.ylabel('x2')

    # Titlu
    plt.title('Liniile de nivel ale functiei f')

    # Afiseaza figura
    fig2.show()


# Definire functie f prin matricea A si vectorul b
A = np.array([[3., 2.], [2., 6.]])  # Matrice pozitiv definita
b = np.array([[2.], [-8.]])

# Apelare functii grafic
grafic_f(A, b)
linii_nivel(A, b)

def dist_euclidiana(x):
    print(x)
    return math.sqrt(np.dot(x, x))

def metoda_de_rezolvare_1(A, b):
    x = [[1] for i in range(0, len(b))]
    print(x)
    k = 0
    r = b - np.matmul(A, x)

    print(r)
    while dist_euclidiana(r) > 10 ** (-10):
        alfa = np.matmul(np.transpose(r), r) / np.matmul(np.matmul(np.transpose(r), r), r)
        x = x + alfa * r
        k += 1
        r = b - np.matmul(A, x)
    return x

# Punctul de minim determinat prin rezolvarea sistemului A*x=b
x_num = metoda_de_rezolvare_1(A,b)

print(x_num)
plt.scatter(x_num[0], x_num[1], s=50, c='black', marker='*')
plt.show()
