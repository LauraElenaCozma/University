/*Scriet ̧i un predicat listpermcirc/2 care determin ̆a lista de permut ̆ari
circulare pentru o list ̆a dat ̆a ca parametru.*/

permuta_circular([],[]).
permuta_circular([H|P],NP) :- append(P,[H],NP).

lista_permutari_aux(Lin,L,[L]) :- L == Lin.
lista_permutari_aux(Lin,L,[L|LP]) :- L \== Lin, permuta_circular(L,L1), lista_permutari_aux(Lin, L1, LP).
% initial avem 123
% permutam circular ajungem la 231; 123 dif de 231
listapermcirc(L,LP) :- permuta_circular(L,L1), lista_permutari_aux(L,L1,LP).
