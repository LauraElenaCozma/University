/*Scriet ̧i un program ˆın Prolog pentru a afi ̧sa un p ̆atrat de n × n caractere
pe ecran.
Denumit ̧i predicatul square/2. Primul argument este un num ̆ar natural
diferit de 0, iar al doilea un caracter (i.e, orice termen ˆın Prolog) care
trebuie afi ̧sat.*/

linie(0, _).
linie(N, C) :- N > 0, write(C), write(' '), N1 is N-1, linie(N1, C).

sq(_, 0, _).
sq(N, M, C) :- linie(N, C), nl, N1 is M - 1, sq(N, N1, C).

square(N, C) :- sq(N, N, C).
