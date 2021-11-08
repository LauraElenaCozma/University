/*A) Definit ̧i un predicat all a/1 care prime ̧ste ca argument o list ̆a  ̧si care
verific ̆a dac ̆a argumentul s ̆au este format doar din a-uri.
?- all a([a,a,a,a]).
?- all a([a,a,A,a]).
B) Scrieti un predicat trans a b/2 care ”traduce” o list ̆a de a-uri ˆıntr-o
list ̆a de b-uri. trans a b(X,Y) trebuie s ̆a fie adev ̆arat dac ̆a ”intrarea” X
este o list ̆a de a-uri  ̧si ”ie ̧sirea” Y este o list ̆a de b-uri, iar cele dou ̆a liste
au lungimi egale.*/

all_a(['a']).
%all_a(['A']).
%all_a(['A'|L]) :- all_a(L).
all_a(['a'|L]) :- all_a(L).

trans_a_b([],[]).
trans_a_b(['a'|L1],['b'|L2]) :- trans_a_b(L1, L2).
