trans_a_b([] , []).
trans_a_b([a | Tail1] , [b | Tail2]) :- trans_a_b(Tail1 , Tail2).
/*
[2]  ?- trans_a_b([a , a , a] , L).
L = [b, b, b].

[2]  ?- trans_a_b([a , a , a] , [b]).
false.

[2]  ?- trans_a_b(L , [b , b]).
L = [a, a].*/
