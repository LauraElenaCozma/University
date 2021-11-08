import time
import copy

def elem_identice(lista):
    """ Primeste o lista si returneaza
    -> simbolul jucatorului castigator (daca lista contine doar acel simbol repetat)
    -> sau False (daca a fost remiza sau daca nu s-a terminat jocul)
    """
    mt = set(lista)  # transforma in set pentru a elimina duplicatele
    if len(mt) == 1:  # lungimea e 1 adica toate simbolurile erau la fel
        castigator = list(mt)[0]
        if castigator != Joc.GOL:
            return castigator
        else:
            return False
    else:
        return False

def linie_deschisa(lista, jucator):
    """
    Primeste o lista de NR_CONNECT elemente si verifica daca mai poate fi completata
    """
    # obtin multimea simbolurilor de pe linie
    mt = set(lista)
    # verific daca sunt maxim 2 simboluri
    if len(mt) <= 2:
        # daca multimea simbolurilor nu are alte simboluri decat pentru cel de "gol" si jucatorul curent
        if mt <= {Joc.GOL, jucator}:  # incluziune de seturi
            # inseamna ca linia este deschisa
            return 1
        else:
            return 0
    else:
        return 0


class Joc:
    """
    Clasa care defineste jocul. Se va schimba de la un joc la altul.
    """
    NR_COLOANE = 7
    NR_LINII = 6
    NR_CONNECT = 4  # cu cate simboluri adiacente se castiga
    SIMBOLURI_JUC = ['X', '0']  # ['G', 'R'] sau ['X', '0']
    JMIN = None  # 'R'
    JMAX = None  # 'G'
    GOL = '.'
    def __init__(self, tabla=None):
        self.matr = tabla or [Joc.GOL]*(Joc.NR_COLOANE * Joc.NR_LINII)


    def final(self):
        # returnam simbolul jucatorului castigator daca are 4 piese adiacente
        #	pe linie, coloana, diagonala \ sau diagonala /
        # sau returnam 'remiza'
        # sau 'False' daca nu s-a terminat jocul
        rez = False

        # verificam linii

        linii = self.NR_LINII - self.NR_CONNECT + 1
        coloane = self.NR_COLOANE - self.NR_CONNECT + 1
        for linie in range(self.NR_LINII):
            for coloana in range(coloane):
                idx_inc = coloana + linie * self.NR_COLOANE
                idx_fin = idx_inc + self.NR_CONNECT
                res = elem_identice(self.matr[idx_inc:idx_fin])
                if res != False:
                    return res

        # verificam coloane
        for linie in range(linii):
            for coloana in range(self.NR_COLOANE):
                idx_inc = coloana + linie * self.NR_COLOANE
                idx_fin = idx_inc + self.NR_CONNECT * self.NR_COLOANE
                res = elem_identice(self.matr[idx_inc:idx_fin:self.NR_COLOANE])
                if res != False:
                    return res

        # verificam diagonale \
        for linie in range(linii):
            for coloana in range(coloane):
                idx_inc = coloana + linie * self.NR_COLOANE
                salt = self.NR_COLOANE + 1
                idx_fin = idx_inc + self.NR_CONNECT * salt
                res = elem_identice(self.matr[idx_inc:idx_fin:salt])
                if res != False:
                    return res

        # verificam diagonale /
        for linie in range(linii):
            for coloana in range(self.NR_CONNECT - 1, self.NR_COLOANE):
                idx_inc = coloana + linie * self.NR_COLOANE
                salt = self.NR_COLOANE - 1
                idx_fin = idx_inc + self.NR_CONNECT * salt
                res = elem_identice(self.matr[idx_inc:idx_fin:salt])
                if res != False:
                    return res

        if rez==False  and  Joc.GOL not in self.matr:
            return 'remiza'
        else:
            return False


    def mutari_joc(self, jucator_opus):
        l_mutari=[]
        # matr_tabla_noua = list(self.matr)

        for coloana in range(self.NR_COLOANE):
            for linie in range(self.NR_LINII -1, -1, -1):
                poz = coloana + linie * self.NR_COLOANE
                if self.matr[poz] == self.GOL:
                    matr_tabla_noua = copy.deepcopy(self.matr)  #copiem tabla de joc in config_noua
                    matr_tabla_noua[poz] = jucator_opus       #adaugam simbolul corespunzator jocatorului curent pe pozitia libera gasita
                    l_mutari.append(Joc(matr_tabla_noua))
                    break

        return l_mutari


    def nr_intervale_deschise(self, jucator):
        # un interval de 4 pozitii adiacente (pe linie, coloana, diag \ sau diag /)
        # este deschis pt "jucator" daca nu contine "juc_opus"

        juc_opus = Joc.JMIN if jucator == Joc.JMAX else Joc.JMAX
        rez = 0
        linii = self.NR_LINII - self.NR_CONNECT + 1
        coloane = self.NR_COLOANE - self.NR_CONNECT + 1
        for linie in range(self.NR_LINII):
            for coloana in range(coloane):
                idx_inc = coloana + linie * self.NR_COLOANE
                idx_fin = idx_inc + self.NR_CONNECT
                rez += linie_deschisa(self.matr[idx_inc:idx_fin], jucator)



        # verificam coloane
        for linie in range(linii):
            for coloana in range(self.NR_COLOANE):
                idx_inc = coloana + linie * self.NR_COLOANE
                idx_fin = idx_inc + self.NR_CONNECT * self.NR_COLOANE
                rez += linie_deschisa(self.matr[idx_inc:idx_fin:self.NR_COLOANE], jucator)


        # verificam diagonale \
        for linie in range(linii):
            for coloana in range(coloane):
                idx_inc = coloana + linie * self.NR_COLOANE
                salt = self.NR_COLOANE + 1
                idx_fin = idx_inc + self.NR_CONNECT * salt
                rez += linie_deschisa(self.matr[idx_inc:idx_fin:salt], jucator)

        # verificam diagonale /
        for linie in range(linii):
            for coloana in range(self.NR_CONNECT - 1, self.NR_COLOANE):
                idx_inc = coloana + linie * self.NR_COLOANE
                salt = self.NR_COLOANE - 1
                idx_fin = idx_inc + self.NR_CONNECT * salt
                rez += linie_deschisa(self.matr[idx_inc:idx_fin:salt], jucator)

        return rez


    def fct_euristica(self):
        # alte variante de euristici? .....
        '''
        putem tine cont daca o linie deschisa are 3 elemente de acelasi tip si un '.', 2 de acelasi tip si 2 '.', unul de acelasi tip si 3 '.', numai puncte
        astfel cand numaram intevalele deschise putem sa setam prioritati(scoruri diferite)
        daca sunt 3 casute ocupate cu simbolul curent e mult mai favorabil sa punem acolo decat daca era o linie cu 2 simboluri curente
        in loc sa adunam 1 la fiecare, putem adauga 3 la cea cu 3 casute ocupate, 2 la cea cu 2 etc.
        '''
        # intervale_deschisa(juc) = cate intervale de 4 pozitii
        # (pe linii, coloane, diagonale) nu contin juc_opus
        return self.nr_intervale_deschise(Joc.JMAX) - self.nr_intervale_deschise(Joc.JMIN)



    def estimeaza_scor(self, adancime):
        t_final = self.final()
        if t_final == Joc.JMAX :
            return (999+adancime)
        elif t_final == Joc.JMIN:
            return (-999-adancime)
        elif t_final == 'remiza':
            return 0
        else:
            return self.fct_euristica()


    def __str__(self):
        sir = ''
        for nr_col in range(self.NR_COLOANE):
            sir += str(nr_col) + ' '
        sir += '\n'

        for lin in range(self.NR_LINII):
            k = lin * self.NR_COLOANE
            sir += (" ".join([str(x) for x in self.matr[k : k+self.NR_COLOANE]])+"\n")
        return sir


