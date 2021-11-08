'''
    Grupa 244, Cozma Laura-Elena
'''

from copy import deepcopy
import time

fisiere_input = ["input_1.txt", "input_2.txt", "input_3.txt", "input_4.txt"]
fisiere_output = ["output_1.txt", "output_2.txt", "output_3.txt", "output_4.txt"]


class Nod:

    def __init__(self, info, h = None):
        self.info = info
        if h is not None:
            self.h = h
        else:                                       #se aplica una din cele 3 euristici
            if EURISTICA == 1:
                self.h = self.euristica1()
            elif EURISTICA == 2:
                self.h = self.euristica2()
            elif EURISTICA == 3:
                self.h = self.euristica_rea()

    def __str__ (self):
        """
        Afisare particularizata a unui obiect de tip nod, conform enuntului
        :return: un sir de caractere cu self.info sub acest format
        """
        sir = '['
        for elem in self.info:
            sir += 'inc('
            if elem == 0:
                sir += 'd,'
            else:
                sir += 'i,'
            sir += str(elem) + '),'
        sir = sir[:-1] + ']'         #pentru a elimina ultima virgula care se pune in final
        return sir

    def __repr__ (self):
        return f"({self.info}, h={self.h})"


    def euristica1(self):
        """
        Prima euristica. Am ales maximul din info, adica care este cea mai inchisa incuietoare. O cheie poate deschide
        o incuietoare maxim o data. Daca am avea un lacat de tipul ddd...ddd, care este cazul cel mai favorabil, atunci
        ar fi necesar max(self.info) pasi pentru a deschide lacatul, deci euristica nu supraestimeaza => este admisibila
        """
        return max(self.info)
    def euristica2(self):
        """
        Similar euristicii 1. Cum am aratat ca euristica 1 este admisibila, max(self.info) - min(self.info) este
        mai mica decat max(self.info), deoarece min(self.info) >= 0. Deci nu va supraestima
        """
        return max(self.info) - min(self.info)
    def euristica_rea(self):
        """
        Nu este o euristica admisibila. Suma va depasi numarul de pasi in unele cazuri, deoarece cu o cheie se pot
        deschide mai multe incuietori in acelasi timp, nu numai una. Ne va da un numar mult mai mare de pasi decat
        cei necesari.
        ex. Pe lacatul i1i1i1i1 si cu cheia dddd, euristica va da 4, insa e necesar un pas ca sa se deschida, deci
        supraestimeaza
        ex. Pe lacatul i1i2i1 si cu cheia ddd, euristica va da 4, dar sunt necesari 2 pasi.
        """
        return sum(self.info)


class Problema:
    def __init__(self, start, chei):
        self.nod_start = Nod(start)
        self.nr_incuietori = len(start)
        self.nod_scop = []
        for i in range(self.nr_incuietori):
            self.nod_scop.append(0)     #configuratia finala este formata numai din incuietori deschise
        self.chei = chei
        self.nr_chei = len(chei)





""" Clase folosite in algoritmul A* """

