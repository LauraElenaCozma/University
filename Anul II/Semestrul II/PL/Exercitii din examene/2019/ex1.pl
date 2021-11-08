/*Scrieti un predicat media(ListaStudenti, Student,Media) astfel ıncat:
- ListaStudenti este o lista cu termeni sn(numeStudent, nota); ın aceasta lista, acelasi student poate sa apara de mai multe ori;
- pentru Student dat, Media va fi media notelor studentului respectiv.*/

media_aux([], _, 0, 0).
media_aux([sn(N, Nota)|L], Nume, S1, Nr1) :- media_aux(L, Nume, S, Nr), N = Nume, S1 is S + Nota, Nr1 is Nr + 1.

media_aux([sn(N, _)|L], Nume, S, Nr) :- media_aux(L, Nume, S, Nr), N\==Nume.

media(L,Nume, Med) :- media_aux(L, Nume, S, Nr), Med is S/Nr.
