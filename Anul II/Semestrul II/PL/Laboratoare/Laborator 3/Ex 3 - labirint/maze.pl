/*Baza de cunostinte din maze.pl descrie un labirint.
Faptele indica ce puncte sunt conectate (din ce punct se poate ajunge
intr-un alt punct intr-un pas).
Drumurile sunt cu sens unic (se poate merge pe ele doar intr-o directie).
De exemplu, se poate ajunge intr-un pas de la 1 la 2, dar nu si invers.
Adaugati un predicat path/2 care indica daca dintr-un punct puteti sa
ajungeti intr-un alt punct (ˆin mai mult ¸i pasi), legˆand conexiunile din baza
de cunostinte.*/

% Maze
/*
connected(1,2).
connected(3,4).
connected(5,6).
connected(7,8).
connected(9,10).
connected(12,13).
connected(13,14).
connected(15,16).
connected(17,18).
connected(19,20).
connected(4,1).
connected(6,3).
connected(4,7).
connected(6,11).
connected(14,9).
connected(11,15).
connected(16,12).
connected(14,17).
connected(16,19).*/

connected(1,2).
connected(2,1).
connected(1,3).
connected(3,4).

path(X,Y, L) :- connected(X,Y).
path(X,Y) :- connected(X,Z), path(Z,Y).
%% atentie de facut fara cicluri