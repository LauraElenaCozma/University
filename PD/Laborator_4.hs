data Natural
----------------- FUNCTIA FOLDR -----------------------

---- Exercitiul 1
--Scrieti o functie recursivă care calculează produsul numerelor dintr-o listă.
produsRec :: [Integer] -> Integer
produsRec [] = 1
produsRec (h:lista) = h * (produsRec lista)
--Apel: produsRec [1,2,5,3,4]

--Foldr in locul recursiei
produsFold :: [Integer] -> Integer
produsFold lista = foldr (*) 1 lista

--ATENTIE SE POATE SCRIE: 
produsFold' :: [Integer] -> Integer  --trebuie neaparat
produsFold' = foldr (*) 1


---- Exercitiul 2
--Scrieti o functie recursivă care verifică faptul că 
--toate elementele dintr-o listă sunt True.
andRec :: [Bool] -> Bool
andRec [] = True
andRec (h:lista) = 
    if h == True 
        then andRec lista
        else h              --sau h && andRec lista

--Cu foldr
andFoldr :: [Bool] -> Bool
andFoldr = foldr (&&) True

--Cu foldl
andFoldl :: [Bool] -> Bool
andFoldl = foldl (&&) True


---- Exercitiul 3
--Scrieti o functie recursivă care concatenează o listă de liste.
--FUNCTIA CONCAT: concateneaza mai multe liste consecutive
--Dificultati
concatRec :: [[a]] -> [a]
concatRec [] = []
concatRec (h:lista) = h ++ (concatRec lista)
--Apel: concatRec [[1,2,3],[2,3,4]]

--Cu foldr
concatFoldr :: [[a]] -> [a]
concatFoldr = foldr (++) [] 

--Cu foldl
concatFoldl :: [[a]] -> [a]
concatFoldl = foldl (++) [] 


---- Exercitiul 4
--Scrieti o functie care elimină un caracter dintr-un sir de caractere.
rmChar :: Char -> String -> String
rmChar c [] = []
rmChar c (h:lista) =
    let rest = rmChar c lista in
    if (c == h) 
        then rest
        else h : rest

--o functie care elimina un caracter dintr-un sir de caractere
rmCharRec _ [] = []
rmCharRec c (h:t) = if c == h then rmCharRec c t
                              else h:(rmCharRec c t)
--rmCharRec 'u' "laura"

rmCharComp c lista = [x | x <- lista, x /= c] --sau not(x==c)

rmCharFold c lista = 
    foldr (\x accum -> if x == c then accum else x:accum) [] lista

--Scrieti o functie recursivă care elimină toate caracterele 
--din al doilea argument care se găsesc în primul argument.
-- "abac" "laura" -> iau cate un caracter din sirul 1 si apelez rmChar de caracter
rmCharsRec :: String -> String -> String
rmCharsRec [] s = s
rmCharsRec (h1:s1) s2 = rmCharsRec s1 (rmChar h1 s2)

--cu Foldr
--pornim de la s2 pe care aplicam rmChar pe primul caracter din s1
rmCharsFoldr :: String -> String -> String
rmCharsFoldr s1 s2 = foldr rmChar s2 s1


--stergem toate caracterele din primul care se gasesc in al doilea
contains' c lista = length [x | x <- lista, x == c] > 0 --verifica daca c e in lista
rmCharsFold rele lista = 
    foldr (\x accum -> if contains' x rele then accum else x:accum) [] lista

------------------------------------------- Recapitulare Laborator ----------------------------------------------------

--learnyouahaskell.com

--functie care din [1,2,3,4,5,6] returneaza 1 * 2 + 3 * 4 + 5 * 6
f1 [] = 0
f1 [_] = error "Numar impar de elemente"
f1 (a:b:l) = a * b + (f1 l)


--toate nr prime de la 1 la n cu filter
divizori n = [x | x <- [1..n], mod n x == 0]
prim n = (divizori n) == [1,n]
primele n = filter prim [1..n]

--FOLDR
f2 a l = foldr (+) a l

--simulam filter cu foldr
--foldr cafilter [] [1,2,3,4]
--op primeste un argument din lista si acumulatorul si returneaza rezultatul

--toate nr pare
op elem accum =
    if even elem then elem:accum
                 else accum 
--apel: foldr op [] [1,2,3,4,5,6]

--foldr: verificam daca un element apartine unei liste sau nu
--foldr op False lista
contains x lista = 
    --accum = true daca am gasit elem pana acum si false daca nu
    let op elem accum = if elem == x then True else accum in
    foldr op False lista

--foldl (-) 2 [5,8,10]
--2 - 5 = -3 - 8 = -11 - 10 = -21
--foldr (-) 2 [5,8,10] la stanga lui - e elem din lista
--10 - 2 = 8 
-- 8 - 8 = 0
-- 5 - 0 = 5

--foldr: suma patratelor
sumapatrat elem accum = elem^2 + accum
--Apel: foldr sumapatrat 0 [1,2,3]
--recursiv
sumapatrat' [] = 0
sumapatrat' (elem:tail) = elem^2 + (sumapatrat' tail)

--foldr: la numerele impare sa adun jumatate si la numerele pare sa adun dublu
-- dupa care facem suma
op' elem accum = if odd elem then 2 * elem + accum
                             else elem `div` 2 + accum
h lista = foldr op' 0 lista


--suma lungimilor listelor din liste
sumaLengthRec [] = 0
sumaLengthRec (lista:tail) = (length lista) + (sumaLengthRec tail)
--Apel: sumaLengthRec [[1,2,3],[2,3]]
sumaLengthFold lista =
    --op :: [a] -> Int -> Int 
    let op elem accum = (length elem) + accum in
    foldr op 0 lista
--puteam face si un map inainte si sa dam foldr doar cu +
sumaLengthFold' lista = 
    let nou = map length lista in
    foldr (+) 0 nou


--foldr (:) [] [1,2,3,4] => [1,2,3,4] 1:2:3:4:[]
reverse' lista = 
    let op elem accum = elem:accum in
    foldr op [] lista
--cu foldl
reverse'' lista = 
    let op elem accum = accum:elem in
    foldl op [] lista


--simulam map cu foldr
map' functie lista = 
    let operator elem accum = (functie elem):accum in
    foldr operator [] lista
--apel: map' (+2) [1,2,3,4,5]

--simulam filter cu foldr
filter' functie lista = 
    let operator elem accum = if (functie elem) then elem:accum else accum in
    foldr operator [] lista


--EVALUARE LENESA
contains'' _ [] = False
contains'' x (h:t) = if h == x then True else contains x t
--dureaza putin deoarece dupa ce il gaseste pe 100 nu mai continua