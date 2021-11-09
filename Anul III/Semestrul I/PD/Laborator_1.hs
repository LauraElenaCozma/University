--comanda ghci ne duce in Prelude

---------COMENZI------------
-- :? help
-- :q quit
-- :cd change directory
-- :t type

-- Ex 1
myInt = 555555555555555555555555555555555555
double :: Integer -> Integer
double x = x + x

----- !!!! incarcarea fisierului :l lab1.hs
----- !!!! reload :r

--import Data.List 
-- :m - Data.List eliminarea librariei

-- Ex 2 maximul a doua numere
maxim :: Integer -> Integer -> Integer
maxim x y = if (x > y) then x else y

-- Ex 3 maximul a 3 numere
maxim3 :: Integer -> Integer -> Integer -> Integer
maxim3 x y z = maxim (maxim x y) z

-- Ex 4 maximul a 4 numere
maxim4 :: Integer -> Integer -> Integer -> Integer -> Integer
maxim4 a b c d = 
    let 
        max1 = maxim a b 
        max2 = maxim max1 c
    in
    maxim max2 d

-- Ex 5 Scrieti o functie care testeaza functia maxim4 prin care s ̆a verificat, i ca rezultatul este
--ın relatia >= cu fiecare din cele patru argumente
verificare :: Integer -> Integer -> Integer -> Integer -> Bool
verificare a b c d = 
    let
        max = maxim4 a b c d
    in
    max >= a && max >= b && max >= c && max >= d

-- Ex 6 Suma patratelor a doua numere
sumaPatrate x y = x^2 + y^2

--Ex 7 Functie care intoarce daca parametrul e par sau impar
paritate x = if x `mod` 2 == 0 then "Par" else "Impar"

--Ex 8 Factorialul unui numar
fact 0 = 1
fact n = n * fact (n - 1)

--Ex 9 Functie care verifica daca primul param e > decat dublul celui de-al doilea 
dublu x y = x > (2 * y)