import copy
import time
start_time = time.time()
""" definirea problemei """
class Nod:
    def __init__(self, info, h = None):
        self.info = info    #o lista de liste
        if h is not None:
            self.h = h
        else:
            self.h = (self.info[2] + self.info[3]) // (problema.M - 1)   #nr de oameni de pe malul de plecare / (numarul de oameni din barca - 1)

    def __str__ (self):
        return "({}, h={})".format(self.info, self.h)
    def __repr__ (self):
        return f"({self.info}, h={self.h})"


class Problema:
    def __init__(self, N = 3, M = 2, mal = "est"):
        self.N = N # nr canibali = nr misionari = 3
        self.M = M # nr locuri in barca = 2
        nod_E = [0, 0, self.N, self.N, "est"]            #(nr_can_vest, nr_mis_vest, nr_can_est, nr_mis_est, mal_unde_e_barca)
        nod_V = [self.N, self.N, 0, 0, "vest"]

        start = nod_E if mal == "est" else nod_V
        scop = nod_V if mal == "est" else nod_E

        self.nod_start = Nod(start, float("inf"))
        self.nod_scop = scop

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

        if self.nod_graf.info[4] == "est":
            nr_mis = self.nod_graf.info[3]
            nr_can = self.nod_graf.info[2]
        else:
            nr_mis = self.nod_graf.info[1]
            nr_can = self.nod_graf.info[0]
        for mis in range(nr_mis + 1):              # cati misionari si cati canibali luam in barca
            for can in range(nr_can + 1):
                if 0 < (mis + can) and (mis + can) <= problema.M:   #nu are voie sa mearga goala sau sa depaseasca nr

                    if can > mis and mis != 0:     #conditii validare barca; nu trebuie sa fie mai multi canibali decat misionari in barca
                        continue
                    if (nr_can - can) > (nr_mis - mis) and (nr_mis - mis) != 0:            #conditii validare mal curent

                        continue
                    N = problema.N
                    if (N - nr_can + can) > (N - nr_mis + mis) and (N -nr_mis + mis) != 0:  #conditii validare mal opus
                        continue
                    n_succ = copy.deepcopy(self.nod_graf.info)
                    if n_succ[4] == "est":
                        n_succ[0] += can
                        n_succ[1] += mis
                        n_succ[2] -= can
                        n_succ[3] -= mis
                        n_succ[4] = "vest"
                    elif n_succ[4] == "vest":
                        n_succ[0] -= can
                        n_succ[1] -= mis
                        n_succ[2] += can
                        n_succ[3] += mis
                        n_succ[4] = "est"

                    succesori.append((Nod(n_succ), 1))
        return succesori


    # se modifica in functie de problema
    def test_scop(self):
        return self.nod_graf.info == self.problema.nod_scop


    def __str__ (self):
        parinte = self.parinte if self.parinte is None else self.parinte.nod_graf.info
        return f"({self.nod_graf}, parinte={parinte}, f={self.f}, g={self.g})"



""" Algoritmul A* """

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
    sir = "Pe malul de est sunt " + str(config[3]) + " misionari si " + str(config[2]) + " canibali.\n"
    sir += "Pe malul de vest sunt " + str(config[1]) + " misionari si " + str(config[0]) + " canibali.\n"
    sir += "Barca se afla pe malul de " + config[4] + ".\n"
    return sir

def str_info_noduri(l):
    """
        o functie folosita strict in afisari - poate fi modificata in functie de problema
    """
    sir = "["
    for x in l:
        sir += str(x) +"  "
    sir += "]"
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
    gasit = True
    nod_curent = None

    pas = 0
    while len(open) != 0:  # cat timp open nu e vida repetam
        pas += 1
        nod_curent = open.pop(0)  # extragem primul nod din open
        closed.append(nod_curent)
        if nod_curent.test_scop() == True:  # daca nodul curent indeplineste conditia scop
            gasit = False
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
        print("Pasi: " + str(nod_curent.f))
        print("Drum de cost minim: " + afisare_simpla(nod_curent.drum_arbore()))





if __name__ == "__main__":
    problema = Problema()
    NodParcurgere.problema = problema
    a_star()
    print("--- %s seconds ---" % (time.time() - start_time))