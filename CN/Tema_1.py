import matplotlib.pyplot as plt
import numpy as np
import math

'''
Exercitiul 1
Sa se gaseasca o aproximare a valorii √3 cu o precizie de 7 zecimale.
'''

'''
Problema se reduce la rezolvarea ecuatiei f(x) = 0, unde f(x) = x * x - 3, cu x >= 0
Calculam f'(x) = 2x, deci radacina ecuatiei este x1 = 0.

Construim tabelul de valori:

x     |   0                 3
______|__________________________
f(x)  |  -3   crescatoare   6
______|__________________________
f'(x) |   0 + + + + + + + + + + +

Deoarece radicalul lui 3 este mai mic decat 3, putem alege drept capat din dreapta al intervalului x = 3.
Intrucat metoda bisectiei este cea mai putin restrictiva, verificam daca respecta conditia:
f(0) * f(3) = (-3) * 6 < 0
Asadar, pe intervalul [0, 3] functia este crescatoare, iar f(0) * (3) < 0, deci solutia este unica.

Pentru a generaliza rezolvarea, o vom face pentru functia f(x) = x * x - n, 
adica dorim sa calculam aproximarea valorii √n cu o precizie de prec zecimale.

'''
def aprox_radical_cu_precizie(n, prec):
    '''
    :param n: Numarul caruia trebuie sa i se calculeze radicalul
    :param prec: Precizia aproximarii
    :return: Aproximarea valorii √n cu o precizie de prec zecimale

    Metoda aplicata este metoda bisectiei, similara cautarii binare.
    Trebuie sa gasim o valoare mid astfel incat mid * mid sa aproximeze n.
    Deci, conditia de oprire va fi cand abs(n - mid * mid) <= eps, adica ultima
    valoare a radicalului gasita aproximeaza cu o precizie de prec zecimale.

    Capetele intervalului [a, b] sunt stabilite [0, n], conform analizei anterioare.
    '''
    a = 0
    b = n
    mid = (a + b) / 2
    '''
    eps este stabilit la 1/10^(prec+1), deoarece vrem ca primele prec zecimale sa 
    corespunda, iar incepand cu prec + 1 pot interveni erori
    '''
    eps = 10 ** (-(prec + 1))
    while abs(n - mid * mid) > eps:
        '''
        La fiecare pas se calculeaza mijlocul intervalului. 
        - Daca am ajuns exact la radical, atunci ne oprim si returnam rezultatul
        - Daca mijlocul^2 este mai mare decat valoarea lui n, atunci valoarea cautata
        se afla la stanga, deci modificam b = mid
        - Daca mijlocul^2 este mai mic decat valoarea lui n, atunci valoarea cautata
        se afla la dreapta, deci modificam a = mid
        '''
        if (mid * mid == n):
            return mid
        elif (mid * mid < n):
            a = mid
        else:
            b = mid
        mid = (a + b) / 2
    return mid

#Afisam rezultatele cu round pentru a se vedea mai usor daca exista diferente
print('Ex. 1')
print('Valoarea este: ' + str(round(math.sqrt(3), 7)))
print('Aproximarea calculata este: ' + str(round(aprox_radical_cu_precizie(3, 7))))


'''
Exercitiul 2
Rezolvati numeric ecuatia e ^ (x - 2) = cos(e ^ (x - 2)) + 1. Sa se ilustreze grafic 
cele doua functii si punctul lor de intersectie
'''

'''
Definim functiile din enunt.
Pentru a afla punctul de intersectie, trebuie sa calculam radacina ecuatiei:
e ^ (x - 2) - cos(e ^ (x - 2)) - 1 = 0. Deci, definim si aceasta functie ca
function_ex2(x).
'''
def function1_ex2(x):
    return np.exp(x - 2)

def function2_ex2(x):
    return np.cos(np.exp(x - 2)) + 1

def function_ex2(x):
    return function1_ex2(x) - function2_ex2(x)

'''
Folosim metoda bisectiei intrucat este cea mai pun restrictiva.
Trebuie doar sa ne asiguram ca pe intervalul ales se respecta conditia: f(a) * f(b) < 0

Calculam f'(x) = e^(x-2) * (sin(e^(x-2)) + 1)
Pentru f'(x) = 0 gasim solutiile de forma: e^(x-2) = {3pi/2, 7pi/2, 11pi/2...}
Deci, x = {ln(3pi/2) + 2, ln(7pi/2) + 2, ln(11pi/2) + 2...}

Construim tabelul de valori:
x     |             ln(3pi/2) + 2           ln(7pi/2) + 2
______|_______________________________________________________
f(x)  |    cresc.     3.71       cresc.          9.99  cresc.
______|_______________________________________________________
f'(x) | + + + + + + + + 0 + + + + + + + + + + + +  0 + + + + 

Observam ca pe intervalul (-inf, ln(3pi/2) + 2 ) functia e crescatoare
ln(3pi/2) + 2 aproximativ egal cu 3.55.
Calculam f(0) = -1.85
f(3) = 2.63, deci f(0) * f(3) < 0. Intervalul ales este [0,3], deoarece solutia este unica.
'''

