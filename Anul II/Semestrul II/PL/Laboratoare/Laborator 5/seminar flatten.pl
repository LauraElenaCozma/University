/*Scriet ̧i un predicat flatten(L,R) unde L este o list ̆a de liste, iar R cont ̧ine elementele lui
L, ˆın aceea ̧si ordine, dar elimin ̆a gruparea ˆın liste:*/
flatten([],[]).
flatten([H|L],Rez) :- flatten(L, Rez1), append(H,Rez1,Rez).
