
isvar(X) :- member(X,[a,b,c,d,e,f]).

/*Scrieti un predicat simplifica(E,ES) astfel incat E este o expresie data,
iar ES este expresia in care sunt simplificate operatiile cu zero.*/

simplifica(zero, zero).
simplifica(X, X) :- isvar(X).
simplifica(plus(E1,E2), Es) :- E2 = zero, simplifica(E1, Es),!.
simplifica(plus(E1,E2), Es) :- E1 = zero, simplifica(E2, Es),!.
simplifica(plus(E1,E2), plus(Es1, Es2)) :- simplifica(E1, Es1), simplifica(E2, Es2),!.


simplifica(ori(_,E2), zero) :- E2 = zero,!.
simplifica(ori(E1,_), zero) :- E1 = zero,!.
simplifica(ori(E1,E2), ori(Es1, Es2)) :- simplifica(E1, Es1), simplifica(E2, Es2),!.

/*Scriet ¸i un predicat valoare(Mem,Expr, Rez) astfel ˆincˆat:
- Mem este o lista de termeni de tipul vi(a,3) care au ca prim argument o variabila,
iar al doilea argument este valoarea variabilei respective;
- daca Expr este o expresie data, Rez va contine valoarea expresiei in care valorile variabilelor sunt date de Mem, iar valoarea lui zero este 0.*/
evaluare(L, C, R) :- isvar(C), member(vi(C,R), L).
evaluare(L, plus(E1,E2), Rez) :- evaluare(L, E1, Rez1), evaluare(L, E2, Rez2), Rez is Rez1 + Rez2.
evaluare(L, ori(E1,E2), Rez) :- evaluare(L, E1, Rez1), evaluare(L, E2, Rez2), Rez is Rez1 * Rez2.

valoare(M, Expr, Rez) :- simplifica(Expr, Expr1), evaluare(M, Expr1, Rez).
