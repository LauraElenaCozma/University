/*Scrieti in Prolog un predicat list poz(L,R) care este adevarat daca R este o lista de perechi care contin elementele din L �si pozitia pe care se afla in L,
pozitiile fiind in ordine crescatoare:*/

list_pozaux([],_,[]).
list_pozaux([H|T],Poz,[(Poz,H)|R]) :- list_pozaux(T,Poz1,R), Poz1 is Poz+1.

list_poz(L,R) :- list_pozaux(L,1,R).
