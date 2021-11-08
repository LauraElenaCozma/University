import time
from copy import deepcopy
import string




class Joc:
    """
    Clasa care defineste jocul. Se va schimba de la un joc la altul.
    """
    NR_COLOANE = 8
    NR_LINII = 8
    SIMBOLURI_JUC = ['N', 'A']
    JMIN = None  # 'A'
    JMAX = None  # 'N'
    GOL = '#'
    def __init__(self, tabla=None):
        self.matr = tabla or [[Joc.GOL for j in range(Joc.NR_COLOANE)] for i in range(Joc.NR_LINII)]
        if tabla is None:
            mij_lin = (Joc.NR_LINII - 1) // 2                   #tabla de joc implicita va contine in mijloc simbolurile A si N dispuse in X
            mij_col = (Joc.NR_COLOANE - 1) // 2
            self.matr[mij_lin][mij_col] = 'A'
            self.matr[mij_lin + 1][mij_col + 1] = 'A'
            self.matr[mij_lin + 1][mij_col] = 'N'
            self.matr[mij_lin][mij_col + 1] = 'N'


    def mutari_joc(self, jucator):
        '''
        Returneaza o lista cu toate tablele de joc care s-ar forma dupa selectarea fiecarei pozitii valide
        '''
        l_mutari=[]
        for lin in range(Joc.NR_LINII):
            for col in range(Joc.NR_COLOANE):
                if self.matr[lin][col] == Joc.GOL:
                    directii = self.pozitie_valida(lin, col, jucator)
                    if len(directii) > 0:
                        l_mutari.append(Joc(self.schimba_culoarea(lin, col, jucator, directii)))


        return l_mutari

    def pozitie_valida(self, lin, col, jucator):
        """
        Pentru o pozitie data prin lin si col, verificam daca poate fi considerata o pozitie valida pentru jucator
        """
        pas_lin = [-1, -1, -1, 0, 1, 1, 1, 0]      #pozitiile relative ale vecinilor fara de lin si col
        pas_col = [-1, 0, 1, 1, 1, 0, -1, -1]
        juc_opus = Joc.JMIN if jucator == Joc.JMAX else Joc.JMAX
        directii = []
        for i in range(8):                          #mereu o pozitie va avea 8 vecini <=> cu len(pas_lin) sau pas_col
            #calculam noile pozitii
            idx_lin = lin + pas_lin[i]
            idx_col = col + pas_col[i]
            nr_piese_castigate = 0
            #mergem pe directia respectiva pana am iesit din tabla sau nu mai dam de piesele jucatorului opus
            while (idx_lin >= 0 and idx_col >= 0 and idx_lin < Joc.NR_LINII and idx_col < Joc.NR_COLOANE and self.matr[idx_lin][idx_col] == juc_opus):
                idx_lin += pas_lin[i]
                idx_col += pas_col[i]
                nr_piese_castigate += 1             #numaram daca am trecut daca am trecut peste cel putin o piesa a jucatorului opus

            if nr_piese_castigate > 0 and idx_lin >= 0 and idx_col >= 0 and idx_lin < Joc.NR_LINII and idx_col < Joc.NR_COLOANE:
                #adica daca am facut cel putin un pas peste un jucator opus
                #si pozitia curenta inca este in interior
                if self.matr[idx_lin][idx_col] == jucator:
                    #daca pe pozitia respectiva e jucatorul curent si nu gol
                    directii.append(i)

        return directii

    def schimba_culoarea(self, lin, col, jucator, directii):
        """
                Pentru o pozitie data prin lin si col, schimbam culorile pe drumurile posibile
                Primim un vector de directii ca sa nu cautam iar drumurile bune, stim direct pe care sa schimbam
        """
        mat = deepcopy(self.matr)
        mat[lin][col] = jucator
        pas_lin = [-1, -1, -1, 0, 1, 1, 1, 0]
        pas_col = [-1, 0, 1, 1, 1, 0, -1, -1]
        juc_opus = Joc.JMIN if jucator == Joc.JMAX else Joc.JMAX

        for i in directii:
            idx_lin = lin + pas_lin[i]
            idx_col = col + pas_col[i]

            while (idx_lin >= 0 and idx_col >= 0 and idx_lin < Joc.NR_LINII and idx_col < Joc.NR_COLOANE and mat[idx_lin][idx_col] == juc_opus):
                #schimbam culoarea piesei; am capturat-o
                mat[idx_lin][idx_col] = jucator
                idx_lin += pas_lin[i]
                idx_col += pas_col[i]
            #cum stim ca in directia aceasta ne puteam deplasa, nu e nevoie sa mai intrebam daca am ajuns la jucator; este clar ca am ajuns

        return mat

    def numara_posibile_mutari(self, jucator):
        '''
        Returneaza cate mutari posibile are in tabla curenta jucatorul
        '''
        nr_mutari = 0
        for lin in range(Joc.NR_LINII):
            for col in range(Joc.NR_COLOANE):
                if self.matr[lin][col] == Joc.GOL:
                    if  len(self.pozitie_valida(lin, col, jucator)) > 0: #pozitie valida returneaza un vector cu directii; cel putin o directie => e valida
                        nr_mutari += 1
        return nr_mutari

    def nr_piese_jucator(self, jucator):
        '''
        Returneaza cate piese are jucatorul pe tabla de culoarea sa
        '''
        nr = 0
        for lin in range(Joc.NR_LINII):
            for col in range(Joc.NR_COLOANE):
                if self.matr[lin][col] == jucator:
                    nr += 1
        return nr
    def fct_euristica(self):
        '''
        Functia euristica: numarul pieselor lui max - numarul pieselor lui mic
        '''
        return self.nr_piese_jucator(Joc.JMAX) - self.nr_piese_jucator(Joc.JMIN)

    def final(self):
        '''
        returnam simbolul jucatorului castigator
        sau returnam 'remiza'
        sau 'False' daca nu s-a terminat jocul
        '''
        rez = False
        nr_mutari_max = self.numara_posibile_mutari(self.JMAX)
        nr_mutari_min = self.numara_posibile_mutari(self.JMIN)
        if nr_mutari_max == 0 and nr_mutari_min == 0:  #daca amandoi sunt blocati
            nr_piese_max = self.nr_piese_jucator(Joc.JMAX)
            nr_piese_min = self.nr_piese_jucator(Joc.JMIN)
            if nr_piese_max > nr_piese_min:            #vedem daca a castigat cineva sau a fost remiza
                return Joc.JMAX
            elif nr_piese_min > nr_piese_max:
                return Joc.JMIN
            else:
                return 'remiza'
        else:
            return False


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
        '''
        Returneaza o tabla de joc(tip sir de caractere pentru afisare)
        '''
        sir = '    '
        alphabet_string = string.ascii_lowercase
        alphabet_list = list(alphabet_string)[:self.NR_COLOANE]
        for chr in alphabet_list:
            sir += chr + ' '
        sir += '\n    '
        for chr in alphabet_list:
            sir += '- '
        sir += '\n'
        for lin in range(self.NR_LINII):
            sir += str(lin) + ' | '
            for col in range(self.NR_COLOANE):
                    sir += self.matr[lin][col] + " "
            sir += '\n'

        return sir

    def afisare_pozitii_valide(self, jucator):
        '''
                Returneaza o tabla de joc(tip sir de caractere pentru afisare) cu tot cu pozitiile de pe care se poate initia urmatoarea mutare. Ele sunt marcate cu _
        '''
        sir = '    '
        alphabet_string = string.ascii_lowercase
        alphabet_list = list(alphabet_string)[:self.NR_COLOANE]
        for chr in alphabet_list:
            sir += chr + ' '
        sir += '\n    '
        for chr in alphabet_list:
            sir += '- '
        sir += '\n'
        for lin in range(self.NR_LINII):
            sir += str(lin) + ' | '
            for col in range(self.NR_COLOANE):
                if self.matr[lin][col] == Joc.GOL and self.pozitie_valida(lin, col, jucator):
                    sir += "_ "
                else:
                    sir += self.matr[lin][col] + " "
            sir += '\n'

        return sir


