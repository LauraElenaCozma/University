
num_aparitii([],_,0).
num_aparitii([H|L],X,Nr) :- H = X, num_aparitii(L,X,Nr1), Nr is Nr1 + 1;
                           H \== X, num_aparitii(L,X,Nr1), Nr is Nr1.
