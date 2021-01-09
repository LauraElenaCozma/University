import numpy as np
import matplotlib.pyplot as plt

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
        aprox_value += Y[k] * (num_L) / (numitor_L)
    return aprox_value


def spline_liniara(X, Y, pointx):
    """ Metoda de interpolare spline liniara.
    :param X: X = [X0, X1, ..., Xn]
    :param Y: [Y0=f(X0), Y1=F(X1), ..., Yn=f(Xn)]
    :param pointx: Punct in care doresti o valoare aproximata a functiei
    :return: aprox_value: Valoarea aproximata calculata interpolarea spline liniara in pointx
    """
    n = np.shape(X)[0]
    a = np.zeros(X.shape)
    b = np.zeros(X.shape)
    aprox_value = 0
    for i in range(n-1):
        a[i] = Y[i]
        b[i] = (Y[i + 1] - Y[i])/(X[i + 1] - X[i])

    for i in range(n-1):
        if pointx >= X[i] and pointx <= X[i+1]:
            aprox_value = a[i] + b[i] * (pointx - X[i])
            break
    return aprox_value

# ======================================================================================================================
# Datele clientului
# ======================================================================================================================
# Nodurile de interpolare
x_client_all = [55., 69, 75, 81, 88, 91, 95, 96, 102, 108, 116, 126, 145, 156, 168, 179, 193, 205,
                222, 230, 235, 240, 242, 244, 253, 259]
y_client_all = [162., 176, 188, 209, 229, 238, 244, 256, 262, 259, 254, 260, 262, 265, 263, 260, 259,
                252, 244, 239, 233, 227, 226, 224, 224, 221]


# Date de simulare
select_from = 3  # TODO: Selecteaza alte valori ('1' ca sa afiseze toate datele)
                 # Extrage date client din 'select_from' in 'select_from' (simulari)
x_client = []
y_client = []
for i in range(len(x_client_all)):
    if i % select_from == 0:
        x_client.append(x_client_all[i])
        y_client.append(y_client_all[i])

x_client = np.array(x_client)
y_client = np.array(y_client)

N = len(x_client) - 1  # Gradul polinomului Lagrange / numar de subintervale

x_domain = np.linspace(x_client[0], x_client[-1], 100)  # Discretizare domeniu (folosit pentru plotare)


# Afisare grafic figura
plt.figure(0)
plt.xlabel('x')
plt.ylabel('y = f(x)')

# Afisare date client pe grafic
plt.scatter(x_client, y_client, marker='*', c='red', s=5, label='Date client')

# Calculare discretizare polinom
y_interp_lagrange = np.zeros(len(x_domain))  # Folosit pentru a stoca valorile aproximate
y_interp_spline_liniara = np.zeros(len(x_domain))  # Folosit pentru a stoca valorile aproximate
for i in range(len(x_domain)):
    y_interp_lagrange[i] = metoda_lagrange(x_client, y_client, x_domain[i])  # TODO: Trebuie sa scrieti voi metoda
    y_interp_spline_liniara[i] = spline_liniara(x_client, y_client, x_domain[i])  # TODO: Trebuie sa scrieti voi metoda


# Afisare doggo
image = np.load('./frida_doggo.npy')
plt.imshow(image, extent=[0, 300, 0, 300])

# Afisare grafic aproximare
plt.plot(x_domain, y_interp_lagrange, c='w', linewidth=2, linestyle='-.', label='Metoda Lagrange')
plt.plot(x_domain, y_interp_spline_liniara, c='g', linewidth=2, linestyle='-', label='Spline Liniara')
plt.title('Interpolare, N={}'.format(N))
plt.legend()
plt.xlim([-1, 305])  # Limiteaza domeniul de afisare
plt.ylim([-1, 305])  # Limiteaza co-domeniul de afisare
plt.show()
