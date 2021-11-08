/*un predicat binar catectnr care s˘a primeasc˘a drept prim argument un termen arbitrar ¸si
s˘a calculeze, ˆın al doilea argument, num˘arul de constante numerice care apar ˆın scrierea
termenului dat ˆın primul argument; de exemplu, la o interogare de forma:
?- catectnr(f(g(f(a, 10), f(f(5.5, Y ), −2)), f(X, Y )), Cate).
r˘aspunsul dat de Prolog trebuie s˘a fie: Cate=3.*/
% verifica daca e o constanta numerica
eConstanta(X) :- nonvar(X), functor(X,_,0), number(X).

% am ajuns la un termen de tip functie si trebuie spart
constanteInTermen(F, Nr) :- F =..[_|Termeni],  constanteInLista(Termeni,Nr).

constanteInLista([],0).
%e constanta numerica
constanteInLista([H|T],Nr) :- eConstanta(H), constanteInLista(T,Nr1), Nr is Nr1+1.
%e variabila
constanteInLista([H|T],Nr) :- not(eConstanta(H)), var(H), constanteInLista(T,Nr).
%e constanta
constanteInLista([H|T],Nr) :- nonvar(H), functor(H,_,0), not(number(H)), constanteInLista(T,Nr).
%e functie
constanteInLista([H|T],Nr) :- nonvar(H), functor(H,_,A), A > 0, constanteInTermen(H,NrT), constanteInLista(T,NrL), Nr is NrT+NrL.

catectnr(F,Nr) :- constanteInTermen(F,Nr).
