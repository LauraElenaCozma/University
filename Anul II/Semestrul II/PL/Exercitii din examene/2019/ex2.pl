cuvant(testul,6).
cuvant(usor,4).
cuvant(este,4).
cuvant(ada,3).
cuvant(carte, 5).

exista_aux(N,[], N).
exista_aux(N,[C|L], S) :- cuvant(C, Lung), S1 is S + Lung, S1 =< N, exista_aux(N, L, S1), not(member(C, L)).

exista(N,L) :- exista_aux(N,L,0).
