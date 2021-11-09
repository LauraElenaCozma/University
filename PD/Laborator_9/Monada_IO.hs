import Data.Char
-- LearnYouAHaskell

ex1 = do
    putStrLn "Hello, what's your name?"
    name <- getLine
    putStrLn ("Hey " ++ name ++ ", you rock!")

-- Exercitii curs
--- Citeste un caracter
main :: IO ()
main = do
    c <- getChar 
    putChar c

--- Citeste o linie folosind getChar; recursiv
myGetLine :: IO String
myGetLine = do
    c <- getChar
    if c == '\n' then return ""
    else
        do
        rest <- myGetLine
        return (c:rest)

myGetLineSecv :: IO String
myGetLineSecv = getChar >>= (\c -> if c == '\n' then 
                                                    return ""
                                                else myGetLineSecv >>= (\rest -> return (c:rest)))
-- Apel: myGetLineSecv

--afisarea recursiva a unui sir
putStrRec :: String -> IO ()
putStrRec [] = return () -- ATENTIE: () nu ""
putStrRec (a:s) = do
    putChar a
    putStrRec s

--- Afisarea unui nr intreg
showInteger :: Int -> IO ()
showInteger n = putStr (show n)

showPlusZece n = putStr (show (n + 10))

--- Citim un intreg de la tastatura dupa care aplicam functia showPlusZece

citesteSiAdunaZece :: IO ()
citesteSiAdunaZece = fmap read getLine >>= showPlusZece

-- Citeste doua numere si intoarce suma lor
citesteSiSuma :: IO Integer
citesteSiSuma = fmap read getLine >>= 
                    (\x -> fmap read getLine >>= \y -> return (x + y))


-- Citeste si suma in varianta do

citesteSiSumaDo = do
    x <- getLine
    y <- getLine
    return ((read x) + (read y))

-- Citeste si afiseaza mesaje in acelasi bloc
citesteSiAfiseaza = do
    putStrLn "Introduceti numele: "
    nume <- getLine
    putStrLn $ "Buna ziua " ++ nume
    putStrLn "Introduceti doua numere: "
    x <- fmap read getLine
    y <- fmap read getLine
    let suma = x + y
    putStrLn ("Suma este: " ++ (show suma))
    -- return suma: se afiseaza implicit suma

--- Citeste din fisier si afiseaza la consola continutul
cat path = do
    continut <- readFile path
    putStr continut
-- Apel: cat "ex_citire.txt"

--- Citeste din fisier si converteste in majuscule
toUpperFile path1 path2= do
    continut <- readFile path1
    let upperContinut = map toUpper continut
    writeFile path2 upperContinut


---- ATENTIE: SUMA NUMERELOR DINTR-UN FISIER

sumaFisier path = do
    continut <- readFile path
    let linii = lines continut   --fiecare linie e un string
    putStrLn (show linii)
    let cuvinte = map words linii   -- fiecare string linie se transforma intr-o lista de stringuri
    putStrLn ("Cuvinte" ++ (show cuvinte))
    let listaCuv = concat cuvinte   --pune toate numerele intr-o lista
    putStrLn ("Cuvinte" ++ (show listaCuv))
    let numere = map read listaCuv  --transforma numerele din string in int
    putStrLn ("Numere" ++ (show numere))
    return (sum numere)


--- Laborator

--- Exemplul 1
--- Citeste un sir de la tastatura si afiseaza sirul dupa prelucrare
prelStr strin = map toUpper strin

citesteSiPrel = do
    sir <- getLine -- !! NEAPARAT PT CITIRE DE STRING
    let sirPrel = prelStr sir
    putStrLn sirPrel

citesteSiPrelSecv = getLine >>= (\sir -> let sirPrel = prelStr sir in putStrLn sirPrel)

--- Exemplul 2
--- Citeste de la tastatura un nr si il afis dupa rpelucrare
prelNo noin = sqrt noin

citesteSiPrelNr = do
    nr <- readLn :: IO Double
    let nrPrel = prelNo nr 
    putStrLn (show nrPrel)

--- Varianta cu secventiere

citesteSiPrelNrSecv = (readLn :: IO Double) >>= (\nr -> let nrPrel = prelNo nr in putStrLn (show nrPrel))


--- Exercitiul 1
-- Citeste un nr n si o secv de n persoane (numele si varsta)
-- Sa se afiseze persoana sau persoanele cu varsta cea mai mare

data Persoana n v= Persoana {name :: String, age :: Int}

maximVarstePersoane 0 lnume vmax = do
    putStrLn ("Persoanele cu varsta maxima de " ++ (show vmax) ++ " sunt " ++ (show lnume))
