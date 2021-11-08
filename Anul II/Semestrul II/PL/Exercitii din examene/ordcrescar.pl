
modificareTermeni([],[]).
modificareTermeni([H|T],[(-1,H)|L]) :- var(H), modificareTermeni(T,L).
modificareTermeni([H|T],[(Ar,H)|L]) :- nonvar(H), functor(H,_,Ar),
                                       modificareTermeni(T,L).

concat([],L,L).
concat([H|T],L,[H|M]) :- concat(T,L,M).

% Quicksort-ul, cu pivotul ales ca fiind capul listei la fiecare pas:

taie((_,_),[],[],[]).
taie((ArP,P),[(ArH,H)|T],[(ArH,H)|L],M) :- ArH=<ArP, taie((ArP,P),T,L,M).
taie((ArP,P),[(ArH,H)|T],L,[(ArH,H)|M]) :- ArH>ArP, taie((ArP,P),T,L,M).

qsort([],[]).
qsort([(Ar,P)|T],S) :- taie((Ar,P),T,M,N),qsort(M,Q),qsort(N,R),concat(Q,[(Ar,P)|R],S).


%sortamDupaCheie(L,LS) :- modificareTermeni(L,NL), sort(1,=<,NL,LS).
sortamDupaCheie(L,LS) :- modificareTermeni(L,NL), qsort(NL,LS).


elimCheie([],[]).
elimCheie([(_,H)|L],[H|NL]) :- elimCheie(L,NL).

ordcrescar(L,NL) :- sortamDupaCheie(L,SL), elimCheie(SL,NL).