class Stare:
    """
    Clasa folosita de algoritmii minimax si alpha-beta
    Are ca proprietate tabla de joc
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

        self.parinte = parinte

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
        
        #pentru cazul in care vectorul mutari_scor e vid, era o problema deoarece nu putea calcula maximul
        if len(mutari_scor) == 0:
            stare.scor = float('-inf')
            return stare
        
        #daca jucatorul e JMAX aleg starea-fiica cu scorul maxim
        stare.stare_aleasa = max(mutari_scor, key=lambda x: x.scor)
    else:
        
        if len(mutari_scor) == 0:
            stare.scor = float('+inf')
            return stare
        
        #daca jucatorul e JMIN aleg starea-fiica cu scorul minim
        stare.stare_aleasa = min(mutari_scor, key=lambda x: x.scor)

    stare.scor=stare.stare_aleasa.scor
    return stare


"""Algoritmul alpha beta"""

def alpha_beta(alpha, beta, stare):
    if stare.adancime==0 or stare.tabla_joc.final():
        stare.scor = stare.tabla_joc.estimeaza_scor(stare.adancime)
        return stare

    if alpha >= beta:
        return stare #este intr-un interval invalid deci nu o mai procesez

    stare.mutari_posibile = stare.mutari_stare()

    if stare.j_curent == Joc.JMAX:
        #in cazul in care nu mai sunt mutari valide, sa nu se blocheze
        if len(stare.mutari_posibile) == 0:
            stare.scor = float('-inf')
            return stare
        scor_curent = float('-inf')

        for mutare in stare.mutari_posibile:
            #calculeaza scorul
            stare_noua = alpha_beta(alpha, beta, mutare)

            if (scor_curent <= stare_noua.scor):
                stare.stare_aleasa = stare_noua
                scor_curent = stare_noua.scor
            if(alpha < stare_noua.scor):
                alpha = stare_noua.scor
                if alpha >= beta:
                    break

    elif stare.j_curent == Joc.JMIN:
        # in cazul in care nu mai sunt mutari valide, sa nu se blocheze
        if len(stare.mutari_posibile) == 0:
            stare.scor = float('inf')
            return stare

        scor_curent = float('inf')

        for mutare in stare.mutari_posibile:
            stare_noua = alpha_beta(alpha, beta, mutare)

            if (scor_curent >= stare_noua.scor):
                stare.stare_aleasa = stare_noua
                scor_curent = stare_noua.scor

            if(beta > stare_noua.scor):
                beta = stare_noua.scor
                if alpha >= beta:
                    break


    stare.scor = stare.stare_aleasa.scor

    return stare



def afis_daca_final(stare_curenta):
    '''
    Daca am ajuns la finalul jocului, se afiseaza statutul acestuia
    '''
    final = stare_curenta.tabla_joc.final()
    if(final):
        if (final=="remiza"):
            print("Remiza!")
        else:
            print("A castigat "+final)
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

    while True:
        # testez daca jocul a ajuns intr-o stare finala; necesar pentru cazul in care tabla initiala nu are nicio mutare valida
        # si afisez un mesaj corespunzator in caz ca da
        if (afis_daca_final(stare_curenta)):
            break
        if (stare_curenta.j_curent == Joc.JMIN):

            #conditie pass
            if stare_curenta.tabla_joc.numara_posibile_mutari(stare_curenta.j_curent) == 0:
                print("Jucator: PASS ")
                stare_curenta.j_curent = stare_curenta.jucator_opus()
            else:

                print(stare_curenta.tabla_joc.afisare_pozitii_valide(stare_curenta.j_curent))
                #muta jucatorul
                raspuns_valid=False
                linie = -1
                coloana = -1
                directii = []
                while not raspuns_valid:
                    try:
                        linie = int(input("linie="))
                        coloana = input("coloana = ")
                        if not coloana.isalpha():
                            raise ValueError('Coloana trebuie sa fie un caracter')

                        # apoi de gasit pe ce "linie" este cea mai de jos
                        # casuta goala de pe acea "coloana"

                        if (linie >= 0 and linie < Joc.NR_LINII and coloana >= 'a' and coloana < chr(ord('a') + Joc.NR_COLOANE)):
                            coloana = ord(coloana) - ord('a')
                            if stare_curenta.tabla_joc.matr[linie][coloana] == Joc.GOL:
                                directii = stare_curenta.tabla_joc.pozitie_valida(linie, coloana, stare_curenta.j_curent)

                                if len(directii) > 0:
                                    raspuns_valid = True

                                else:
                                    print("Pozitia nu e valida")
                            else:
                                print("Pozitia e deja ocupata")
                        else:
                            print("Linie sau coloana invalida")


                    except ValueError:
                        print("Linia trebuie sa fie numar intreg, coloana un caracter.")

                #dupa iesirea din while sigur am valide linia si coloana
                #deci pot plasa simbolul pe "tabla de joc"

                #modificam tabla de joc curenta cu cea noua dupa capturarea pieselor
                stare_curenta.tabla_joc.matr = deepcopy(stare_curenta.tabla_joc.schimba_culoarea(linie, coloana, stare_curenta.j_curent, directii))

                #afisarea starii jocului in urma mutarii utilizatorului
                print("\nTabla dupa mutarea jucatorului")
                print(str(stare_curenta))

                # testez daca jocul a ajuns intr-o stare finala
                # si afisez un mesaj corespunzator in caz ca da
                if (afis_daca_final(stare_curenta)):
                    break

                #S-a realizat o mutare. Schimb jucatorul cu cel opus
                stare_curenta.j_curent = stare_curenta.jucator_opus()

        #--------------------------------
        else: #jucatorul e JMAX (calculatorul)
            #Mutare calculator
            # daca s-a blocat calculatorul
            if stare_curenta.tabla_joc.numara_posibile_mutari(stare_curenta.j_curent) == 0:
                print("Calculator: PASS ")
                stare_curenta.j_curent = stare_curenta.jucator_opus()
            else:
                t_inainte = int(round(time.time() * 1000))
                if tip_algoritm == '1':
                    stare_actualizata = min_max(stare_curenta)
                else:  # tip_algoritm==2
                    stare_actualizata = alpha_beta(-5000, 5000, stare_curenta)

                stare_curenta.tabla_joc = stare_actualizata.stare_aleasa.tabla_joc
                print("Tabla dupa mutarea calculatorului")
                print(str(stare_curenta))

                # preiau timpul in milisecunde de dupa mutare
                t_dupa = int(round(time.time() * 1000))
                print("Calculatorul a \"gandit\" timp de " + str(t_dupa - t_inainte) + " milisecunde.")

                if (afis_daca_final(stare_curenta)):
                    break

                # S-a realizat o mutare. Schimb jucatorul cu cel opus
                stare_curenta.j_curent = stare_curenta.jucator_opus()




if __name__ == "__main__" :
        main()