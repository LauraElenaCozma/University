/*a) Definit ̧i un predicat successor/2 care ˆıntoarce ˆın al doilea argument
succesorul num ̆arului dat ca prim argument.*/

succesor(L,[x|L]).

/*b) Definit ̧i un predicat plus/3 care adun ̆a dou ̆a numere.*/
plus(L1,[],L1).
plus(L1,[x|L2],[x|L3]) :- plus(L1,L2,L3).

/*c) Definit ̧i un predicat times/3 care ˆınmult ̧e ̧ste dou ̆a numere.*/
times([],_,[]).
times([_|L1],L2,R) :- times(L1,L2,R1), plus(L2,R1,R).
