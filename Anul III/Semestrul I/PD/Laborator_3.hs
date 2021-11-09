------LISTE--------
-----List comprehension------
a = [x^2 | x <- [1..10], x `rem` 3 == 2]   ---rem un fel de mod
--[4,25,64]
a' = [(x, y) | x <- [1..5], y <- [x..(x+2)]]
--[(1,1),(1,2),(1,3),(2,2),(2,3),(2,4),(3,3),(3,4),(3,5),(4,4),(4,5),(4,6),(5,5),(5,6),(5,7)]
a'' = [(x, y) | x <- [1..3], let k = x^2, y <- [1..k]]
--[(1,1),(2,1),(2,2),(2,3),(2,4),(3,1),(3,2),(3,3),(3,4),(3,5),(3,6),(3,7),(3,8),(3,9)]
a''' = [x | x <- "Facultatea de Matematica si Informatica", elem x ['A'..'Z']]
------ !!!!! elem x lista => True daca x apartine listei
--"FMI"
a'''' = [[x..y] | x <- [1..5], y <- [1..5], x < y]
--[[1,2],[1,2,3],[1,2,3,4],[1,2,3,4,5],[2,3],[2,3,4],[2,3,4,5],[3,4],[3,4,5],[4,5]]



---Ex 1. factori n întoarce lista divizorilor pozitivi ai lui n.
factori :: Int -> [Int]
factori n = [x | x <- [1..n], n `mod` x == 0]

--Ex 2. Folosind functia factori, definiti predicatul prim n care întoarce True dac s, i numai
--daca n este numar prim.
prim n = (factori n) == [1, n]

--Ex 3. numerePrime n întoarce lista numerelor prime din intervalul [2..n].
numerePrime :: Int -> [Int]
numerePrime n = [x | x <- [2..n], prim x]

--Ex 4. Myzip3 care face zip cu 3 argumente
--folosind variabile auxiliare
myzip3 l1 l2 l3 =
    let
        zip1 = zip l1 l2 
        zip2 = zip zip1 l3
    in
    [(a,b,c) | ((a,b),c) <- zip2]
--fara variabile auxiliare
myzip3' l1 l2 l3 = [(a, b, c) | ((a, b), c) <- zip (zip l1 l2) l3]

--------Functii de nivel inalt-------
--------MAP--------
--Ex. 1: Scrieti o functie generic firstEl care are ca argument o list de perechi de tip (a,b)
--si întoarce lista primelor elementelor din fiecare pereche
---List comprehension---
firstElComp l = [a | (a,b) <- l]
---Map--- 
firstElMap l = map (\(a,b) -> a) l

--Ex. 2:Scrieti functia sumList care are ca argument o list de liste de valori Integer s, i întoarce
--lista sumelor elementelor din ecare list (suma elementelor unei liste de întregi se
--calculeaz cu functia sum):
sumListComp l = [sum l_sub | l_sub <- l]

sumListMap l = map sum l

sumListRec [] = []
sumListRec (l_sub:l) = (sum l_sub) : (sumListRec l)

--Ex. 3: Scrieti o functie prel2 care are ca argument o list de Integer s, i întoarce o list în
--care elementele pare sunt înjumatatite, iar cele impare sunt dublate:
prel2Comp l = [k | x <- l, let k = if odd x then x * 2 else x `div` 2]
prel2Map l = map (\x -> if odd x then x * 2 else x `div` 2) l  ---ATENTIE DIV nu /

------FILTER--------
--Ex. 1: Scrieti o functie care primeste ca argument un caracter si o lista de siruri, rezultatul
--ind lista sirurilor care contin caracterul respectiv (folositi functia elem).
contineCaracterFil x l = filter (x `elem`) l

contineCaracterRec x [] = []
contineCaracterRec x (l_sub:l) = if x `elem` l_sub 
    then l_sub : (contineCaracterRec x l)
    else contineCaracterRec x l
contineCaracterComp x l = [l_sub | l_sub <- l, let res = x `elem` l_sub, res == True]

--Ex 2: Scrieti o functie care primeste ca argument o list de întregi s, i întoarce lista p tratelor
--numerelor impare.
patratImpareMap l = map (^2) (filter odd l)
patratImpareComp l = [x^2 | x <- l, odd x]
patratImpareRec [] = []
patratImpareRec (h:l) = if odd h 
    then h^2 : patratImpareRec l 
    else patratImpareRec l

--Ex 3: Scrieti o functie care primeste ca argument o list de întregi s, i întoarce lista p tratelor
--numerelor din pozitii impare. Pentru a avea acces la pozit, ia elementelor folositi zip.
--------DIFICIL
patratPozImpMap l = map (^2) (map (\(el, poz) -> el) (filter (\(el, poz) -> odd poz) (zip l [1..])))

