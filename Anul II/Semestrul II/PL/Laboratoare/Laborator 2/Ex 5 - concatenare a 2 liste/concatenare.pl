/*un predicat care este poate fi folosit pentru a concatena dou ̆a liste
al treilea argument este concatenarea listelor date ca prime dou ̆a
argumente*/

concat([], L, L).
concat([H1|L1],L2,[H1|L3]) :- concat(L1, L2, L3).
