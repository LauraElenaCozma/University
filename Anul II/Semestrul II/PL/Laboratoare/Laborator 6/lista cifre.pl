/*Determina lista de cifre a unui numar dat*/
lista_cifre(X,[X]) :- X < 10.
lista_cifre(X,L) :- X >= 10, X1 is X//10,C is X mod 10,  lista_cifre(X1,L1), append(L1,[C],L).