--Ex 4: Scrieti o functie care primeste ca argument o list de s, iruri de caractere s, i întoarce
--lista obtinuta prin eliminarea consoanelor din ecare s, ir. Rezolvat, i exercit, iul folosind
--numai filter, map si elem.  
------ ?????? Exista o varianta mai usoara ?????  --------DIFICIL
numaiVocale l = map (filter (\x -> x `elem` "aeiouAEIOU")) l

--Defiti recursiv functiile mymap si myfilter cu aceeasi functionalitate ca si functiile predefinite
mymap f [] = []
mymap f (h:lista) = (f h) : (mymap f lista)
--mymap (\x -> x * 2) [2,4,1,5,3]    [4,8,2,10,6]
myfilter f [] = []
myfilter f (h:lista) = if (f h) then h : (myfilter f lista) else (myfilter f lista)
--myfilter (\x -> x `mod` 2 == 0) [2,4,1,5,3]  [2,4]


-- Folosind comprehensiunea, functia and si functia zip, completati definitia functiei ordonataNat 
-- care verica daca o lista de valori Int este ordonata , relatia de ordine fiind cea naturala:
---ATENTIE
ordonataNat lista = and [x <= y | (x,y) <- zip lista (tail lista)]


-------------------------------- Recapitulare laborator ------------------------------------------

--Functie care calculeaza factorialul unui numar
fact n = if (n == 0) then 1
         else n * fact (n - 1)


--Ia primul element dintr-o lista de perechi
firstEl l = [x | (x, y) <- l]

--Calculeaza suma elementelor fiecarei liste
sumList list = [sum l | l <- list]

--Numerele impare sunt dublate iar cele pare se injumatatesc
prel2 list = 
        let
            prelucrare x = if mod x 2 == 0 then x `div` 2
                           else (x * 2)
        in [prelucrare x | x <- list]

--Suma elementelor pare
f [] = 0
f l = if mod (head l) 2 == 0 then 
        head l + (f (tail l))
      else  
        f (tail l)

--v2 folosind sabloane
f2 [] = 0
f2 (cap:coada) = if mod cap 2 == 0 then 
                  cap + (f coada)
                 else 
                  f coada

--suma elementelor din 2 in 2
sumdoi [] = 0
--sumdoi [elem] = elem sau
sumdoi (elem:[]) = elem
sumdoi (cap1:cap2:coada) = cap1 + (sumdoi coada)

--piatra foarfeca hartie
--am facut un tip de date
data Alegere = Piatra | Foarfeca | Hartie deriving (Show)
data FinalJoc = Primul | AlDoilea | Egalitate deriving (Show)
joc :: Alegere -> Alegere -> FinalJoc
joc Piatra Foarfeca = Primul
joc Piatra Hartie = AlDoilea
joc Foarfeca Piatra = AlDoilea
joc Foarfeca Hartie = Primul
joc Hartie Piatra = Primul
joc Hartie Foarfeca = AlDoilea
joc _ _ = Egalitate

--list comprehension
divizori n = [x | x <- [1..n], mod n x == 0]
prim' n = (divizori n) == [1,n]
toatePrime n = [x | x <- [1..n], prim' x]

--zip
myzip3Lab [] _ _ = []
myzip3Lab _ [] _ = []
myzip3Lab _ _ [] = []
myzip3Lab (cap1:coada1) (cap2:coada2) (cap3:coada3) = (cap1,cap2,cap3) : (myzip3Lab coada1 coada2 coada3)

myzip3Lab' l1 l2 l3 = 
    let l = zip (zip l1 l2) l3 in
    [(x,y,z) | ((x,y),z) <- l]

--compunere de functii
h x = (x,x)
i (x,y) = x * y
--j = i . h apoi j 4 si da 16

aplicaCu3 f = f 3
--aplicaCu3 j == 9
--(5+) 3 == 8

--exercitii map
op x = if mod x 2 == 0 then div x 2 else x * 3 + 1
ex1Map l = map op l

ex2Map l = map (\x -> x - x * x) l 

--primul element din fiecare pereche
firstEl' l = map fst l
firstEl2 l = map (\(x,_) -> x) l

--suma din fiecare lista din lista
sumElem l = map sum l

--filter conditie lista == [x | x <- lista, conditie]

--par injumatatit, impar dublat
prelucrare2 lista = map (\x -> if mod x 2 == 0 then div x 2 else x * 2) lista

--patratele numerelor de pe pozitii impare
ex3 :: [Integer] -> [Integer]
ex3 l =
  let
    lfilter = filter (\(_,y) -> odd y) (zip l [1..])
  in
  map (\(x,_) -> x * x) lfilter

--functie care adauga un nr la fiecare element dintr-o lista
ex5 lista x = map (+x) lista

