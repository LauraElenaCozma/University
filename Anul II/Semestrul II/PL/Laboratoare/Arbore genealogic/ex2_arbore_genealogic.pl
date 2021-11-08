male(rickard).
male(aerys).
male(eddard).
male(brandon).
male(benjen).
male(rhaegar).
male(viserys).
male(robb).
male(bran).
male(rickon).
male(jon).
male(aegon).

female(lyarra).
female(rhaella).
female(catelyn).
female(lyanna).
female(elia).
female(daenerys).
female(sansa).
female(arya).
female(rhaenis).

/* parent_of(X , Y) X este copilul lui Y*/

child_of(eddard , rickard).
child_of(eddard , lyarra).
child_of(brandon , rickard).
child_of(brandon , lyarra).
child_of(benjen , rickard).
child_of(benjen , lyarra).
child_of(lyanna , rickard).
child_of(lyanna , lyarra).
child_of(rhaegar , aerys).
child_of(rhaegar , rhaella).
child_of(viserys , aerys).
child_of(viserys , rhaella).
child_of(daenerys , aerys).
child_of(daenerys , rhaella).
child_of(robb , catelyn).
child_of(robb , eddard).
child_of(sansa , catelyn).
child_of(sansa , eddard).
child_of(arya , catelyn).
child_of(arya , eddard).
child_of(bran , catelyn).
child_of(bran , eddard).
child_of(rickon , catelyn).
child_of(rickon , eddard).
child_of(jon , lyanna).
child_of(jon , rhaegar).
child_of(rhaenys , elia).
child_of(rhaenys , rhaegar).
child_of(rhaenys , aegon).
child_of(rhaenys , rhaegar).

parent_of(X , Y) :- child_of(Y , X).
father_of(F , C) :- parent_of(F , C) , male(F).
mother_of(M , C) :- parent_of(M , C) , female(M).
%sa fie parinte si daca e parinte sa fie femeie
grandfather_of(GF , C) :- father_of(GF , F) , father_of(F , C) ; father_of(GF , M) , mother_of(M , C).
%gf sa fie tatal tatalui lui c sau gf sa fie tatal mamei lui c
grandmother_of(GM , C) :- mother_of(GM , F) , father_of(F , C) ; mother_of(GM , M) , mother_of(M , C).
%gm sa fie mama tatalui lui c sau gm sa fie mama mamei lui c

sister_of(S , P) :- father_of(F , S) , father_of(F , P) , mother_of(M , S) , mother_of(M , P) , female(S) , not(S = P).
brother_of(S , P) :- father_of(F , S) , father_of(F , P) , mother_of(M , S) , mother_of(M , P) , male(S) , not(S = P).
% au aceeasi parinti, e baiat si S nu e acceasi persoana cu P

aunt_of(A , P) :- sister_of(A , Parent) , parent_of(Parent , P).
% este sora parintelui lui P
uncle_of(U , P) :- brother_of(U , Parent) , parent_of(Parent, P).
% este fratele unui parinte
%
/*?- uncle_of(B , robb).
B = brandon ;
B = benjen ;
false.

?- uncle_of(B , arya).
B = brandon ;
B = benjen ;
false.

?- aunt_of(A , arya).
A = lyanna ;
false.

?- aunt_of(daenerys , jon).
true .
*/
/* !!!!!! nu merge*/
ancestor_of(X , P) :- father_of(X , P) ; mother_of(X , P) ; aunt_of(X , P) ; uncle_of(X , P).
ancestor_of(X , P) :- ancestor_of(Y , P) , (father_of(Y , P) ; mother_of(Y , P) ; aunt_of(Y , P) ; uncle_of(Y , P)).


not_parent(X,Y) :- not(parent_of(X,Y)).
% sau not_parent(X,Y) :- \+ parent_of(X,Y).

ancestor_not_parent(X,Y) :- ancestor_of(X , Y) , not_parent(X , Y).


char(king).
char(richMan).
char(priest).

choice(god,priest).
% daca e persoana religioasa, nu alege preotul
choice(money , richMan).
choice(authority , king).

is_killed(C , X , Y) :- not(choice(C , X)) , not(choice(C , Y)).
% X si Y sunt ucisi de alegerea C a mercenarului