def bisectie(f, a, b, eps):
    assert eps > 0, 'Epsilon trebuie sa aiba valoare pozitiva'
    assert a < b, 'Capetele intervalului sunt puse incorect'
    assert np.sign(f(a)) * np.sign(f(b)) < 0, 'Nu respecta conditia metodei bisectiei'
    num_it = int(np.floor(math.log2((b - a) / eps)))        #calculam numarul de iteratii
    fa = f(a)                                               #calculam functia in capetele intervalului
    fb = f(b)
    if fa == 0:                                             #am gasit solutia in capatul a
        return a, 0
    elif fb == 0:                                           #am gasit solutia in capatul b
        return b, 0
    for k in range(num_it):
        x = (a + b) / 2                                     #calculam mijlocul si valoarea functiei in mijloc
        fx = f(x)
        if fx == 0:                                         #daca am ajuns la solutie o returnam
            return x, (k + 1)
        else:

            if (fa * fx) < 0:                               #solutia se afla in partea stanga
                b = x
            elif (fb * fx) < 0:                             #solutia se afla in partea dreapta
                a = x
        fa = f(a)                                           #actualizam valorile fa si fb
        fb = f(b)
    return x, num_it                                        #am ajuns la solutie la finalul iteratiilor

print('Ex. 2')
x = np.linspace(-1, 6, 10000)                               #cum intervalul ales pentru gasirea solutiei este [0,3],
y1 = function1_ex2(x)                                       #am ales un interval mai larg pentru intregul grafic
y2 = function2_ex2(x)
plt.plot(x, y1)
plt.plot(x, y2, 'r')
plt.axvline(0, c = 'black')
plt.ylim(-5, 5)
plt.axhline(0, c = 'black')
sol, N = bisectie(function_ex2, 0, 3, 10 ** (-5))
print('Pe [0, 3] solutia este ' + str(sol) + ' cu ' + str(N) + ' iteratii.')
plt.scatter(sol, function1_ex2(sol))
plt.legend(['$e^{x-2}$', 'cos($e^{x-2}$)+1'])
plt.title('Graficele functiilor si intersectia lor')
plt.show()


'''
Exercitiul 3
Creati functia pozitie_falsa care determina solutia ecuatiei f(x) = 0 cu x din [a,b]
Intr-un fisier script sa se construiasca graficul functiei f(x) = x^3-7*x^2+14*x-8 pe intervalul [−5, 5]. 
Alegeti 3 intervale astfel incat metoda pozitiei false sa fie convergenta. 
Aflati cele 3 solutii apeland functia pozitie falsa cu eroarea de aproximare eps = 10^(-5).
'''
def pozitie_falsa(f, a, b, eps):
    '''
    :param f: functia care determina ecuatia
    :param a, b: capetele intervalului in care se rezolva ecuatia
    :param eps: eroarea de aproximare
    :return: solutia ecuatiei si numarul de iteratii necesare N

    Vom inlocui sirul (ak) cu a0 si a1, intrucat la fiecare pas avem nevoie
    doar de ultimele 2 valori. a1 reprezinta ak, iar a0 = ak-1. Analog pentru (bk)
    si (xk).
    Formula pentru calcularea lui x0 si x1 rezulta din intersectia lui AB( A(a0,f(a0)),
    B(b0, f(b0)) cu OX.

    '''
    assert eps > 0, 'Epsilon trebuie sa aiba valoare pozitiva'
    assert a < b, 'Capetele intervalului sunt puse incorect'
    assert np.sign(f(a)) * np.sign(f(b)) < 0, 'Nu respecta conditia metodei pozitiei false'

    if f(a) == 0:                                             #am gasit solutia in capatul a
        return a, 0
    elif f(b) == 0:                                           #am gasit solutia in capatul b
        return b, 0

    a0 = a                      #initializam capetele intervalelor
    b0 = b
    x0 = (a0 * f(b0) - b0 * f(a0)) / (f(b0) - f(a0))    #calculam x0
    N = 0
    while True:
        N += 1                   #actualizam numarul de iteratii
        if f(x0) == 0:           #solutia a fost gasita, o returnam prin x1
            x1 = x0
            break;
        elif f(a0) * f(x0) < 0:  #am micsorat intervalul de cautare spre stanga
            a1 = a0
            b1 = x0
        else:                   #am micsorat intervalul de cautare spre dreapta
            a1 = x0
            b1 = b0

        x1 = (a1 * f(b1) - b1 * f(a1)) / (f(b1) - f(a1))  #calculam noua intersectie
        if (abs(x1 - x0) / abs(x0)) < eps:  #verificam daca ne-am apropiat suficient de mult de solutie; solutia poate sa fie in 0
            break               #astfel folosim eroarea absoluta
        x0 = x1                 #actualizam x0 cu valoarea noua calculata
    return x1, N


