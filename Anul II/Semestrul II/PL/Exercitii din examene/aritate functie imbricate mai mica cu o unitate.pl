%toti termenii din lista sa aiba aritatea ar sau sa fie
% variabile
aritatebuna([],_).
aritatebuna([H|T],Ar) :- var(H), aritatebuna(T,Ar).
aritatebuna([H|T],Ar) :- nonvar(H), functor(H,_,Ar), aritatebuna(T,Ar).

difarlista([]).

difarlista([H|L]) :- nonvar(H),
                     functor(H,_,Ar),
                     difarterm(H,Ar),
                     difarlista(L).

difarlista([H|L]) :- var(H),
                     difarlista(L).



difarterm(F,Ar) :- F=..[_|Termeni],
                     Ar1 is Ar-1,
                     aritatebuna(Termeni,Ar1),
                     difarlista(Termeni).


difarunit(F) :- var(F).
difarunit(F) :- nonvar(F),functor(F,_,Ar), difarterm(F,Ar).

este(andrei, activ). este(elena, calm). este(radu, vesel).
iubeste(radu, hamsterii).
iubeste(Persoana, cainii) :- este(Persoana, activ).
iubeste(Persoana, pisicile) :- este(Persoana, calm).
iubeste(ana, Animal) :- iubeste(andrei, Animal).
iubeste(andrei, Animal) :- iubeste(elena, Animal).
iubeste(Persoana, Animal) :- iubeste(Prieten, Animal), este(Prieten, vesel).
