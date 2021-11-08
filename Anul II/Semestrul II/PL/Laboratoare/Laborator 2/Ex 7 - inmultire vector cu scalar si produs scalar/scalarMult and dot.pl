/*A) Scriet ̧i un predicat scalarMult/3 al c ̆arui prim argument este un
ˆıntreg, al doilea argument este o list ̆a de ˆıntregi, iar al treilea argument
este rezultatul ˆınmult ̧irii cu scalari al celui de-al doilea argument cu
primul.*/
scalarMult(_,[],[]).
scalarMult(C, [H|L], [H1|L2]) :- H1 is C*H, scalarMult(C, L, L2).
% scalarMult(C, [H|L], [H*C|L2]) :- scalarMult(C, L, L2). NU MERGE.
% afiseaza *

/*B) Scriet ̧i un predicat dot/3 al c ̆arui prim argument este o list ̆a de
ˆıntregi, al doilea argument este o list ̆a de ˆıntregi de lungimea primeia, iar
al treilea argument este produsul scalar dintre primele dou ̆a argumente.*/
dot([],[],0).
dot([H1|L1],[H2|L2],S) :- H3 is H1 * H2, dot(L1,L2,S1), S is S1 + H3.
