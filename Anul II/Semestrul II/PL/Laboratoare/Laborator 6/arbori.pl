
srd(nil,[]).
srd(arb(R,S,D), L):- srd(S,Ls), srd(D,Ld), append(Ls,[R|Ld], L).

rsd(nil,[]).
rsd(arb(R,S,D), L):- rsd(S,Ls), rsd(D,Ld), append([R|Ls],Ld, L).

sdr(nil,[]).
sdr(arb(R,S,D), L):- sdr(S,Ls), sdr(D,Ld), append(Ls,Ld, L1), append(L1,[R],L).

frunze(nil,[]).
frunze(arb(X,nil,nil),[X]).
frunze(arb(_,S,D),L) :- (S\=nil;D\=nil),!,frunze(S,Ls), frunze(D,Ld), append(Ls,Ld,L).


fructe(mere). fructe(pere). fructe(capsuni).
sunt(mere, rosii). sunt(capsuni, rosii). sunt(pere, gustoase). sunt(capsuni, gustoase).
consuma(ana, X) :- fructe(X), sunt(X, rosii).
consuma(victor, X) :- fructe(X), sunt(X, rosii).
consuma(victor, X) :- fructe(X), sunt(X, gustoase).

q(a).
q(b).
r(c).
r(d).
s(e).
top(X,Y) :- p(X,Y).
top(X,X) :- s(X).
p(X,Y) :- q(X), r(Y).
p(X,Y) :- s(X), r(Y).


joc(sah, 2). joc(reversi, 2). joc(solitaire, 1).
joc(cartiJoc, OricatiJucatori).
prefera(ana, Joc) :- joc(Joc, 1).
prefera(george, Joc) :- joc(Joc, 5).
prefera(victor, Joc) :- joc(Joc, 2).
prefera(victor, Joc) :- prefera(george, Joc).
