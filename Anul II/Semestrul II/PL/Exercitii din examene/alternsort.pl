/*un predicat binar alternsort, astfel ˆıncˆat alternsort(L, M) s˘a fie satisf˘acut ddac˘a L ¸si M
sunt liste de liste de numere, iar M se obt¸ine din lista L prin ˆınlocuirea fiec˘arui element
al sau cu o lista sortata, astfel:
primul element, L1, al lui L, se ınlocuieste cu lista S1 obtinuta prin sortarea crescatoare
a lui L1;
al doilea element, L2, al lui L, se ınlocuieste cu lista S2 obtinuta prin sortarea descresc˘atoare a lui L;
¸s.a.m.d.: elementele lui L de pe pozit¸ii impare se sorteaz˘a cresc˘ator, iar cele de pe pozit¸ii
pare se sorteaz˘a descresc˘ator ¸si se depun, astfel sortate, ˆın M;
s˘a se scrie ¸si toate predicatele auxiliare necesare pentru implementarea lui alternsort,
inclusiv un predicat pentru sortare de liste, cu o metod˘a de sortare la
alegere;
Elementele de pe pozitii impare sunt creascatoare, cele de pe poz impare descrescatoare*/
sortareimpara([],[]).
sortareimpara([H|T],[S|Rez]) :- sort(0,@<,H,S), sortarepara(T,Rez).
sortarepara([],[]).
sortarepara([H|T],[S|Rez]) :- sort(0,@>,H,S), sortareimpara(T,Rez).

alternsort(L,Rez) :- sortareimpara(L,Rez).