class NodParcurgere:
    """O clasa care cuprinde informatiile asociate unui nod din listele open/closed
        Cuprinde o referinta catre nodul in sine (din graf)
        dar are ca proprietati si valorile specifice algoritmului A* (f si g).
        Se presupune ca h este proprietate a nodului din graf
    """

    problema = None		# atribut al clasei (se suprascrie jos in __main__)


    def __init__(self, nod_graf, cheie = None, parinte=None, g=0, f=None):
        self.nod_graf = nod_graf	# obiect de tip Nod
        self.cheie = cheie          # indexul cheii folosite pentru formarea noii configuratii din parinte
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
            if nod.info == nod_curent.nod_graf.info:  # daca e nodul cautat ne oprim si returnam True
                return True
            nod_curent = nod_curent.parinte
        return False

    def expandeaza(self):
        """Pentru nodul curent (self) parinte, gasim toti succesorii (fiii)
        si returnam o lista de tupluri (nod_fiu, cost_muchie_tata_fiu),
        sau lista vida, daca nu exista niciunul.
        (Fiecare tuplu contine un obiect de tip Nod si un numar.)
        """
        succesori = []

        for i in range(self.problema.nr_chei):                          #luam fiecare cheie
            config_noua = deepcopy(self.nod_graf.info)                  #pentru fiecare cheie copiem configuratia curenta a lacatului

            for j in range(self.problema.nr_incuietori):                #schimbam fiecare incuietoare conform cheii
                if config_noua[j] + self.problema.chei[i][j] < 0:       #daca un lacat e deschis si il deschidem iar, ramane la fel
                    config_noua[j] = 0
                else:
                    config_noua[j] += self.problema.chei[i][j]          #cum deschis = -1, inchis = 1 si gol = 0, e suficient
                                                                        #sa adunam valorile configuratiei cu cheia pentru a avea noua configuratie

            succesori.append((Nod(config_noua), 1, i))                  #adaugam si indicele cheii
        return succesori


    def test_scop(self):
        """
        Verifica daca am ajuns la final; compara configuratia curenta cu cea finala, adica dddd...
        """
        return self.nod_graf.info == self.problema.nod_scop


    def __str__ (self):
        """
        Afisare particularizata pentru obiect de tip NodParcurgere
        """
        sir = ''
        sir += 'Incuietori: ' + str(self.parinte.nod_graf) + "\n\n"
        sir += 'Folosim cheia: ' + transformare_inversa_cheie(self.problema.chei[self.cheie]) + ' pentru a ajunge la ' + str(self.nod_graf) + '\n\n'
        return sir



""" Algoritmul A* """

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

        for (s, cost, index_cheie) in succesori:  # parcurgem succesorii
            nod_nou = None
            if nod_curent.contine_in_drum(s) == False:  # daca s nu apartine drumului lui nod_curent
                g_s = nod_curent.g + cost  # costul pana la nodul curent + costul noii muchii
                f_s = g_s + s.h

                nod_pas_anterior_open = in_lista(open, s)   #determinam nodul s daca era deja in open din pasii anteriori
                if nod_pas_anterior_open is not None:        #daca e in open
                    if f_s < nod_pas_anterior_open.f:

                        open.remove(nod_pas_anterior_open)
                        nod_nou = NodParcurgere(s, index_cheie, nod_curent, g_s, f_s)

                else: #daca nu e in open, verific daca el e in closed
                    nod_pas_anterior_closed = in_lista(closed, s)

                    if nod_pas_anterior_closed is not None:
                        if f_s < nod_pas_anterior_closed.f:
                            closed.remove(nod_pas_anterior_closed)
                            nod_nou = NodParcurgere(s, index_cheie, nod_curent, g_s, f_s)


                    else: #nu e nici in open, nici in closed
                        nod_nou = NodParcurgere(s, index_cheie, nod_curent , g_s)

            if nod_nou is not None: #pun nod nou in open astfel incat lista sa ramana sortata
                        #sortam crescator dupa f, descrescator dupa g
                index = 0
                while index < len(open):
                    if open[index].f < nod_nou.f or (open[index].f == nod_nou.f and open[index].g > nod_nou.g):
                        index += 1
                    else:
                        break

                open.insert(index , nod_nou)

    sir = ''
    if(len(open )==0) and not gasit:
        sir += "Lacatul nu se poate deschide cu ajutorul cheilor primite."
    else:
        sir += afisare_simpla(nod_curent.drum_arbore()) + "\n"
        sir += "S-au realizat " + str(nod_curent.f) + " operatii."

    return sir


def afisare_simpla(L):
    """
    Folosita in afisarea drumului
    """
    nr_linie = 1
    nr = len(L)
    sir = 'Initial: ' + str(L[0].nod_graf) + '\n\n'
    for i in range(1, nr):                          #cate un element de pe drumul gasit
        sir += str(nr_linie) + ') ' + str(L[i])     #afisam nr liniei impreuna cu informatia de pe drum
        nr_linie += 1

    sir += 'Incuietori(stare scop): ' + str(L[nr - 1].nod_graf) + '\n'

    return sir


