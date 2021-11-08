import copy
import time
start_time = time.time()

euristica = 1
'''
    am modificat fata de prima varianta afisarea, am facut functii pentru euristici si cateva detalii mici in cod
'''
""" definirea problemei """
class Nod:
    def __init__(self, info, h):
        self.info = info    #o lista de liste
        self.h = h

    def __str__ (self):
        return "({}, h={})".format(self.info, self.h)
    def __repr__ (self):
        return f"({self.info}, h={self.h})"


class Problema:
    def __init__(self, start = [['a'], ['d', 'b'], ['c']], scop = [['b', 'c'], [], ['d', 'a']]):
        self.nod_start = Nod(start, float("inf"))
        self.nod_scop = scop
        self.nr_stive = len(start)  # N=3 in enunt
        self.nr_cuburi = sum([len(stiva) for stiva in start])  # M=4 in enunt




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

    def euristica_1(self, info):
        # euristica: nr de cuburi care difera fata de configuratia finala           142 iteratii while; 0.018 secunde
        # aproximeaza mai bine pe h decat varianta cu nr de stive
        h = 0  # deoarece daca o stiva e acum 2 1 3 si trebuie sa fie 1 3 2 aceasta face h+=3 pe cand varianta cu stivele +=1
        nod_scop = self.problema.nod_scop  # aproximeaza mai bine numarul de cuburi care urmeaza sa fie schimbate, iar la fiecare pas schimbam un cub
        for stiva_i in range(self.problema.nr_stive):  # 11 pasi pentru exemplu
            for poz in range(min(len(info[stiva_i]), len(nod_scop[stiva_i]))):  # mergem pana la inaltimea minima
                if info[stiva_i][poz] != nod_scop[stiva_i][poz]:  # time = 0.006
                    h += 1
        return h


    def euristica_2(self, info):
        h = 0
        nod_scop = self.problema.nod_scop  # euristica: nr de stive diferite
        for stiva_i in range(self.problema.nr_stive):  # 212 pasi pe exemplu
            if len(nod_scop[stiva_i]) != len(info[stiva_i]):  # 0.033 mai incet decat euristica cu numar cuburi diferite
                h += 1  # aproximeaza mai prost, deoarece nu anticipeaza bine cate cuburi mai trebuie mutate
            else:
                for poz in range(len(info[stiva_i])):  # mergem pana la inaltimea minima
                    if info[stiva_i][poz] != nod_scop[stiva_i][poz]:
                        h += 1
                        break

        h = int(h / 2)  # euristica e nr. stive gresite / 2
        return h

    def drum_arbore(self):
        """
            Functie care calculeaza drumul asociat unui nod din arborele de cautare.
            Functia merge din parinte in parinte pana ajunge la radacina
        """
        nod_c = self
        drum = [nod_c]
        while nod_c.parinte is not None :
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

        for stiva in range(self.problema.nr_stive):  # parcurgem toate stivele

            configuratie = copy.deepcopy(self.nod_graf.info)
            if len(configuratie[stiva]) != 0:                      # daca stiva curenta e nevida
                vf = configuratie[stiva].pop()                     # luam elementul din varful stivei
                for poz in range(self.problema.nr_stive):          # parcurgem din nou toate stivele si adaugam elementul extras la toate celelalte
                    if poz != stiva:                               # nu trebuie sa adaugam in aceeasi stiva
                        nou_succesor = copy.deepcopy(configuratie)
                        nou_succesor[poz].append(vf)
                        if euristica == 1:
                            h_succesor = self.euristica_1(nou_succesor)
                            succesori.append((Nod(nou_succesor, h_succesor), 1))   # am stabilit ca g = 1
                        else:
                            h_succesor = self.euristica_2(nou_succesor)
                            succesori.append((Nod(nou_succesor, h_succesor), 1))  # am stabilit ca g = 1


        return succesori


    # se modifica in functie de problema
    def test_scop(self):
        return self.nod_graf.info == self.problema.nod_scop


    def __str__ (self):
        parinte = self.parinte if self.parinte is None else self.parinte.nod_graf.info
        return f"({self.nod_graf}, parinte={parinte}, f={self.f}, g={self.g})"



""" Algoritmul A* """


def str_info_noduri(l):
    """
        o functie folosita strict in afisari - poate fi modificata in functie de problema
    """
    sir = "["
    for x in l:
        sir += str(x) +"  "
    sir += "]"
    return sir


def afisare_simpla(L):
    '''
    afisare particularizata pentru problema blocurilor
    '''

    sir = "\n"
    for Li in L:        #cate un element de pe drumul gasit
        config = Li.nod_graf.info
        sir += afisare(config) + "\n"
    return sir

def afisare(config):
    sir = ""
    for linii in config:
        for elem in linii:
            sir += str(elem) + " "
        if not len(linii):
            sir += "|"
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
    if(len(open )==0) and not gasit:
        print("Lista open e vida, nu avem drum de la nodul start la nodul scop")
    else:
        print("Nr iteratii while: " + str(pas))
        print("Distanta: " + str(nod_curent.f))
        print("Drum de cost minim: " + afisare_simpla(nod_curent.drum_arbore()))





if __name__ == "__main__":
    problema = Problema()
    NodParcurgere.problema = problema
    a_star()
    print("--- %s seconds ---" % (time.time() - start_time))