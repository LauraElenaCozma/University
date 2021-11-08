
form(W,R,O,N,G,Val) :- Val is (G + N * 10 + O * 10 ** 2 + R * 10 ** 3 + W * 10 ** 4).

is_digit(X) :- member(X,[0,1,2,3,4,5,6,7,8,9]).

distinct([]).
distinct([H|L]) :- not(member(H,L)), distinct(L).

validate(W,R,O,N,G,I,H,T) :- is_digit(W), is_digit(R), is_digit(O), is_digit(N),
    is_digit(G), is_digit(I), is_digit(H), is_digit(T), W > 0, R > 0,
    form(W,R,O,N,G,Vw), form(R,I,G,H,T,Vr),Vr is Vw+Vw.


