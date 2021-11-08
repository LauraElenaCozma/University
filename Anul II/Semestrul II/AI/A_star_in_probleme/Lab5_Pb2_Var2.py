import copy
import time
import math
start_time = time.time()
""" definirea problemei """

'''
Fata de prima varianta trimisa, am modificat afisarea si am inclus ambele euristici in acelasi fisier .py.
'''
euristica = 1


class Nod:
    def __init__(self, info, h):
        self.info = info    #o matrice
        self.h = h

    def __str__ (self):
        return "({}, h={})".format(self.info, self.h)
    def __repr__ (self):
        return f"({self.info}, h={self.h})"


class Problema:
    def __init__(self, start=[[0, 4, 3], [2, 8, 5], [1, 7, 6]], scop=[[1, 2, 3], [4, 5, 6], [7, 8, 0]]):
        self.l_matrice = len(start)
        self.nod_start = Nod(start, float('inf'))
        self.nod_scop = scop		# doar info (fara h)
        self.N = len(start) * len(start) - 1


    def cauta_nod_nume(self, info):
        """Stiind doar informatia "info" a unui nod,
        trebuie sa returnati fie obiectul de tip Nod care are acea informatie,
        fie None, daca nu exista niciun nod cu acea informatie."""

        for nod in self.noduri:  # parcurgem nodurile
            if nod.info == info:  # daca obiectul de tip nod are informatia info
                return nod  # il returnam
        return None



""" Sfarsit definire problema """



""" Clase folosite in algoritmul A* """

class NodParcurgere:
    """O clasa care cuprinde informatiile asociate unui nod din listele open/closed
        Cuprinde o referinta catre nodul in sine (din graf)
        dar are ca proprietati si valorile specifice algoritmului A* (f si g).
        Se presupune ca h este proprietate a nodului din graf
    """

    problema = None		# atribut al clasei (se suprascrie jos in __main__)


    def __init__(self, nod_graf, parinte=None, g=0, f=None):
        self.nod_graf = nod_graf	# obiect de tip Nod
        self.parinte = parinte		# obiect de tip NodParcurgere
        self.g = g					# costul drumului de la radacina pana la nodul curent
        if f is None :
            self.f = self.g + self.nod_graf.h
        else:
            self.f = f

    def euristica_1(self, info):                            #21 de iteratii pe exemplu, timp de 0.004 secunde
        # nr de pozitii pe care difera configuratiile
        h = 0
        nod_scop = self.problema.nod_scop
        for i in range(self.problema.l_matrice):  # mai putin precis decat distanta Manhattan
            for j in range(self.problema.l_matrice):
                if info[i][j] != 0 and nod_scop[i][j] != info[i][j]:
                    h += 1
        return h


    def euristica_2(self, info):                            #13 iteratii pe exemplu, timp de 0.001 secunde
        # suma distantelor Manhattan intre pozitia din configuratia curenta si cea finala
        h = 0
        nod_scop = self.problema.nod_scop
        N = self.problema.l_matrice  # e o metoda mai precisa; e mult mai aproape de realitate, insumand distantele pe care ar mai trebui sa le parcurga
        for c in range(1, N * N):
            i1, j1 = cauta_poz_numar(info, c)
            i2, j2 = cauta_poz_numar(nod_scop, c)
            h += (abs(i1 - i2) + abs(j1 - j2))
        return h

    def drum_arbore(self):
        """
            Functie care calculeaza drumul asociat unui nod din arborele de cautare.
            Functia merge din parinte in parinte pana ajunge la radacina
        """
        nod_c = self
        drum = [nod_c]
        while nod_c.parinte is not None:
            drum = [nod_c.parinte] + drum
            nod_c = nod_c.parinte
        return drum


    def contine_in_drum(self, nod):
        """
            Functie care verifica daca nodul "nod" se afla in drumul dintre radacina si nodul curent (self).
            Verificarea se face mergand din parinte in parinte pana la radacina
            Se compara doar informatiile nodurilor (proprietatea info)
            Returnati True sau False.

            "nod" este obiect de tip Nod (are atributul "nod.info")
            "self" este obiect de tip NodParcurgere (are "self.nod_graf.info")
        """
        nod_curent = self
        while nod_curent is not None:  # mergem din parinte in parinte pana in radacina
            if nod.info == nod_curent.nod_graf.info:  # daca au informatiile il returnam
                return True
            nod_curent = nod_curent.parinte
        return False

    # se modifica in functie de problema
    def expandeaza(self):
        """Pentru nodul curent (self) parinte, trebuie sa gasiti toti succesorii (fiii)
        si sa returnati o lista de tupluri (nod_fiu, cost_muchie_tata_fiu),
        sau lista vida, daca nu exista niciunul.
        (Fiecare tuplu contine un obiect de tip Nod si un numar.)
        """

        succesori = []

        poz_i, poz_j = cauta_poz_numar(self.nod_graf.info, 0)           #gasim pozitia lui 0

        dir = [[0, -1], [-1, 0], [0, 1], [1, 0]]
        for d in dir:
            n_poz_i = poz_i + d[0]
            n_poz_j = poz_j + d[1]                         #calculam pozitiile vecinilor
            if 0 <= n_poz_i and n_poz_i < problema.l_matrice and 0 <= n_poz_j and n_poz_j < problema.l_matrice:  #daca e o mutare valida
                n_succ = copy.deepcopy(self.nod_graf.info)
                n_succ[poz_i][poz_j], n_succ[n_poz_i][n_poz_j] = n_succ[n_poz_i][n_poz_j], n_succ[poz_i][poz_j]
                if euristica == 1:
                    h_succesor = self.euristica_1(n_succ)
                    succesori.append((Nod(n_succ, h_succesor), 1))  # am stabilit g = 1
                else:
                    h_succesor = self.euristica_2(n_succ)
                    succesori.append((Nod(n_succ, h_succesor), 1))  # am stabilit g = 1


        return succesori

    # se modifica in functie de problema
    def test_scop(self):
        return self.nod_graf.info == self.problema.nod_scop


    def __str__ (self):
        parinte = self.parinte if self.parinte is None else self.parinte.nod_graf.info
        return f"({self.nod_graf}, parinte={parinte}, f={self.f}, g={self.g})"



