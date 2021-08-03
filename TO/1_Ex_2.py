import numpy as np
from scipy.optimize import minimize

'''Cozma Laura-Elena, 344'''

''' Alegem dimensiunile pentru m, n si p '''
m = 2
n = 2
p = 2

''' Generam matricile folosind valori random '''
A = np.random.rand(m, n)
b = np.random.rand(m)
C = np.random.rand(p, n)
d = np.random.rand(p)

''' Alegem punctul de start x0 '''
x0 = np.array([2, 2])

''' Definim functia care trebuie minimizata '''
def f(x):
    '''
    Forma initiala a functiei este 1/2*‖Ax−b‖^2
    Eliminam norma dupa formula (Ax-b).T*(Ax-b)
    '''
    return 1/2. * x.T @ A.T @ A @ x - b.T @ A @ x - 1/2. * b.T @ b

''' Definim constrangerea din enunt '''
def constraint(x):
    return np.atleast_1d(d - C@x)

''' Apelam functia minimize pentru a gasi minimul '''
res = minimize(f, x0,method="SLSQP",constraints={"fun": constraint, "type": "ineq"})
print('Punctul de minim:')
print(res.x)


'''
Generati 2 seturi de date (A,b,C,d) astfel incat:  
(i) pentru primul set, multimea punctelor de extrem ale functiei obiectiv sa fie fezabile; 
(ii) pentru al doilea set, sa existe cel putin un punct de extrem nefezabil.
'''

'''
Tinem cont ca punctele de extrem neconstrans ale functiei satisfac conditiile de ordin I:
A^T(Ax-b) = 0. <=> A^t*Ax - A^tb = 0 <=> A^t*Ax = A^tb
Pentru ca multimea sa fie fezabila, trebuie ca Cx <= d.

(i) Cum stim ca A^t*Ax = A^tb, putem stabili C = A^tA
Rezulta ca A^tAx <= d <=> A^tb <= d. Astfel, pentru a face multimea fezabila, consideram d = A^tb, iar
inegalitatea va fi satisfacuta.
'''

'''
Pastram dimensiunile pentru m si n stabilite la punctul a
Generam matricile A si b si generam C si d pe baza lor
'''

print('\nPunctul b.(i)')
A = np.random.rand(m, n)
b = np.random.rand(m)
C = A.T @ A
d = A.T @ b
print('Matricea A:')
print(A)
print('Matricea b:')
print(b)
print('Matricea C:')
print(C)
print('Matricea d:')
print(d)

'''
(ii) Analog punctului (i) alegem C = A^tA, iar d=A^tb-(1,1).T (<d, deci nu va mai satisface inegalitatea)
'''
print('\nPunctul b.(ii)')
A = np.random.rand(m, n)
b = np.random.rand(m)
C = A.T @ A
d = A.T @ b - 1
print('Matricea A:')
print(A)
print('Matricea b:')
print(b)
print('Matricea C:')
print(C)
print('Matricea d:')
print(d)
