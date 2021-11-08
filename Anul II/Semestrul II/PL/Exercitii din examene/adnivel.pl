
termenadmisibil(T) :- nonvar(T), not(number(T)).


adnivlista([],_,[]).
adnivlista([H|T],Niv,Rez) :- termenadmisibil(T),adnivterm(H,Niv,NouH),
                          adnivlista(T,Niv,RezT),append([NouH],RezT,Rez).

adnivlista([H|T],Niv,Rez) :- not(termenadmisibil(T)),                                                 adnivlista(T,Niv,RezT),append([H],RezT,Rez).

adnivterm(F,Niv,NouTerm) :- termenadmisibil(F),
                            F=..[Nume|Termeni], Niv1 is Niv+1,
                            adnivlista(Termeni,Niv1,RezT),
                            NouTerm=..[Nume,Niv|RezT].
adnivterm(F,_,F) :- not(termenadmisibil(F)).

adnivel(F,Termen) :- adnivterm(F,0,Termen).