maximVarstePersoane n lnume vmax = do
    putStrLn "Introdu numele"
    nume <- getLine
    putStrLn "Introdu varsta"
    age <- readLn :: IO Integer
    putStrLn ("Nume: " ++ nume ++ " Varsta: " ++ (show age))
    if age > vmax then maximVarstePersoane (n - 1) [nume] age
    else 
        if age == vmax 
            then maximVarstePersoane (n - 1) (nume:lnume) age
        else maximVarstePersoane (n - 1) lnume vmax

citesteNrPersoane = do
    n <- readLn :: IO Integer
    putStrLn ("Trebuie sa introduci datele a " ++ show n ++ " persoane")
    maximVarstePersoane n [] 0

--Exercit, iul 2
--Aceeas, i cerint,ă ca mai sus, dar datele se citesc dintr-un fis, ier de intrare, în care
--fiecare linie cont, ine informat, ia asociată unei persoane, numele si varsta fiind
--separate prin vigulă (vedet, i fis, ierul ex2.in).
--Indicat, ie: pentru a separa numele de varsta puteti folosi funct, ia splitOn din
--modulul Data.List.Split.

--nu functioneaza 
{-mysplit linie s = [s] --punem ultimul caracter ramas
mysplit (c:cs) s 
    | c == ',' = [s] ++ mysplit cs ""
    | otherwise = mysplit cs (s ++ [c])
persDinFisier = do
    continut <- readFile "ex2.in"
    let linii = lines continut
    --let cuvinte = map (splitOn "," linii)
    --let cuvinteConcat = concat cuvinte
    putStrLn (show linii)-}
--split manual
aux [] [] elem = []
aux buffer [] elem = [buffer]
aux buffer (head:tail) elem = if elem == head 
                                            then buffer : (aux [] tail elem)
                                            else aux (buffer ++ [head]) tail elem
splitOn lista elem = aux [] lista elem

ex2 = do
    date <- readFile "ex2.in"
    let linii = splitOn date '\n'
    let oameni = map (\linie -> let [nume, varsta] = splitOn linie ',' in ((read varsta) :: Int, nume)) linii
    let (varsta, nume) = maximum oameni
    putStrLn nume

-- Exercitiul 3
--a) Să se scrie o funct, ie care cites, te de la tastatură un număr intreg si verifică
--dacă acesta este palindrom. Funct, ia afis,eaza un mesaj corespunzător.
reversal :: Integral a => a -> a
reversal = go 0
  where go a 0 = a
        go a b = let (q,r) = b `quotRem` 10 in go (a*10 + r) q

checkPal nr = reversal nr == nr
ioPalindrom = do
    nr <- readLn :: IO Int
    putStrLn (show (checkPal nr))


--b) Folosind funct, ia de la a) să se scrie o funct, ie care are ca parametru un nr
--intreg n s, i citeste n numere de la tastatura, verificând daca acestea sunt
--numere palindrom.
ioPal 1 = ioPalindrom
ioPal n = do
    ioPalindrom
    ioPal (n - 1) 

ioMaiMultePalindroame = do
    nrPali <- readLn :: IO Int
    ioPal nrPali

--Citim 2 linii, si afisam suma lor
citeste = do
    linia1 <- getLine
    linia2 <- getLine
    let x = (read linia1) :: Int
    let y = (read linia2) :: Int
    print (x + y)

--cu readLn
citeste' = do
    x <- readLn
    y <- readLn
    print (x + y)

--folosind un plan intermediar
--plan intermediar nu se executa daca nu il apelam
citeste'' = do
    x <- readLn
    let plan_intermediar = do
        z <- readLn
        t <- readLn
        u <- readLn
        return (z + t + u)
    y <- readLn
    z <- plan_intermediar
    print (x + y + z)


-- Citeste o matrice de la tastatura
-- Fiecare element e pe o linie
citeste_linie 0 = return []
citeste_linie m = do
    x <- readLn :: (IO Int)
    restul <- citeste_linie (m - 1)
    return (x : restul)

citeste_matrice 0 _ = return []
citeste_matrice n m = do
    linie <- citeste_linie m
    restul_liniilor <- citeste_matrice (n - 1) m
    return (linie : restul_liniilor)

exMatrice = do
    n <- readLn :: (IO Int)
    m <- readLn :: (IO Int)
    matrice <- citeste_matrice n m
    print matrice


--citim de pe un singur rand
citeste_rand = do
    linie <- getLine
    let elems = words linie
    return ((map read elems) :: [Int])

citeste_matrice' 0 = return []
citeste_matrice' n = do
    rand <- citeste_rand
    restul <- citeste_matrice' (n - 1)
    return (rand:restul)

exMatrice' = do
    [n,m] <- citeste_rand
    matrice <- citeste_matrice' n
    print matrice

{-
exMatrice'
3 3
1 2 3
4 5 6
7 8 9-}