arbterm(X,arb(X,[])) :- var(X).
arbterm(X,AX) :- nonvar(X), X=..L, (L=[H], AX=arb(H,[]); L=[H,K|T], listarblistterm([K|T],ListSubarb), AX=arb(H,ListSubarb)).

listarblistterm(L,[]) :- nonvar(L), L=[].
listarblistterm(L,[AH|LAT]) :- nonvar(L), L=[H|T], arbterm(H,AH), listarblistterm(T,LAT).
