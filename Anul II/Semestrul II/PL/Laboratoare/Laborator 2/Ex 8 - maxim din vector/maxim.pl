
max([X],X).
max([H|L],M1) :- max(L, M1),H < M1.
max([H|L],H) :- max(L, M1),H >= M1.

