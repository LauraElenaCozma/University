/*ˆIn fi ̧sierul animale.pl g ̆asit ̧i o baz ̆a de cuno ̧stinte care define ̧ste
animalele cunoscute. Un ”mutant” se obtine prin combinarea a doua
animale cunoscute, cu proprietatea ca numele unuia are un sufix care este
prefix pentru numele celuilalt. Numele animalului mutant se obtine prin
concatenarea celor dou ̆a nume, ˆın care partea comuna apare o singura
dat ̆a. De exemplu, din alligator  ̧si tortue se obt ̧ine aligatortue.
Scriet ̧i un predicat mutant/1 care genereaz ̆a pe rˆand toate animalele
mutante.*/
animal(alligator).
animal(tortue).
animal(caribou).
animal(ours).
animal(cheval).
animal(vache).
animal(lapin).
%% MULTA ATENTIE AICI CUM GASIM TOATE SUFIXURILE CARE SUNT PREFIX PENTRU
%%CELALALT CUVANT
mutant(M) :-animal(A), animal(B), A\==B, name(A,La), name(B,Lb),
    append(Pa,Sa,La), Pa \==[], append(Sa,_,Lb), Sa\==[], append(Pa,Lb,L), name(M,L).