class Stare:
    """
    Clasa folosita de algoritmii minimax si alpha-beta
    Are ca proprietate tabla de joc
    Functioneaza cu conditia ca in cadrul clasei Joc sa fie definiti JMIN si JMAX (cei doi jucatori posibili)
    De asemenea cere ca in clasa Joc sa fie definita si o metoda numita mutari_joc() care ofera lista cu
    configuratiile posibile in urma mutarii unui jucator
    """

    ADANCIME_MAX = None

    def __init__(self, tabla_joc, j_curent, adancime, parinte=None, scor=None):
        self.tabla_joc = tabla_joc
        self.j_curent = j_curent

        #adancimea in arborele de stari
        self.adancime=adancime

        #scorul starii (daca e finala) sau al celei mai bune stari-fiice (pentru jucatorul curent)
        self.scor=scor

        #lista de mutari posibile din starea curenta
        self.mutari_posibile=[]

        #cea mai buna mutare din lista de mutari posibile pentru jucatorul curent
        self.stare_aleasa=None

    def jucator_opus(self):
        if self.j_curent==Joc.JMIN:
            return Joc.JMAX
        else:
            return Joc.JMIN

    def mutari_stare(self):
        l_mutari=self.tabla_joc.mutari_joc(self.j_curent)
        juc_opus=self.jucator_opus()
        l_stari_mutari=[Stare(mutare, juc_opus, self.adancime-1, parinte=self) for mutare in l_mutari]

        return l_stari_mutari


    def __str__(self):
        sir= str(self.tabla_joc) + "(Juc curent: "+self.j_curent+")\n"
        return sir



