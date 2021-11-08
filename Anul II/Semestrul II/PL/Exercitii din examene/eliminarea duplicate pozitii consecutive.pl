elimdup([],[]).
elimdup(L,L) :- length(L,1).
elimdup([H1,H2|T],[H1|L]) :- H1 \== H2, elimdup([H2|T],L).
elimdup([H1,H2|T],L) :- H1 = H2, elimdup([H2|T],L).


elimdupconsec([],[]).
elimdupconsec([H|T],[L1|L]) :- elimdup(H,L1), elimdupconsec(T,L).
