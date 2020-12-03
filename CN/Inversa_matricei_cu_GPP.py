import numpy as np

def subs_desc_fast(a, b):
    """ (Optionala) Verifica daca matricea A este patratica + compatibilitatea cu vectorul b"""
    assert a.shape[0] == a.shape[1], 'Matricea sistemului nu este patratica'
    assert a.shape[0] == b.shape[0], 'Matricea sistemului si vectorul b nu se potrivesc'

    """ Initializeaza vectorul solutiei numerice."""
    n = b.shape[0] - 1
    x_num = np.zeros(shape=n+1)

    """ Determina solutia numerica."""
    x_num[n] = b[n] / a[n, n]        #Scrie ultima componenta a solutiei numerice
    #stim exact cate componente mai am de aflat, stiind ca este substitutie descendenta
    for k in range(n - 1, -1, -1):   #Merge invers
        s = np.dot(a[k, k + 1:], x_num[k + 1:])
        x_num[k] = (b[k] - s) / a[k, k]

    return x_num

#Metoda gauss cu pivotare partiala
def met_pivotare_partiala(a, b):
    """ (Optionala) Verifica daca matricea A este patratica + compatibilitatea cu vectorul b"""
    assert a.shape[0] == a.shape[1], 'Matricea sistemului nu este patratica'
    assert a.shape[0] == b.shape[0], 'Matricea sistemului si vectorul b nu se potrivesc'

    a_ext = np.concatenate((a, b[:, None]), axis = 1) #b - ia toate liniile si pune inca o dimensiune None
    n = b.shape[0] - 1
    for k in range(n):
        """ Determinantul trebuie sa fie dif de 0. Daca nu e, rang mai mic si nu e comp det"""
        """ Aflam pozitia pivotului de pe coloana k + verificare compatibilitate sistem"""
        if not a_ext[k:, k].any(): #ret true daca e un elem nenul sau false daca sunt toate nule
            raise AssertionError('Sistem incompatibil sau sistem compatibil nedeterminat')
        else:
            # Cum alegi privotul ca sa obtii MEG cu pivotare partiala
            p = np.argmax(np.abs(a_ext[k:, k]))
            p += k #Q: Ce dimensiune are vectorul in care cautam?
        """ Schimba linia 'k' cu 'p' daca pivotul nu se afla pe diagonala pricipala."""
        if k != p: #daca pivotul nu e pe diag principala
            a_ext[[p, k], :] = a_ext[[k, p], :]  #interschimba liniile

        """ Zero sub pozitia pivotului pe coloana. """
        for j in range(k + 1, n + 1):
            m = a_ext[j, k] / a_ext[k, k]
            a_ext[j, :] -= m * a_ext[k, :]

    """ Verifica compatibilitate again."""
    #daca det nu a fost dif de 0 elem din dr jos e 0
    if a_ext[n, n] == 0:
        raise AssertionError('Sistem incompatibil sau sistem compatibil nedeterminat')

    """ Gaseste solutia numerica folosind metoda substitutiei descendente. """
    x_num = subs_desc_fast(a_ext[:, :-1], a_ext[:, -1])
    return x_num



def calculeaza_inversa(a):
    """
    Calcularea inversei unei matrici a folosind metoda Gauss cu pivotare totala
    :return: a^(-1)
    """

    """
    Aplicam meg cu pivotare totala pentru calcularea inversei pentru a avea erori
    cat mai mici (daca este cazul)
    """

    """ Verifica daca matricea A este patratica """
    assert a.shape[0] == a.shape[1], 'Matricea sistemului nu este patratica'

    """ Verificare daca matricea e inversabila (determinantul e diferit de 0) """
    if np.linalg.det(a) == 0:
        raise AssertionError('Matricea nu e inversabila')

    n = a.shape[0]
    I = np.identity(n)
    A_inv = np.zeros(a.shape)

    """ 
    Stim ca A*A_inv = I
    Despartim matricile A_inv si I in coloane si calculam folosind meg fiecare coloana
    din A_inv.
    """
    for k in range(n):
        A_inv[:, k] = met_pivotare_partiala(a, I[:, k])

    return A_inv

print('MEG cu pivotare partiala')

A_gauss = np.array([
    [5., 1., -6.],
    [2., 1., -1.],
    [6., 12., 1.]
])
b_gauss = np.array([7., 8., 9.]).T  #calculam transpusa
x_sol = met_pivotare_partiala(A_gauss, b_gauss)
print(x_sol)

b_check = np.matmul(A_gauss, x_sol)
print(b_check)
print('\nInversa')
A_inv = calculeaza_inversa(A_gauss)
print(A_inv)
print(np.round(np.matmul(A_gauss, A_inv)))