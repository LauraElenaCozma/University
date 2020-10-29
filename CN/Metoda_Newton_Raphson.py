import numpy as np
import matplotlib.pyplot as plt

def f(x):
    return np.cos(x) - x

def df(x):
    return -np.sin(x) - 1
a = 0
b = np.pi/2
x = np.linspace(a, b, 100)
y = f(x)
x_0 = np.pi / 4
eps = 10 ** (-5)



#b
def metoda_NR(f, df, a, b, epsilon, x_0):
    assert epsilon > 0, 'Mesaj eroare'
    assert a < b, 'Mesaj eroare'
    assert np.sign(f(a)) * np.sign(f(b)) < 0, 'Mesaj eroare'

    #Verifica ca se indeplinesc si celelalte conditii din teorema prezentata
    x_old = x_0
    N = 0
    #Iteratiile algoritmului
    while True:
        x_new = x_old - f(x_old)/df(x_old)
        N += 1

        if np.abs(f(x_new)) < epsilon:
            break

        x_old = x_new

    return x_new, N

x_new_, N_ = metoda_NR(f, df, a, b, eps, x_0)
print(x_new_)

#a
plt.figure(0)
plt.plot(x, y)
plt.xlabel('x')
plt.ylabel('y')
plt.title('Metoda N-R')
plt.axvline(0, c = 'black')
plt.axhline(0, c = 'black')
plt.axis('scaled')
plt.grid()
plt.scatter(x_new_, 0)
plt.legend(['f(x)', 'x_num'])
plt.show()