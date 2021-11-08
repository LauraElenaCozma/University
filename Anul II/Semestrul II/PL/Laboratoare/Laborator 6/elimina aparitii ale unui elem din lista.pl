/*Scriet ̧i un predicat elimina/3 care  ̧sterge toate aparit ̧iile unui
element dintr-o list ̆a dat ̆a ca parametru*/

elimina([],_,[]).
elimina([H|L],X,R) :- H =:= X, elimina(L,X,R).
elimina([H|L],X,[H|R]) :- H \== X, elimina(L,X,R).


/*Scriet ̧i un predicat multime/2 care transform ̆a o list ̆a ˆın mult ̧ime
eliminˆand toate duplicatele.*/
multime([],[]).
multime([H|L],[H|M]) :- multime(L,M1), elimina(M1, H, M).

/*Scrieti un predicat emult/1 care verifica daca o lista este multime.*/

emult(L) :- multime(L,M), L = M.

reuniune(M1,M2,R) :- append(M1, M2, R1), multime(R1, R).

inters([],_,[]).
inters([H|M1],M2,R) :- inters(M1,M2,R), not(member(H,M2)).
inters([H|M1],M2,[H|R]) :- inters(M1,M2,R), member(H,M2).

% ce e in M1 si nu e in M2
diff([],_,[]).
diff([H|M1],M2,[H|R]) :- diff(M1,M2,R), not(member(H,M2)).
diff([H|M1],M2,R) :- diff(M1,M2,R), member(H,M2).

perechi(_,[],[]).
perechi(X,[H|M],[(X,H)|R1]) :- perechi(X,M,R1).

prod_cartezian([],_,[]).
prod_cartezian([H|M1],M2,R2) :- prod_cartezian(M1,M2,R), perechi(H,M2,R1), append(R1, R, R2).
