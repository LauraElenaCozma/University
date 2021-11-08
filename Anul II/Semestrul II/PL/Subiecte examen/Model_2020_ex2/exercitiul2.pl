/*S˘a se scrie un predicat ternar selectpoz(Lista, T otACataP ozitie, ListaElementeSelectate),
definit ca mai jos, precum ¸si toate predicatele auxiliare necesare pentru definirea acestuia:
selectpoz s˘a fie satisf˘acut ddac˘a primul s˘au argument este o list˘a L, al doilea argument al s˘au este un
num˘ar natural nenul N, iar al treilea argument este lista elementelor lui L aflate ˆın lista L pe pozit¸ii date
de multiplii lui N cuprin¸si ˆıntre N ¸si lungimea listei L;
¸si, ˆıntr–o interogare ˆın Prolog, selectpoz s˘a funct¸ioneze sub forma: dac˘a prime¸ste o list˘a arbitrar˘a L
ˆın primul argument ¸si un num˘ar natural nenul arbitrar N ˆın al doilea argument, s˘a obt¸in˘a ˆın al treilea
argument lista elementelor lui L selectate din N ˆın N pozit¸ii, ca mai
sus; de exemplu:*/

elem_poz([H|_],1,H).
elem_poz([_|L],P,V) :- P1 is P - 1, elem_poz(L,P1,V).

selectpozaux(L, N, [], _) :- length(L, Len), N>Len.
selectpozaux(L, N, [X|NL], Naux) :-length(L, Len), N=<Len,elem_poz(L,N,X), N1 is N + Naux, selectpozaux(L, N1, NL, Naux).


selectpoz(L, N, NL) :- selectpozaux(L,N,NL,N).