'''
Definim functia din enunt
'''
def function3(x):
    return x ** 3 - 7 * (x ** 2) + 14 * x - 8


'''
Alegerea subintervalelor:
Conditiile metodei pozitiei false sunt:
1) f(a) * f(b) < 0
2) f' nu se anuleaza pe [a,b]
3) f" nu se anuleaza pe [a,b]

Calculam f'(x) = 3 * x^2 - 14 * x + 14
Radacinile ecuatiei f'(x) = 0 sunt:
x1 = 1.45 si x2 = 3.21, deci in aceste puncte f' se anuleaza 
Calculam f"(x) = 6 * x - 14
Radacina ecuatiei f"(x) = 0 este:
x3 = 2.33

Construim tabelul de valori(+/- = functia ia valori pozitive/negative)

x     |-5         1.45        2.33           3.21        5  
______|_______________________________________________________
f(x)  |-378   sc. 0.63  sd.  -0.73     sd.  -2.11  sc.   12    
______|_______________________________________________________
f'(x) | + + + + +  0 - - - - - - - - - - - -  0 + + + + + + +  
______|_______________________________________________________
f"(x) | - - - - - - - - - - -  0 + + + + + + + + + + + + + +                 
______|_______________________________________________________

Cum nu putem alege 1.45, 2.33 si 3.21, aflam ca functia:
 - creste pe [-5, 1.44], iar f(-5) * f(1.44) < 0
 - scade pe [1.46, 2.32], iar f(2.32) * f(1.46) < 0
 - creste pe [3.22, 5], iar f(3.22) * f(5) < 0
Deoarece pe aceste intervale sunt monotone, respecta conditia in capete, iar f' si f'' nu se anuleaza, 
vom alege intervalele:  [-5, 1.44], [1.46, 2.32], [3.22, 5], iar pe fiecare va fi cate o solutie unica.
'''
print('Ex. 3')
x = np.linspace(-5, 5, 10000) #discretizam intervalul
y = function3(x)              #aplicam function3 pe valorile lui x ca sa aflam valorile lui y
plt.plot(x, y)                #plotam functia
plt.axvline(0, c = 'black')   #afisam axele de coordonate
plt.ylim(-5, 5)
plt.axhline(0, c = 'black')
plt.legend(['$x^3-7*x^2+14*x-8$'])  #construim legenda si punem un titlu
plt.title('Graficul functiei')

sol1, N1 = pozitie_falsa(function3, -5, 1.44, 10 ** (-5))
sol2, N2 = pozitie_falsa(function3, 1.46, 2.32, 10 ** (-5))
sol3, N3 = pozitie_falsa(function3, 3.22, 5, 10 ** (-5))
print('Pe [-5; 1.44] solutia este ' + str(sol1) + ' cu ' + str(N1) + ' iteratii.')
print('Pe [1.46; 2.32] solutia este ' + str(sol2) + ' cu ' + str(N2) + ' iteratii.')
print('Pe [3.22; 5] solutia este ' + str(sol3) + ' cu ' + str(N3) + ' iteratii.')
plt.scatter(sol1, 0)                #construim punctele obtinute pe grafic
plt.scatter(sol2, 0)
plt.scatter(sol3, 0)
plt.show()

'''
Exercitiul 4
Creati functia secanta care determina solutia ecuatiei f(x) = 0 cu x din [a,b]
Intr-un fisier script sa se construiasca graficul functiei f(x) = x^3 + x^2 - 2x pe intervalul [−3, 3]. 
Alegeti 3 intervale astfel incat metoda secantei sa fie convergenta. 
Aflati cele 3 solutii apeland functia pozitie falsa cu eroarea de aproximare eps = 10^(-5).
'''


