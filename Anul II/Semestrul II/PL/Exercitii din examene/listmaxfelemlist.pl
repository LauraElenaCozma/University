/*listmaxfelemlist s˘a fie satisf˘acut primul s˘au argument este o list˘a LL de liste avˆand elemente care nu
au elemente de tip lista, iar al doilea argument al s˘au este una dintre listele din LL care nu are elemente de
tip lista la randul ei ¸si este de lungime maxima raportat la aceasta proprietate;
¸si, ıntr–o interogare ˆın Prolog, listmaxfelemlist s˘a funct¸ioneze sub forma: dac˘a primeste, ın primul
argument, o list˘a arbitrar˘a de liste LL, atunci sa ıntoarca false daca LL nu cont¸ine liste care s˘a nu cont¸in˘a
liste, iar, ˆın caz contrar, sa obtina ın al doilea argument o lista
L din LL de lungime maxim˘a astfel ıncat L
s˘a nu cont¸in˘a liste; de exemplu:*/


nuEListaInLista([]).
nuEListaInLista([H|L]) :- not(is_list(H)), nuEListaInLista(L).

% ! ne oprim la ultimul element, daca e o lista fara liste in el,
% initializam maximul
listaLungMax([H|L],Lmax,H) :- length(L,0),is_list(H), nuEListaInLista(H), length(H,Lmax).
% ne oprim la ultimul element, daca e o lista cu liste in el,
% initializam maximul cu -1; daca se gasesc elemente dorite pe parcurs,
% maximul se schimba. daca nu,ramane -1. In acest caz returnam false
listaLungMax([H|L],-1,_) :- length(L,0),is_list(H),
    not(nuEListaInLista(H)).
listaLungMax([H|L],Len,H) :- is_list(H),listaLungMax(L,Max1,_),
    nuEListaInLista(H), length(H,Len), Len > Max1.
listaLungMax([H|L],Max1,R1) :- is_list(H),listaLungMax(L,Max1,R1),
    nuEListaInLista(H), length(H,Len), Len =< Max1.
listaLungMax([H|L],Max1,R1) :- is_list(H),listaLungMax(L,Max1,R1),
    not(nuEListaInLista(H)).

listamaxfelemlist(L,Lmax) :- listaLungMax(L,Len,Lmax), Len \== -1.
