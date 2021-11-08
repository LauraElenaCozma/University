listintermnr([],[]).
listintermnr([H],[H]) :- number(H).
listintermnr([H],[[H]]) :- not(number(H)).
% daca H e constanta numerica, adaugam la rezultat H
listintermnr([H|T],[H|Lrez]) :- number(H),
                             listintermnr(T, Lrez).  %luam rezultatul de dupa H


listintermnr([H|T], Rez) :- not(number(H)),
                          listintermnr(T, [Hrez | Lrez]),
                          not(is_list(Hrez)),  %daca ultimul element nu e lista
                          append([[H]], [Hrez | Lrez], Rez).%formam o noua lista din H
listintermnr([H|T], Rez) :- not(number(H)),
                          listintermnr(T, [Hrez | Lrez]),
                          is_list(Hrez), %daca e deja o lista dupa el
                          append([[H|Hrez]], Lrez, Rez). %il adaugam la lista existenta
