def in_lista(l, nod):
    """
    Cautam un nod in lista
    lista "l" contine obiecte de tip NodParcurgere
    "nod" este de tip Nod
    """
    for i in range(len(l)):
        if l[i].nod_graf.info == nod.info:
            return l[i]
    return None


def citire(file_name):
    """
    Functie care citeste continutul lui nume_fisier si il returneaza sub forma unei liste
    :param file_name: numele fisierului ce urmeaza sa fie citit
    :return: configuratia initiala a lacatului si o lista continand cheile din fisier
    """
    chei = []
    lacat = []
    file = open(file_name, "r")

    l_file = file.readline()        #citim configuratia lacatului
    l_file = l_file.split()         #separam in functie de spatii si determinam fiecare incuietoare de cate ori e inchisa
    for i in range(len(l_file)):
        if len(l_file[i]) == 1:
            lacat.append(0)
        elif len(l_file[i]) == 2:
            aux = l_file[i][1:]
            lacat.append(int(aux))

    for line in file:
        line = line.rstrip("\n")    #in momentul in care citim liniile, vor avea \n in coada. Vrem sa il eliminam
        chei.append(transformare_cheie(line))

    file.close()
    return lacat, chei

def transformare_cheie(cheie):
    """
    Dintr-un string de tipul 'iddgd', este transformata intr-o lista, i fiind inlocuit cu 1, d cu -1 si gol cu 0
    Vom reprezenta cheile ca o lista de int-uri. Nu este necesara pastrarea drept tupluri de tipul (i,2), (i,1), (d,0),
    intrucat prima litera este redundanta.
    :param cheie: cheia ce urmeaza sa fie transformata
    :return: lista de cifre, cheia transformata
    """
    nou_format_cheie = []
    for c in cheie:
        if c == 'g':
            nou_format_cheie.append(0)
        elif c == 'i':
            nou_format_cheie.append(1)
        elif c == 'd':
            nou_format_cheie.append(-1)

    return nou_format_cheie

def transformare_inversa_cheie(cheie):
    """
    Transforma lista de cifre cheie intr-o cheie din formatul dat in enunt
    :param cheie: lista, continand cifre
    :return: o cheie din literele i, d, g
    """
    nou_format_cheie = '['
    for i in range(len(cheie)):
        if cheie[i] == 0:
            nou_format_cheie += 'g,'
        elif cheie[i] == 1:
            nou_format_cheie += 'i,'
        else:
            nou_format_cheie += 'd,'
    nou_format_cheie = nou_format_cheie[:-1] + ']'
    return nou_format_cheie

if __name__ == "__main__":

    '''
    input_1.txt
    Contine un lacat cu toate incuietorile inchise o data. In momentul aplicarii fiecarei chei, prima si ultima incuietoare se pot deschide, dar cel din mijloc nu. 
    Astfel, se va ajunge la configuratia d i1 d, care va fi repetata, algoritmul A star se va opri si va afisa ca nu s-a gasit solutie.
    
    input_2.txt
    Contine un input care e deja solutie, adica un lacat deschis. El este egal cu configuratia scop, deci se va opri.
    
    input_3.txt
    Inputul are un drum de cost minim de lungime 5. Euristica inadmisibila gaseste unul de lungime 6.
    
    input_4.txt
    Inputul are un drum de cost minim de lungime 10. Euristica inadmisibila gaseste unul de lungime 11.
     
    '''
    for i in range(0,4): #parcurgem fisierele
        file = open(fisiere_output[i], "w+")
        for j in range(1, 4):           #parcurgem euristicile
            file.write("Euristica " + str(j) + "\n\n")
            EURISTICA = j
            timpul_de_inceput = time.time()             #luam timpul de inceput pentru aceasta euristica
            lacat, chei = citire(fisiere_input[i])      #extragem lacatul si cheile din fisierul de intrare
            problema = Problema(lacat, chei)
            NodParcurgere.problema = problema
            sir = a_star()
            file.write(sir + "\n")
            file.write("--- Timpul total de rulare este de %s secunde ---" % (time.time() - timpul_de_inceput))
            file.write("\n\n\n")
        file.close()