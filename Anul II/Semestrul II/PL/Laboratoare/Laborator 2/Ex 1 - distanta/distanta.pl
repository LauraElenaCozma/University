/*Definit ̧i un predicat distance/3 pentru a calcula distant ̧a dintre dou ̆a
puncte ˆıntr-un plan 2-dimensional. Punctele sunt date ca perechi de
coordonate.*/

distance((X1, Y1), (X2, Y2), D) :- D is sqrt((X1 - X2) ** 2 + (Y1 - Y2) ** 2).
