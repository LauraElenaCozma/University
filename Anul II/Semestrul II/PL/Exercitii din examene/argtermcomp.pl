efunctie(X) :- nonvar(X), functor(X,_,Ar) ,Ar > 0.

argtermcompLista([],[],0).
argtermcompLista([H|T],[Hnou|L],Nr) :- efunctie(H), argtermcompTerm(H,Hnou), argtermcompLista(T,L,Nr).
argtermcompLista([H|T],L,Nr) :- not(efunctie(H)), argtermcompLista(T,L,Nr1),Nr is Nr1+1.


argtermcompTerm(F,Fnou) :- efunctie(F), F=..[Nume|Termeni], argtermcompLista(Termeni,Tnoi,Nr), append([Nr],Tnoi,Rez), Fnou=..[Nume|Rez].
argtermcompTerm(F,F) :- not(efunctie(F)).

argtermcomp(F,Fnou) :- argtermcompTerm(F,Fnou).