import numpy as np

# ##########################################################
# Metoda substitutiei descendente, functionala, dar nu rapida
# ##########################################################

def subs_desc_slow(a, b):
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
        # TODO Cu slice-uri
        s = np.dot(a[k, k + 1:], x_num[k + 1:])
        '''
        s = 0.
        #iteram elementele de la dreapta pivotului
        for j in range(k + 1, n + 1, 1):
            s += a[k, j] * x_num[j]
        '''

        x_num[k] = (b[k] - s) / a[k, k]

    return x_num



# ##########################################################
# Date
# ##########################################################
A = np.array([
   [1., 2., 3.],
   [0., 1., 2.],
   [0., 0., 2.]
]);

x_sol = np.array([1., 1., 1.])
b_ = np.matmul(A, x_sol)
print(b_)

x_numeric = subs_desc_slow(A, b_)
print(x_numeric)

def met_fara_pivotare(a, b):
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
            p = np.argmin(a_ext[k:, k] == 0) #trebuie sa ii adunam k pentru ca el da relativ la k
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
    x_num = subs_desc_slow(a_ext[:, :-1], a_ext[:, -1])
    return x_num

#Metoda de eliminare gauss
A_gauss = np.array([
    [2., 3., 0.],
    [3., 4., 2.],
    [1., 3., 1.]
])
x_sol_gauss = np.array([1., 2., 3.])
b_gauss = np.matmul(A_gauss, x_sol_gauss)

x_numeric_gauss = met_fara_pivotare(A_gauss, b_gauss)
print(x_numeric_gauss)

eps = 10 ** (-20)
a_limitare = np.array([
    [eps, 1.],
    [1., 1.]
])

b_limitare = np.array([1., 2.])
x_sol_limitare = met_fara_pivotare(a_limitare, b_limitare)
print(x_sol_limitare)  #rezultat: [0., 1.] si nu e corect
#1/eps e un numar foarte mare


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
            #TODO: Cum alegi privotul ca sa obtii MEG cu pivotare partiala
            p = np.argmin(a_ext[k:, k] == 0) #trebuie sa ii adunam k pentru ca el da relativ la k
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
    x_num = subs_desc_slow(a_ext[:, :-1], a_ext[:, -1])
    return x_num
