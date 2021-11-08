/*Definit ̧i un predicat crosswd/6 care calculeaz ̆a toate variantele ˆın care
putet ̧i completa grila. Primele trei argumente trebuie s ̆a fie cuvintele pe
vertical ̆a, de la stˆanga la dreapta, (V1,V2,V3), iar urm ̆atoarele trei
argumente trebuie s ̆a fie cuvintele pe orizontal ̆a, de sus ˆın jos (H1,H2,H3).
Hint: Specificat ̧i c ̆a V1, V2, V3, H1, H2, H3 sunt cuvinte care au
anumite litere comune. Unde este cazul, folosit ̧i variabile anonime.*/

% Crossword puzzle

word(abalone,a,b,a,l,o,n,e).
word(abandon,a,b,a,n,d,o,n).
word(enhance,e,n,h,a,n,c,e).
word(anagram,a,n,a,g,r,a,m).
word(connect,c,o,n,n,e,c,t).
word(elegant,e,l,e,g,a,n,t).

crossword(V1, V2, V3, H1, H2, H3) :-
    word(V1,_,A,_,B,_,C,_),
    word(V2,_,D,_,E,_,F,_),
    word(V3,_,G,_,H,_,I,_),
    word(H1,_,A,_,D,_,G,_),
    word(H2,_,B,_,E,_,H,_),
    word(H3,_,C,_,F,_,I,_).
crosswd(V1,V2,V3,H1,H2,H3) :-
                word(V1,_,A,_,B,_,C,_),
                word(V2,_,D,_,E,_,F,_),
                word(V3,_,G,_,H,_,I,_),
                word(H1,_,A,_,D,_,G,_),
                word(H2,_,B,_,E,_,H,_),
                word(H3,_,C,_,F,_,I,_).





