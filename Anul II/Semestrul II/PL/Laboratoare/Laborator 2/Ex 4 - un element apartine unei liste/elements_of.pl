/*un predicat care verific ̆a dac ̆a o list ̆a cont ̧ine un anumit termen
element of(X,Y) trebuie s ̆a fie adev ̆arat dac ̆a X este un element al
lui Y.
 Dac ̆a primult element al listei este termenul
pe care ^ıl c ̆aut ̆am, atunci am terminat. */
element_of(X, [X]).
element_of(X, [H|L]) :- X =:= H; element_of(X, L).
