/*Vom rezolva acest puzzle ˆin Prolog.
1) Definiti un predicat la dreapta(X,Y) care este adevarat cand
numerele X si Y sunt consecutive, X fiind cel mai mare dintre ele.
2) Definiti un predicat la stanga(X,Y) care este adevarat cand
numerele X si Y sunt consecutive, Y fiind cel mai mare dintre ele.
3) Definiti un predicat langa(X,Y) care este adevarat cand numerele X
 ¸si Y sunt consecutive.*/

la_dreapta(X,Y) :- X is Y+1.
la_stanga(X,Y) :- Y is X+1.
langa(X,Y) :- la_dreapta(X,Y); la_stanga(X,Y).

solutie(Strada,PosesorZebra) :- Strada = [casa(1,norvegian,_,_,_,_),
                                          casa(2,_,_,_,_,_),
                                          casa(3,_,_,_,lapte,_),
                                          casa(4,_,_,_,_,_),
                                          casa(5,_,_,_,_,_)],
member(casa(_,englez,rosie,_,_,_), Strada),
member(casa(_,spaniol,_,caine,_,_), Strada),
member(casa(_,_,verde,_,cafea,_), Strada),
member(casa(_,ucrainean,_,_,ceai,_), Strada),
member(casa(_,_,_,melci,_,'Old Gold'), Strada),
member(casa(_,_,galbena,_,_,'Kools'), Strada),
member(casa(_,_,_,_,'suc de portocale','Lucky Strike'), Strada),
member(casa(_,japonez,_,_,_,'Parliaments'), Strada),
member(casa(Cv,_,verde,_,_,_), Strada),
member(casa(Cb,_,bej,_,_,_), Strada),
member(casa(Cc,_,_,_,_,'Chesterfields'), Strada),
member(casa(Cvulpe,_,_,vulpe,_,_), Strada),
member(casa(Ck,_,_,_,_,'Kools'), Strada),
member(casa(Ccal,_,_,cal,_,_), Strada),
member(casa(Calbs,_,albastra,_,_,_), Strada),
member(casa(Cnorv,norvegian,_,_,_,_), Strada),
langa(Cv,Cb),
langa(Cc, Cvulpe),
langa(Ck, Ccal),
langa(Calbs, Cnorv),
member(casa(_,PosesorZebra,_,zebra,_,_), Strada).
