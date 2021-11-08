/*maxar sa fie satisfacut ddaca primul sau argument este un termen Prolog, al doilea argument al sau este
numarul natural egal cu maximul aritatilor operatiilor din componenta termenului de pe primul argument,
iar al treilea argument al sau este:

. lista numelor operatiilor de aritate maxima din componenta acelui
termen, daca termenul nu este o variabila; 
2. lista vida, daca acel termen este o variabila, aqsadar nu are
operatii ın component¸a sa, caz ın care al doilea argument al lui
maxar trebuie sa aiba valoarea 0; ¸si, ıntr–o interogare ˆın Prolog,
maxar s˘a funct¸ioneze sub forma: dac˘a primeste un termen arbitrar ˆın
primul argument, sa calculeze, ın al doilea argument, maximul
aritatilor operatiilor din componenta acelui termen, iar, ın al
treilea argument, sa obtina lista operatiilor de aritate maxima din
component¸a acelui termen*/


aritate_lista([],0,[]).
aritate_lista([H|Tail],ArMax,LMax) :-
    maxar(H, ArH, LH),
    aritate_lista(Tail, ArT, LT),
    (
        (   ArH > ArT, ArMax = ArH, LMax = LH);
        (   ArH = ArT, ArMax = ArH, append(LH,LT,LMax));
        (   ArH < ArT, ArMax = ArT, LMax = LT)).


maxar(V,0,[]) :- var(V).
maxar(T, ArMax, LMax) :-
    nonvar(T),
    T =.. [Nume|Termeni],
    functor(T,_,ArT),
    aritate_lista(Termeni, ArTerm, LTerm),
    (
        (   ArT > ArTerm, ArMax = ArT, LMax = [Nume]);
        (   ArT = ArTerm, ArMax = ArT, LMax = [Nume|LTerm]);
        (   ArT < ArTerm, ArMax = ArTerm, LMax = LTerm)).













