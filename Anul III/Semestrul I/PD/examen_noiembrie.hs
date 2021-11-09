import Data.Char
--NU UITA DE PROTOTIPUL FUNCTIEI

--Sa se scrie o functie care pentru un sir de caractere calculeaza suma codificarilor caracterelor din sir folosind urmatoarea codificare:

--Caracterul e vocala => 1

--Caracterul e consoana => 2

--Caracterul e cifra => 3

--Orice altceva => -1
codifica :: Num a => [Char] -> a
codifica lista = sum [cod x | x <- lista]
    where
        cod x = if elem x "AEIOUaeiou"                --daca e vocala
                    then 1
                else if (isAlpha x) && (not (elem x "AEIOUaeiou")) --daca e consoana
                    then 2
                else if isDigit x                     --daca e cifra
                    then 3
                else -1                               --orice altceva

--2 + 2 + 1 + 2 - 1 + 1 + 2 - 1 + 1 + 2 + 1 + 2 + 2 + 2 + 1 - 1 + 2 + 1 + 2 + 2 + 1 + 2 - 1 - 1 + 3 - 1)

--Sa se scrie o functie, care primeste ca parametru un cuvant, o lista de siruri de caractere si un nr intreg n 
--si verifica daca toate sirurile din lista care au ca prefix cuvantul dat, au lungimea mai mare decat n.

--Rezolvati aceasta problema folosind functii de nivel inalt (fara recursie si descrieri de liste).

--Pentru punctaj maxim trebuie sa scrieti prototipurile functiilor.
--selectam numai cuvintele care il au ca prefix pe cuvant
--mapam cuvintele in True daca au lungimea > n sau False altfel
--facem && intre valori cu foldr
prefix :: Eq a => [a] -> [[a]] -> Int -> Bool
prefix cuvant lista n = foldr (&&) True (map (\c -> length c > n) (filter (\c -> take (length cuvant) c == cuvant) lista))

--prefix "an" ["andiva", "anaf", "anotimp", "caiac", "amar"] 5
--prefix "an" ["andiva", "anaf", "anotimp", "caiac", "amar"] 3


data Enciclopedie = Intrare String String | Lista String [Enciclopedie] deriving Show

enc1 = Lista "animal"[Lista "mamifer"[Intrare "elefant" "acesta e un elefant", Intrare "caine" "acesta este un caine", Intrare "pisica" "aceasta este o pisica"], Intrare "animale domestice" "definitie"]

enc2 = Lista "Animal"[Lista "Mamifer"[Intrare "Elefant" "acesta e un elefant",Intrare "caIne" "acesta este un caine",Intrare "piSIca" "aceasta este o pisica"],Intrare "animale domestice" "definitie"]

enc3 = Lista "animal"[Lista "mamifer"[Intrare "elefant" "Acesta e un Elefant", Intrare "caine" "acesta este un caine", Intrare "pisica" "aceasta este o pisica"], Intrare "animale Domestice" "definitie"]

enc4 = Lista "animal"[Lista "mamifer"[Intrare "pisica" "aceasta este o pisica",Intrare "elefant" "acesta e un elefant", Intrare "caine" "acesta este un caine"], Intrare "animale domestice" "definitie"]


--a) Sa se scrie o functie care numara cate intrari sunt intr-o enciclopedie data ca parametru. 
nr :: Num p => Enciclopedie -> p
nr (Intrare _ _) = 1                                    
nr (Lista _ []) = 0
nr (Lista n (h:tail)) = (nr h) + (nr (Lista n tail))

--b) Sa se faca instanta a clasei Eq pentru tipul de date Enciclopedie, astfel incat sa se verifice egalitatea dintre doua enciclopedii 
--comparand componentele lor in ordinea in care apar. Titlurile intrarilor si ale listelor sunt sunt verificate fara a tine cont de litere mari sau mici

--b)
--functie care imi transforma un sir de caractere in litere mari pentru a compara indiferent de litere mari si mici
toUpperString :: [Char] -> [Char]
toUpperString s = map toUpper s

--doua intrari sunt egale daca au numele egale indiferent de litere mari si mici, iar descrierile sunt egale
--rezultatul e False daca una din listele de enciclopedii se termina mai devreme
instance Eq Enciclopedie where
    (Intrare x1 y1) == (Intrare x2 y2) = (toUpperString x1) == (toUpperString x2) && y1 == y2
    (Lista n1 []) == (Lista n2 []) = (toUpperString n1) == (toUpperString n2)
    (Lista _ []) == (Lista _ (y:ys)) = False
    (Lista _ (x:xs)) == (Lista _ []) = False
    (Lista n1 (x:xs)) == (Lista n2 (y:ys)) = (toUpperString n1) == (toUpperString n2) && x == y && (Lista n1 xs) == (Lista n2 ys)

enc5 = Intrare "pisica" "aceasta este o pisica"
enc6 = Intrare "pisica" "Aceasta estE eo pisica"


f [] = [[]]
f (x:xs) = (x:xs) : (f xs)