------------------ Restanta 2019 -------------------
-- Fiind data o lista de perechi de nr intregi determina daca toate perechile de numere pare
-- au produsul elementelor mai mare decat 10
prodPar [] = True
prodPar ((a,b):lista) = if ((even a) && (even b) && (a * b <= 10)) 
                                then False
                        else prodPar lista

--prodPar [(10,12), (2,3), (2,6), (5,1), (13,20)]

--List comp
prodParComp lista = and [result | (a,b) <- lista, even a, even b, let result = a * b > 10]

--HOF
prodParHof lista = foldr (&&) True (map (\(a,b) -> a * b > 10) (filter valid lista))
                where
                    valid (a,b) = even a && even b


--Inlocuieste element din lista cu produs elemente pare care apar inaintea lui
prodInainteAux [] prodAnt = []
prodInainteAux (x:xs) prodAnt = if (even x) 
                                    then
                                        prodAnt : (prodInainteAux xs (prodAnt * x))
                                    else 
                                        prodAnt : (prodInainteAux xs prodAnt)

prodInainte lista = prodInainteAux lista 1
--Apel: prodInainte [2,6,-3,18,-7,10] -> [1,2,12,12,216,216]
--Apel: prodInainte [-3,6,1,-6,9,18] -> [1,1,6,6,-36,-36]
--Apel: prodInainte [5,-2,-6,7] -> [1,1,-2,12]



--Se da tipul parametrizat de date al arborilor binari cu info doar pe frunze
--Drumul e True daca e la stanga, false la dreapta
--sa se scrie o functie encoding care intoarce o lista de perechi formate
--din elementele continute in frunze si codificarea lor
data Binar a = Leaf a | Node (Binar a) (Binar a) deriving(Show)
tree = (Node (Node (Leaf 3) (Leaf 4)) (Node (Node (Leaf 1) (Leaf 2)) (Leaf 5)))
encoding' (Leaf a) drum = [(a, drum)]
encoding' (Node st dr) drum =
            encoding' st (True:drum) ++ encoding' dr (False:drum)

encoding t = encoding' t []


--------------------- Examen 10 Februarie 2019 ---------------------------

--Combina alternativ 2 liste
combina [] _ = []
combina _ [] = []
combina (x:xs) (y:ys) = x : y : (combina xs ys)
--Apel: combina [1,3,5,7,9] [2,4,6]
--Apel: combina "ana" "mere"

--Folosind list comprehension 
--ATENTIE: cum sa combini 2 valori in list comprehension
combinaComp lista1 lista2 = [ val | (x,y) <- zip lista1 lista2, val <- [x, y] ]
--Folosind HOF
combinaHof lista1 lista2 = foldr (\(a,b) accum -> a:b:accum) [] (zip lista1 lista2)


------------------------------ Model Examen------------------------------------
--------------------------Operatii pe numere mari------------------------------
type Cifra = Int
type Numar = [Cifra]
--Ex 1a--
--Adaugam un nr de zerouri in fata numarului
lungimePlus :: Numar -> Int -> Numar
lungimePlus numar 0 = numar
lungimePlus numar z = lungimePlus (0 : numar) (z - 1)

--Ex 1b--
--aduce 2 liste la aceeasi lungime
normalizeazaLungime :: (Numar, Numar) -> (Numar, Numar)
normalizeazaLungime (l1, l2) =
    let 
        x1 = length l1
        x2 = length l2
        maxim = max x1 x2
    in
    (lungimePlus l1 (maxim - x1), lungimePlus l2 (maxim - x2))


--Ex 2--
--Veridica daca 2 nr de lungimi egale nr 1 <= nr 2
lteN [] [] = True 
lteN (h1:t1) (h2:t2) 
    | h1 < h2 = True
    | h1 > h2 = False
    | otherwise = lteN t1 t2

--Verifica daca nr 1 <= nr 2 chiar dca nu sunt egale ca lungime
lte :: Numar -> Numar -> Bool
lte a b = 
    let (x,y) = normalizeazaLungime (a,b) in
    lteN x y

--Transforma un numar de la lista la numar
numar :: Numar -> Integer
numar lista = 
    let lista_cu_indici = zip (reverse[0..((length lista) - 1)]) lista in
    foldr (\(puterea, x) accum -> accum + (toInteger x) * 10^puterea) 0 lista_cu_indici

--v2 mai usor rasucim lista
numar' lista = foldr (\x accum -> accum * 10 + x) 0 (reverse lista)

-----Adunarea a doua numere mari------
plusAux :: Numar -> Numar -> (Numar, Int)
plusAux [] [] = ([],0)
plusAux (h1:t1) (h2:t2) =
    let 
        (rezultat, rest) = plusAux t1 t2 
        acum = h1 + h2 + rest
    in
    if acum < 10 then
        (acum:rezultat, 0)
    else
        ((acum `mod` 10):rezultat, 1)

plus :: Numar -> Numar -> Numar
plus a b =
    let 
        (x, y) =normalizeazaLungime (a, b)
        (rezultat, rest) = plusAux x y
    in
    if rest == 1 
        then rest:rezultat
        else rezultat 

-----Inmultirea unui numar(tip lista) cu o cifra

mulC :: Cifra -> Numar -> Numar
mulC cifra numar =
    let (rezultat, rest) = foldr (\x (rezultat, rest) ->   --foldr acum o sa ne intoarca o pereche
                                    let acum = rest + cifra * x in 
                                    ((acum `mod` 10):rezultat,(acum `div` 10))
                                    ) ([],0) numar in   
    if rest > 0 then
        rest:rezultat
    else
        rezultat 
--apel: mulC 9 [9,9]