def secanta(f, a, b, x0, x1, eps):
    '''
    :param f: functia care determina ecuatia
    :param a, b: capetele intervalului in care se rezolva ecuatia
    :param x0, x1: punctele de start
    :param eps: eroarea de aproximare
    :return: solutia ecuatiei si numarul de iteratii necesare N

    Vom inlocui sirul (xk) cu x0, x1 si x2, intrucat la fiecare pas avem nevoie
    doar de ultimele 3 valori. x2 reprezinta xk, x1 = ak-1, iar x0 = ak-2.

    La fiecare pas construim secanta si aflam x2 conform formulei. Ne oprim cand eroarea relativa
    e mai mica decat eroarea de aproximare
    '''

    assert eps > 0, 'Epsilon trebuie sa aiba valoare pozitiva'
    assert a < b, 'Capetele intervalului sunt puse incorect'
    assert a <= x0 and x0 <= b, 'x0 nu se afla in interval'
    assert a <= x1 and x1 <= b, 'x1 nu se afla in interval'
    assert np.sign(f(a)) * np.sign(f(b)) < 0, 'Nu respecta conditia metodei secantei'

    if f(a) == 0:                                             #am gasit solutia in capatul a
        return a, 0
    elif f(b) == 0:                                           #am gasit solutia in capatul b
        return b, 0

    N = 1
    while True:
        N += 1                                                #incrementam numarul de iteratii
        x2 = (x0 * f(x1) - x1 * f(x0)) / (f(x1) - f(x0))      #actualizam x2
        if x2 < a or x2 > b:
            print('Introduceti alte valori pentru x0 si x1')
            break
        x0 = x1                                               #actualizam x0 si x1
        x1 = x2
        if (abs(x1 - x0)) < eps:                           #deoarece solutia x = 0 poate sa fie in x0
            break                                          #si impartirea la 0 nu e posibila, folosim eroarea absoluta
    return x2, N


'''
Definim functia din enunt
'''
def function4(x):
    return x ** 3 + x ** 2 - 2 * x

'''
Alegerea subintervalelor:
Conditiile metodei pozitiei false sunt:
1) f(a) * f(b) < 0
2) f' nu se anuleaza pe [a,b]

Calculam f'(x) = 3x^2 + 2x -2
Radacinile ecuatiei f'(x) = 0 sunt:
x1 = 0.54 si x2 = -1.21, deci in aceste puncte f' se anuleaza 

Construim tabelul de valori(+/- = functia ia valori pozitive/negative)

x     |-3         -1.21                      0.54        3  
______|_______________________________________________________
f(x)  |-12   sc.   2.11         sd.         -0.63  sc.   30
______|_______________________________________________________
f'(x) | + + + + +  0 - - - - - - - - - - - -  0 + + + + + + +  
______|_______________________________________________________

Cum nu putem alege -1.21 si 0.54, aflam ca functia:
 - creste pe [-3, -1.2], iar f(-3) * f(-1.2) < 0
 - scade pe [-1.22, 0.53], iar f(-1.22) * f(0.53) < 0
 - creste pe [0.55, 3], iar f(0.55) * f(3) < 0
Deoarece pe aceste intervale sunt monotone, respecta conditia in capete, iar f' si f'' nu se anuleaza, 
vom alege intervalele (fiecare avand cate o solutie unica):
 [-3, -1.2] cu valorile x0 si x1 aproape de capete sau chiar capetele (deoarece x0 = -3
 iesea din interval dupa o iteratie, am ales -2.5)
 [-1.22, 0.53] cu x0 si x1 capetele intervalului, alegerea optima
 [0.55, 3] cu x0 si x1 capetele intervalului, alegerea optima
'''

print('Ex. 4')
x = np.linspace(-3, 3, 10000)
y = function4(x)
plt.plot(x, y)
sol1, N1 = secanta(function4, -3, -1.2, -2.5, -1.2, 10 ** (-5))
sol2, N2 = secanta(function4, -1.22, 0.53, -1, 0.5, 10 ** (-5))
sol3, N3 = secanta(function4, 0.55, 3, 0.55, 3, 10 ** (-5))
plt.scatter(sol1, 0)
plt.scatter(sol2, 0)
plt.scatter(sol3, 0)

print('Pe [-3, -1.2] solutia este ' + str(sol1) + ' cu ' + str(N1) + ' iteratii.')
print('Pe [-1.22, 0.53] solutia este ' + str(sol2) + ' cu ' + str(N2) + ' iteratii.')
print('Pe [0.55, 3] solutia este ' + str(sol3) + ' cu ' + str(N3) + ' iteratii.')

plt.axvline(0, c = 'black')
plt.ylim(-3, 3)
plt.axhline(0, c = 'black')
plt.legend(['$x^3+x^2-2*x$'])
plt.title('Graficul functiei')
plt.show()

