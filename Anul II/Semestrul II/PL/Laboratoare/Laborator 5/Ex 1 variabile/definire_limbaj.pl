

is_var(a).
is_var(b).
is_var(c).
is_var(d).
is_var(e).


:- op(630, xfy, sau).
:- op(620, xfy, si).
:- op(610, fy,  nu).
:- op(640, xfy, imp).
/*scrieti un predicat care sa intoarca true daca
argumentul este o formula corecta.*/

/*
formula(X) :- is_var(X).
formula(nu X) :- formula(X).
formula(si(X,Y)) :- formula(X), formula(Y).
formula(X sau Y) :- formula(X), formula(Y).
formula(X imp Y) :- formula(X), formula(Y).

formula(X) :- is_var(X).
formula(nu X) :- formula(X).
formula(sau(X,Y)) :- formula(X), formula(Y).
formula(si(X,Y)) :- formula(X), formula(Y).
formula(imp(X,Y)) :- formula(X), formula(Y).*/
formula(X) :- is_var(X).
formula(nu X) :- formula(X).
formula(X sau Y) :- formula(X), formula(Y).
formula(X si Y) :- formula(X), formula(Y).
formula(X imp Y) :- formula(X), formula(Y).

test :- catch(read(X), Error, false) , X.

find_vars(X,V,Vfin) :-