""" Algoritmul MinMax """

def min_max(stare):

    if stare.adancime==0 or stare.tabla_joc.final() :
        stare.scor=stare.tabla_joc.estimeaza_scor(stare.adancime)
        return stare

    #calculez toate mutarile posibile din starea curenta
    stare.mutari_posibile=stare.mutari_stare()

    #aplic algoritmul minimax pe toate mutarile posibile (calculand astfel subarborii lor)
    mutari_scor=[min_max(mutare) for mutare in stare.mutari_posibile]

    if stare.j_curent==Joc.JMAX :
        #daca jucatorul e JMAX aleg starea-fiica cu scorul maxim
        stare.stare_aleasa = max(mutari_scor, key=lambda x: x.scor)
    else:
        #daca jucatorul e JMIN aleg starea-fiica cu scorul minim
        stare.stare_aleasa = min(mutari_scor, key=lambda x: x.scor)

    stare.scor=stare.stare_aleasa.scor
    return stare



def alpha_beta(alpha, beta, stare):
    if stare.adancime==0 or stare.tabla_joc.final() :
        stare.scor = stare.tabla_joc.estimeaza_scor(stare.adancime)
        return stare

    if alpha >= beta:
        return stare #este intr-un interval invalid deci nu o mai procesez

    stare.mutari_posibile = stare.mutari_stare()

    if stare.j_curent == Joc.JMAX :
        scor_curent = float('-inf')

        for mutare in stare.mutari_posibile:
            #calculeaza scorul
            stare_noua = alpha_beta(alpha, beta, mutare)

            if (scor_curent < stare_noua.scor):
                stare.stare_aleasa = stare_noua
                scor_curent = stare_noua.scor
            if(alpha < stare_noua.scor):
                alpha = stare_noua.scor
                if alpha >= beta:
                    break

    elif stare.j_curent == Joc.JMIN :
        scor_curent = float('inf')

        for mutare in stare.mutari_posibile:
            stare_noua = alpha_beta(alpha, beta, mutare)

            if (scor_curent > stare_noua.scor):
                stare.stare_aleasa = stare_noua
                scor_curent = stare_noua.scor

            if(beta > stare_noua.scor):
                beta = stare_noua.scor
                if alpha >= beta:
                    break

    stare.scor = stare.stare_aleasa.scor

    return stare



def afis_daca_final(stare_curenta, pozitie):
    """
    verifica doar linia, coloana, 2 diagonale pt elementul nou, de pe "pozitie"
    Distingem 4 cazuri: elementul incheie o linie, coloana, \ sau /(primul for i)
    Pentru fiecare caz il consideram pe elementul de pe pozitie ca fiind primul, al doilea etc element din sirul de 4
    Dupa ce am stabilit care e pozitia primului element din sirul de 4(for j), iteram prin sirul de 4(for k) si verificam daca are elemente identice
    """

    lin = pozitie // Joc.NR_COLOANE             #calculam linia corespunzatoare pozitiei in matrice
    col = pozitie - lin * Joc.NR_COLOANE        #calculam coloana corespunzatoare pozitiei in matrice
    #transformam lista intr-o lista de liste ca sa fie mai usoara procesarea
    mat = [[stare_curenta.tabla_joc.matr[i * Joc.NR_COLOANE + j] for j in range(Joc.NR_COLOANE)] for i in range(Joc.NR_LINII)]

    #V, S, NV, SV
    dir_lin = [0, -1, -1, 1]
    dir_col = [-1, 0, -1, -1]

    for i in range(len(dir_lin)):
        for j in range(4):
            #il consideram pe mat[lin][col] primul, al doilea, al 3-lea si al 4-lea element dintr-un sir de 4, pe rand
            new_lin = lin + j * dir_lin[i]
            new_col = col + j * dir_col[i]
            valid = True
            #parcurgem si restul elementelor din sirul de 4; mergem inainte; adica daca suntem pe directia vest, inainte inseamna spre est
            for k in range(4):
                if new_lin >= 0 and new_lin < Joc.NR_LINII and new_col >= 0 and new_col < Joc.NR_COLOANE: #daca linia si coloana nou calculate sunt in interior
                    if mat[lin][col] != mat[new_lin][new_col]: #sa aiba toate elem aceeasi culoare
                        valid = False
                        break
                    else:
                        #mergem in directia opusa fata de directia pe care am pornit
                        new_lin -= dir_lin[i]
                        new_col -= dir_col[i]
                else:
                    valid = False
                    break

            if valid:
                print("A castigat " + mat[lin][col])
                return True
            elif Joc.GOL in mat:
                print("Remiza")
                return True
            else:
                return False