""" Algoritmul A* """

def cauta_poz_numar(lista , c):
    '''
    returneaza pozitia pe care se afla numarul c in matricea lista
    '''
    for i in range(problema.l_matrice):
        for j in range(problema.l_matrice):
             if lista[i][j] == c:
                return (i, j)

def str_info_noduri(l):
    """
        o functie folosita strict in afisari - poate fi modificata in functie de problema
    """
    sir = "["
    for x in l:
        sir += str(x) +" "
    sir += "]"
    return sir

def afisare_simpla(L):
    '''
    afisare particularizata pentru problema 8-puzzle
    '''

    sir = ""
    for Li in L:        #cate un element de pe drumul gasit
        matrice = Li.nod_graf.info
        sir += afisare(matrice) + "\n"
    return sir

def afisare(config):
    sir = ""
    for linii in config:
        for elem in linii:
            sir += str(elem) + " "
        sir += "\n"

    return sir

def afis_succesori_cost(l):
    """
        o functie folosita strict in afisari - poate fi modificata in functie de problema
    """
    sir = ""
    for (x, cost) in l:
        sir += "\nnod:  " +str(x) + ", cost arc:" + str(cost)

    return sir


def in_lista(l, nod):
    """
    lista "l" contine obiecte de tip NodParcurgere
    "nod" este de tip Nod
    """
    for i in range(len(l)):
        if l[i].nod_graf.info == nod.info:
            return l[i]
    return None


def a_star():
    rad_arbore = NodParcurgere(NodParcurgere.problema.nod_start)
    open = [rad_arbore]		# open va contine elemente de tip NodParcurgere
    closed = []				# closed va contine elemente de tip NodParcurgere
    gasit = False
    nod_curent = None
    pas = 0
    while len(open) != 0:  # cat timp open nu e vida repetam
        pas += 1
        nod_curent = open.pop(0)  # extragem primul nod din open
        closed.append(nod_curent)

        if nod_curent.test_scop() == True:  # daca nodul curent indeplineste conditia scop
            gasit = True
            break

        succesori = nod_curent.expandeaza()  # pentru fiecare succesor din lista succesorilor

        for (s, cost) in succesori:  # parcurgem succesorii
            nod_nou = None
            if nod_curent.contine_in_drum(s) == False:  # daca s nu apartine drumului lui nod_curent
                g_s = nod_curent.g + cost  # costul pana la nodul curent + costul noii muchii
                f_s = g_s + s.h

                nod_pas_anterior_open = in_lista(open , s)   #determinam nodul s daca era deja in open din pasii anteriori
                if nod_pas_anterior_open is not None:        #daca e in open
                    if f_s < nod_pas_anterior_open.f:
                        open.remove(nod_pas_anterior_open)
                        nod_nou = NodParcurgere(s , nod_curent , g_s , f_s)

                else: #daca nu e in open, verific daca el e in closed
                    nod_pas_anterior_closed = in_lista(closed , s)

                    if nod_pas_anterior_closed is not None:
                        if f_s < nod_pas_anterior_closed.f:
                            closed.remove(nod_pas_anterior_closed)
                            nod_nou = NodParcurgere(s , nod_curent , g_s , f_s)


                    else: #nu e nici in open, nici in closed
                        nod_nou = NodParcurgere(s , nod_curent , g_s)

            if nod_nou is not None: #pun nod nou in open astfel incat lista sa ramana sortata
                        #sortam crescator dupa f, descrescator dupa g
                index = 0
                while index < len(open):
                    if open[index].f < nod_nou.f or (open[index].f == nod_nou.f and open[index].g > nod_nou.g):
                        index += 1
                    else:
                        break

                open.insert(index , nod_nou)



    print("\n------------------ Concluzie -----------------------")
    if(len(open) == 0) and not gasit:
        print("Lista open e vida, nu avem drum de la nodul start la nodul scop")
    else:
        print("Nr. iteratii while: " + str(pas))
        print("Distanta: " + str(nod_curent.f))
        print("Drum de cost minim: \n" + afisare_simpla(nod_curent.drum_arbore()))





if __name__ == "__main__":
    problema = Problema()
    NodParcurgere.problema = problema
    a_star()
    print("--- %s seconds ---" % (time.time() - start_time))
