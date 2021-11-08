

:- op(300,fy,lista_nr).

:- op(300,fy,nr_elem).


nr_elem([],0).
nr_elem([_|L],Nr) :- nr_elem(L,Nr1), Nr is Nr1+1.



lista_nr([],[],_).
lista_nr([H|L],[H2|L1],Nr) :- nr_elem(H,Val),append([lista_nr Nr],H,H1),append(H1,[nr_elem Val],H2), Nr1 is Nr+1, lista_nr(L,L1,Nr1).

nrlistanrelem(L,LL) :- Nr is 1, lista_nr(L,LL,Nr).
