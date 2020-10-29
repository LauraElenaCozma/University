fact n = if (n == 0) then 1
         else n * fact (n - 1)


firstEl l = [x | (x, y) <- l]

sumList list = [sum l | l <- list]

prel2 list = 
        let
            prelucrare x = if mod x 2 == 0 then x `div` 2
                           else (x * 2)
        in [prelucrare x | x <- list]

-- suma elementelor pare
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
data Alegere = Piatra | Foarfeca | Hartie 
data FinalJoc = Primul | AlDoilea | Egalitate
--                       nu functioneaza
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
prim n = (divizori n) == [1,n]
toatePrime n = [x | x <- [1..n], prim x]

--zip
myzip3 [] _ _ = []
myzip3 _ [] _ = []
myzip3 _ _ [] = []
myzip3 (cap1:coada1) (cap2:coada2) (cap3:coada3) = (cap1,cap2,cap3) : (myzip3 coada1 coada2 coada3)

myzip3' l1 l2 l3 = 
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