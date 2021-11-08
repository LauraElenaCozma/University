termenPrioritar(T) :- var(T).
termenPrioritar(T) :- nonvar(T), functor(T,_,0).

extrageTermeniPrioritari([],[]).
extrageTermeniPrioritari([H|T],[H|L]) :- termenPrioritar(H),
                                         extrageTermeniPrioritari(T,L).

extrageTermeniPrioritari([H|T],L) :- not(termenPrioritar(H)),
                                         extrageTermeniPrioritari(T,L).


extrageTermeniNeprioritari([],[]).
extrageTermeniNeprioritari([H|T],[H|L]) :- not(termenPrioritar(H)),
                                         extrageTermeniNeprioritari(T,L).

extrageTermeniNeprioritari([H|T],L) :- termenPrioritar(H),
                                         extrageTermeniNeprioritari(T,L).



reordonareTermeni(L,NL) :- extrageTermeniPrioritari(L,PL),
                           extrageTermeniNeprioritari(L,PN),
                           append(PL,PN,NL).


punvarctLista([],[]).
punvarctLista([H|T],Rez) :- punvarctTermen(H,Hnou), punvarctLista(T,Tnou),
                         append([Hnou],Tnou,Rez).

punvarctTermen(F,Fnou) :- nonvar(F), F=..[Nume|Termeni],
                          reordonareTermeni(Termeni,ReordTerm),
                          punvarctLista(ReordTerm,NoiTermeni),
                          Fnou=..[Nume|NoiTermeni].
punvarctTermen(F,F) :- var(F).


punvarctinfata(F,Fnou) :- punvarctTermen(F,Fnou).
