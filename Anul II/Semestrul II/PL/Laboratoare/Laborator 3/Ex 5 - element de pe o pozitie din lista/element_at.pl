/*Definit ̧i un predicat element at/3 care, primind o list ̆a  ̧si un num ̆ar
natural n, ˆıntoarce al n-ulea element din list ̆a.*/
element_at([H|_],1,H).
element_at([_|L],N,R) :- N1 is N - 1, element_at(L,N1,R).
