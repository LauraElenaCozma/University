import numpy as np

def ex_1(A):
    n = A.shape[0]
    L = np.identity(n)
    R = np.zeros(A.shape)

    R[0][0] = A[0][0]
    for i in range(0, n-1):
        b = A[i][i+1]   # deasupra diag principale in A
        c = A[i+1][i]   # sub diag principala in A
        L[i+1][i] = c/R[i][i]   #li - sub diag principala in L
        R[i][i+1] = b    # si - deasupra diag principala in L
        R[i+1][i+1] = A[i+1][i+1] - L[i+1][i] * R[i][i+1]  # ri - diag principala in R

    return L, R


def rezolva_sistem(L, R, b):
    x = np.zeros(b.shape)
    y = np.zeros(b.shape)
    n = L.shape[0]
    # Ly = b; Rx = y
    # find y
    y[0] = b[0]
    for i in range(1, n):
        y[i] = b[i] - L[i][i-1] * y[i-1]
    #y_ = np.matmul(L, y)
    #print("rezultatul y")
    #print(y_)
    x[n-1] = y[n-1]/R[n-1][n-1]
    for i in range(n-2, -1, -1):
        x[i] = (y[i] - x[i+1] * R[i][i+1])/R[i][i]
    return x



A = np.array([
    [2., 3., 0., 0.],
    [6., 3., 9., 0.],
    [0., 2., 5., 2.],
    [0., 0., 4., 3.]
])
b = np.array([21., 69., 34., 22.]).T

L, R = ex_1(A)
print(A)
#print(L)
#print(R)
A_ = np.matmul(L, R)
#print(A_)
x = rezolva_sistem(L, R, b)

x_ = np.matmul(A, x.T)


################################################################

def matrice_tridiagonala(c, d, f, n):
    A = np.zeros([n, n])
    #  d f 0 0 0 ..... 0
    # c d f 0 0 ...... 0
    # 0 c d f 0 ...... 0
    # ..................
    # 0 0 0 ...... c d f
    # 0 0 0 ........ c d
    for i in range(n):
        A[i][i] = d
        if (i+1) < n:
            A[i][i+1] = f
        if (i-1) >= 0:
            A[i][i-1] = c

    b = np.ones(n)
    b[0] = b[n-1] = 2
    print("In matrice tridiagonala")
    print(A)
    print(b)
    return A, b


A_2, b_2 = matrice_tridiagonala(1, 2, 3, 5)
L_2, R_2 = ex_1(A_2)
print(np.matmul(L_2, R_2))
x_2_sol = rezolva_sistem(L_2, R_2, b_2)
print(x_2_sol)
b_2_ = np.matmul(A_2, x_2_sol)
print(b_2_)