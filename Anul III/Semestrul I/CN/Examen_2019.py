import numpy as np
import matplotlib.pyplot as plt

def SubsDesc(A, b):
    n = A.shape[0]
    x = np.zeros(n)
    x[n-1] = b[n-1]/A[n-1][n-1]
    k = n-2
    while k >= 0:
        x[k] = (b[k] - np.dot(A[k, (k+1):], x[(k+1):]))/A[k,k]
        k = k - 1
    return x


def GaussPivPart(A, b):
    n = A.shape[0]
    A_ext = np.concatenate((A, b[:, None]), axis = 1)
    print(A_ext)
    for k in range(n-1):
        if not A_ext[k:][k].any():
            raise AssertionError("Matricea nu are valori dif de 0 pe coloana")
        p = np.argmax(np.abs(A_ext[k:, k]))
        p = p + k
        print(p)
        if A_ext[p][k] == 0:
            raise AssertionError("Sistem incomp sau comp nedet")

        if p != k:
            A_ext[[p,k], :] = A_ext[[k,p], :]
        for l in range(k+1, n):
            m = A_ext[l][k]/A_ext[k][k]
            A_ext[l,:] -= m * A_ext[k,:]

        print(A_ext)
    if A_ext[n-1][n-1] == 0:
        raise AssertionError("Sistem incomp sau comp nedet")

    x = SubsDesc(A_ext[:, :-1], A_ext[:, -1])
    return x

A = np.array([
    [0., 1., 1.],
    [2., 1., 5.],
    [4., 2., 1.]
])

b = np.array([3., 5., 1.])

x = GaussPivPart(A, b)
print(x)
b_ = np.matmul(A, x)
print("Noul b")
print(b_)


def SplineC(X, Y, fpa, fpb, x):
    n = X.shape[0] - 1
    a = np.zeros(n)
    b = np.zeros(n+1)
    c = np.zeros(n)
    d = np.zeros(n)
    b[0] = fpa
    b[n] = fpb
    h = X[1] - X[0]
    S = 0
    for j in range(n):
        a[j] = Y[j]
        d[j] = (-2/(h**3)) * (Y[j+1] - Y[j]) + (1/(h**2)) * (b[j+1] + b[j])
        c[j] = (3/(h**2)) * (Y[j+1] - Y[j]) - (b[j+1] + 2 * b[j])/h

    for j in range(n):
        if X[j] >= x and x <= X[j+1]:
            S = a[j] + b[j] * (x - X[j]) + c[j] * ((x-X[j])**2) + d[j] * ((x-X[j])**3)

    return S


x_client = np.array([1., 2., 3.])
y_client = np.array([2., 3., 5.])

x_domain = np.linspace(x_client[0], x_client[-1], 20)  # Discretizare domeniu (folosit pentru plotare)
plt.scatter(x_client, y_client, marker='*', c='red', s=200, label='Date client')

# Calculare discretizare polinom
y_spline = np.zeros(len(x_domain))  # Folosit pentru a stoca valorile aproximate
for i in range(len(x_domain)):
    y_spline[i] = SplineC(x_client, y_client, 0, 0, x_domain[i])
plt.grid()
plt.show()