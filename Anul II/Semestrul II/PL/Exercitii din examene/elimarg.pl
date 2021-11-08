
termenValid(X) :- nonvar(X), number(X) ; nonvar(X), functor(X,_,Ar), Ar > 0.

transformaLista([],[],0).
transformaLista([H|L],[H|L1],Nr) :- termenValid(H), transformaLista(L,L1,Nr).
transformaLista([H|L],L1,Nr) :- not(termenValid(H)), transformaLista(L,L1,Nr1), Nr is Nr1+1.

recursieLista([],[]).
recursieLista([H|T],Rez) :- transformaTermen(H,Hnou), recursieLista(T,Tnou), append([Hnou],Tnou,Rez).
transformaTermen(F,Fn) :- nonvar(F),functor(F,_,Ar), Ar > 0,
                          F=..[Nume|Termeni],
                          recursieLista(Termeni,Rez),
                          transformaLista(Rez,TermNoi,Nr),
                          ((   Nr > 0 , Fn =..[Nume,Nr|TermNoi]);
                          (   Nr = 0 , Fn =..[Nume|TermNoi])).
transformaTermen(F,F) :- var(F) ; nonvar(F), functor(F,_,0).

elimarg(F,Fnou) :- transformaTermen(F,Fnou).