def afis_daca_final_toata_matricea(stare_curenta):
    '''
    Afiseaza starea jocului daca e in stare finala sau false altfel. Folosita in partea de jmax, pentru a nu fi nevoiti sa gasim ce pozitie a ales jmax
    '''
    final = stare_curenta.tabla_joc.final()
    if (final):
        if (final == "remiza"):
            print("Remiza!")
        else:
            print("A castigat " + final)

        return True

    return False


def main():
    #initializare algoritm
    raspuns_valid=False
    while not raspuns_valid:
        tip_algoritm=input("Algorimul folosit? (raspundeti cu 1 sau 2)\n 1.Minimax\n 2.Alpha-beta\n ")
        if tip_algoritm in ['1','2']:
            raspuns_valid=True
        else:
            print("Nu ati ales o varianta corecta.")

    # initializare ADANCIME_MAX
    raspuns_valid = False
    while not raspuns_valid:
        n = input("Adancime maxima a arborelui: ")
        if n.isdigit():
            Stare.ADANCIME_MAX = int(n)
            raspuns_valid = True
        else:
            print("Trebuie sa introduceti un numar natural nenul.")


    # initializare jucatori
    [s1, s2] = Joc.SIMBOLURI_JUC.copy()  # lista de simboluri posibile
    raspuns_valid = False
    while not raspuns_valid:
        Joc.JMIN = str(input("Doriti sa jucati cu {} sau cu {}? ".format(s1, s2))).upper()
        if (Joc.JMIN in Joc.SIMBOLURI_JUC):
            raspuns_valid = True
        else:
            print("Raspunsul trebuie sa fie {} sau {}.".format(s1, s2))
    Joc.JMAX = s1 if Joc.JMIN == s2 else s2

    #initializare tabla
    tabla_curenta = Joc()
    print("Tabla initiala")
    print(str(tabla_curenta))

    #creare stare initiala
    stare_curenta = Stare(tabla_curenta, Joc.SIMBOLURI_JUC[0], Stare.ADANCIME_MAX)
    linie = -1
    coloana = -1
    while True :
        if (stare_curenta.j_curent == Joc.JMIN):
            #muta jucatorul
            raspuns_valid=False
            linie = -1
            while not raspuns_valid:
                try:
                    coloana = int(input("coloana = "))
                    # de verificat daca "coloana" este in intervalul corect,
                    # apoi de gasit pe ce "linie" este cea mai de jos
                    # casuta goala de pe acea "coloana"
                    if (coloana < Joc.NR_COLOANE and coloana >= 0):

                        for i in range(Joc.NR_LINII - 1, -1, -1):
                            poz = i * Joc.NR_COLOANE + coloana

                            if stare_curenta.tabla_joc.matr[poz] == Joc.GOL:
                                linie = i
                                raspuns_valid = True
                                break
                        if linie == -1:
                            print("Toata coloana este ocupata.")
                    else:
                        print("Coloana invalida (trebuie sa fie un numar intre 0 si Joc.NR_COLOANE - 1")


                except ValueError:
                    print("Coloana trebuie sa fie un numar intreg.")

            #dupa iesirea din while sigur am valida coloana
            #deci pot plasa simbolul pe "tabla de joc"
            pozitie = linie * Joc.NR_COLOANE + coloana
            stare_curenta.tabla_joc.matr[pozitie] = Joc.JMIN

            #afisarea starii jocului in urma mutarii utilizatorului
            print("\nTabla dupa mutarea jucatorului")
            print(str(stare_curenta))

            #testez daca jocul a ajuns intr-o stare finala
            #si afisez un mesaj corespunzator in caz ca da
            if (afis_daca_final(stare_curenta, pozitie)):
                break


            #S-a realizat o mutare. Schimb jucatorul cu cel opus
            stare_curenta.j_curent = stare_curenta.jucator_opus()

        #--------------------------------
        else: #jucatorul e JMAX (calculatorul)
        #Mutare calculator
            #preiau timpul in milisecunde de dinainte de mutare
            t_inainte=int(round(time.time() * 1000))
            if tip_algoritm=='1':
                stare_actualizata = min_max(stare_curenta)
            else: #tip_algoritm==2
                stare_actualizata = alpha_beta(-5000, 5000, stare_curenta)
            stare_curenta.tabla_joc = stare_actualizata.stare_aleasa.tabla_joc
            print("Tabla dupa mutarea calculatorului")
            print(str(stare_curenta))

            #preiau timpul in milisecunde de dupa mutare
            t_dupa=int(round(time.time() * 1000))
            print("Calculatorul a \"gandit\" timp de "+str(t_dupa-t_inainte)+" milisecunde.")

            if (afis_daca_final_toata_matricea(stare_curenta)):
                break

            #S-a realizat o mutare. Schimb jucatorul cu cel opus
            stare_curenta.j_curent = stare_curenta.jucator_opus()


if __name__ == "__main__" :
        main()