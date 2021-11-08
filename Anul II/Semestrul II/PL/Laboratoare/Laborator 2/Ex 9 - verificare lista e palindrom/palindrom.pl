/*Definit ̧i un predicat palindome/1 care este adev ̆arat dac ̆a lista primit ̆a ca
argument este palindrom (lista citit ̆a de la stˆanga la dreapta este identic ̆a
cu lista citit ̆a de la dreapta la stˆanga).*/

%AAAAAATENTIEEE LA APPEND H E TIP LISTA
inversa([],[]).
inversa([H|L], L2) :- inversa(L, L1), append(L1,[H], L2).

palindrome([]).
palindrome(L1) :- inversa(L1, L2), L1 = L2.
