/*Definit ̧i un predicat remove duplicates/2 care  ̧sterge toate duplicatele
din lista dat ̆a ca prim argument  ̧si ˆıntoarce rezultatul ˆın al doilea
argument.*/

% mai intai definim un predicat care sterge duplicatele pentru un
% element din lista
delete(_,[],[]).
delete(X,[X|L],L1) :- delete(X,L,L1).
delete(X,[Y|L],[Y|L1]) :- Y \== X, delete(X,L,L1).
%ATENTIE COMPARARE VARIABILE DISTINCTE

remove_duplicates([],[]).
remove_duplicates([H|L],[H|L2]) :- remove_duplicates(L,L1),delete(H,L1,L2).
