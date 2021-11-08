%predicat care dubleaza o lista de termeni
dubleazaTermeni(T,Tdublat) :- append(T,T,Tdublat).

%se ocupa cu parcurgerea in recursie a param. unei functii
dublatLista([],[]).
dublatLista([H|T],Tfin) :- dublatTermen(H,Hnou), dublatLista(T,Tnou),
                           append([Hnou],Tnou,Tfin).

%in cazul in care F e functie unara aplicam dubleazaTermeni
dublatTermen(F,Fnou) :- nonvar(F), F=..[Nume|Termeni], functor(F,_,Ar), Ar = 1,
                   dublatLista(Termeni,NoiTermeni),
                   dubleazaTermeni(NoiTermeni,TermeniFin),
                   Fnou=..[Nume|TermeniFin].
%in cazul in care F e functie, dar nu unara, nu aplicam dubleazaTermeni
dublatTermen(F,Fnou) :- nonvar(F), F=..[Nume|Termeni], functor(F,_,Ar), Ar \== 1,
                   dublatLista(Termeni,NoiTermeni),
                   Fnou=..[Nume|NoiTermeni].
%daca F e o variabila, ramane nemodificat
dublatTermen(F,F) :- var(F).


unardublat(F,Fnou) :- dublatTermen(F,Fnou).
