import Data.Char
import Data.List
---------------------------------------------RECAPITULARE--------------------------------------------------------
--RECURSIE
--Functie care calculeaza suma elementelor de pe poz impare in prima pereche si de pe pozitii pare in a doua
sum2 [] = (0, 0)
sum2 [x] = (x, 0)
sum2 (a:b:l) = 
    let (x, y) = sum2 l in
    (a + x, b + y)

sum2' [] = (0, 0)
sum2' [x] = (x, 0)
sum2' (a:b:l) = 
    let x = sum2' l in
    (a + (fst x), b + (snd x))

--LIST COMPREHENSION
--returneazaa o lista cu diferenta perechilor consecutive 
diff [] = []
diff l =
    let l2 = zip l (tail l) in
    [x - y | (x, y) <- l2]

diff' l = [x - y | (x, y) <- zip (tail l) l]

--MAP SI FILTER
--toti divizorii unui nr cu map si filter
divizori n = filter (\x -> n `mod` x == 0) [1..n]

--suma patratelor divizorilor
sumdivsquare n = sum (map (^2) (divizori n))

--FOLDR SI FOLDL
--sumdivsquarer cu foldr
sumdivsquarer n = 
    foldr (\elem accum -> accum + elem^2) 0 (divizori n)

--se schimba ordinea elem si accum avand in vedere ca
sumdivsquarel n = 
    foldl (\accum elem -> accum + elem^2) 0 (divizori n)

------------------------------------------------LABORATOR 5 ----------------------------------------------------
----------------------------------------------  Cifrul Cezar  -----------------------------------------------------
--1 Primele n caractere din string se adauga la final
rotate :: Int -> [Char] -> [Char]
--drop 5 [1,2,3,4,5,6,7,8] => le ia pe toate mai putin primele 5
--take 5 l => ia primele 5 elemente
rotate n l = 
    if n < 0 || n > (length l) 
        then error "argument invalid"
        else
            (drop n l) ++ (take n l)

--2
prop_rotate :: Int -> String -> Bool
prop_rotate k str = rotate (l - m) (rotate m str) == str
                        where l = length str    
                              m = if l == 0 then 0 else k `mod` l

--3
makeKey n = zip ['A'..'Z'] (rotate n ['A'..'Z'])
--4
lookUp c cifru = 
    let l = filter (\(x,y) -> x == c) cifru in
    if l == [] then c else snd (head l)
--lookUp 'Y' (makeKey 5)
--5
--codifica un singur caracter
encipher n c = 
    let cifru = makeKey n in
    lookUp c cifru

--6 uniformizam mesajul

normalize text = 
    let t2 = map toUpper text in
    filter (\c -> (isDigit c) || (isUpper c)) t2 

--7
encipherStr n text = 
    [encipher n x| x <- normalize text]

--8
reverseKey l = [(b, a) | (a, b) <- l]

--9
decipher :: Int -> Char -> Char
decipher n c =
    let cifru = reverseKey (makeKey n) in
    lookUp c cifru

--10
decipherStr :: Int -> String -> String
decipherStr n text =
    let t2 = filter (\c -> isUpper c || isDigit c || c == ' ') text in
    [decipher n x | x <- t2]


--------------------------------------------------
data Alegere = Piatra | Hartie | Foarfece deriving(Show)
--un fel de enum

--constructori la liste: [] si operatorul :
--constructori la int: numerele(-1,0,1,2,3...)
--constructori la pereche: (,)

--DEFINIRE OPERATORI
a % b = mod a b
a // b = div a b
a +-+ b = a^2 + b ^2

data Figura = Cerc Float | Patrat Float | Dreptunghi Float Float deriving(Show)
--constructorii sunt Cerc, Patrat si Dreptunghi
aria (Cerc raza) = raza^2 * pi 
aria (Patrat latura) = latura^2
aria (Dreptunghi lungime latime) = lungime * latime

data Sex = Feminin | Masculin | Altele String
--cum e definita lista haskell
data Lista = Goala | Append Int Lista
sum' Goala = 0
sum' (Append x tail) = x + (sum' tail)
--Lista nu e un tip
--sum' (Append 1 (Append 2 Goala))
