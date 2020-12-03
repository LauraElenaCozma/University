import Data.List
-- FUNCTOR: e generalizarea de la map care merge pe orice fel de tip
-- primeste o cutie de a si o functie de la a la b si returneaza o cutie de b
-- avem fmap

data MyList a = Nil | a ::: (MyList a)

instance Show a => Show (MyList a) where
    show Nil = "[]"
    show (head ::: tail) = (show head) ++ ":" ++ (show tail)
--show (1 ::: (2 ::: Nil))

-- Cu Functor
-- nu mai avem a, avem doar cutia
instance Functor MyList where
    fmap _ Nil = Nil
    fmap f  (head ::: tail) = (f head) ::: (fmap f tail)
-- fmap (+2) (1 ::: (2 ::: Nil))

{-
APPLICATIVE: <*> 
avem o cutie de a
o cutie cu functii f : a -> b si primesti o cutie de b
-}

{-
* tipuri: int, string, maybe char, [int] = [] int  ==> type classes (sunt ca niste interfete)
* -> * myList, [], Maybe constructori de tipuri care au nevoie de un parametru
* -> * -> * (,) are nevoie de 2 tipuri ca sa devina intreg
-}

--facem suma intre oricare 2 elemente din prima lista cu a doua
--[(+)] <*> [1,2,3] <*> [4,5,6]
--[(+2),(3-),(5*)] <*> [1,2,3] -> a bagat mana in cutia cu functii, in cutia cu elemente 
                                --le-a combinat si a avut cutie de b
--g a b = [(+)] <*> a <*> b ==> el se asteapta ca a si b sa fie liste
--f a b = (pure (+)) <*> a <*> b ==> pentru orice tip de cutie
--f (Just 5) (Just 7) => (Just 12)
-- !!! pure a -> cutie de a


-- IMPLEMENTAM APPLICATIVE dar ca la zip nu orice pereche cu orice pereche
instance Applicative MyList where
    pure x = x ::: (pure x)  --ca sa nu ne dea doar primul element ::: []
    Nil <*> _ = Nil
    _ <*> Nil = Nil
    (h1 ::: t1) <*> (h2 ::: t2) = (h1 h2) ::: (t1 <*> t2)

--a = 1 ::: (2 ::: (3 ::: Nil))
--b = 4 ::: (5 ::: (6 ::: Nil))
--f de mai sus 

-- MONADA
{-m e monada <=> e si applicative
m e constructor de tipuri
return: baga a in cutie ca la applicative

>>= (bind)
primeste o cutie de a
f : a-> o cutie de b        returneaza o cutie de b
-}

divizori x = [y | y <- [1..x], x `mod` y == 0]
toti_divizorii lista = [d | x <- lista, d <- divizori x]
-- nu vrem lista de liste, vrem o lista cu toti divizorii
-- lista de liste ar face functorul, monada face doar o lista

head' [] = Nothing
head' (h:_) = Just h


inv 0 = Nothing
inv x = Just (1.0 / x)
-- (return [2,2,3,4]) >>= head' >>= inv ==> Just 0.5
-- cutie de float => cutie de int => cutie de int


data Optional a = None | Some a deriving (Show)

instance Functor Optional where
    fmap _ None = None
    fmap  f (Some a) = Some (f a)

instance Applicative Optional where
    pure x = Some x
    (Some f) <*> (Some x) = Some (f x)
    _ <*> _ = None

instance Monad Optional where
    None >>= _ = None
    (Some x) >>= f = f x

head'' [] = None
head'' (h:_) = Some h

inv' 0 = None
inv' x = Some (1.0/x)

--(return [2,2,3,4]) >>= head'' >>= inv' ===> Some 0.5


--do notation
f cutie = do
    x <- cutie
    let alta_cutie = head' x
    y <- alta_cutie
    z <- inv y
    let t = z * z + z
    let variabila_mea = "Salutare"
    return t

--aduna toate elementele dintr-o cutie cu toate din alta cutie
--toate cutiile din care scoatem trebuie sa fie de acelasi tip, sa aiba acelasi invelis
aduna cutie1 cutie2 = do
    x <- cutie1 --scoatem din cutie
    y <- cutie2
    return (x + y) --bagam iar in cutie

--aduna (Some 4) (Some 6) => Some 10

--toate cutiile din care scoatem trebuie sa fie de acelasi tip, sa aiba acelasi invelis
h cutie = do
    x <- cutie
    y <- [1,2,3,4]
    --z <- (Some 5) nu merge pentru ca some nu e de acelasi tip cu lista
    return x


---------------------- I/O ---------------------------
main = do
    putStrLn "Hello World!" --putStrLn intoarce o cutie, fix de ce avem nevoie la do notation

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


---------- Exercitii laborator -------------
-- Exercitiul 1
-- Primeste un numar n si o secventa de n persoane nume si varsta;
-- afisam persoana cu varsta cea mai mare
citesteNr 0 = return []
citesteNr n = do 
    nume <- getLine
    varsta <- readLn :: (IO Int)
    restul <- citesteNr (n - 1)      -- scoatem tot dintr-o cutie; returneaza un IO
    return ((varsta, nume) : restul) -- bagam iar in cutie
ex1 = do
    n <- readLn :: (IO Int)
    oamenii <- citesteNr n
    let (varsta, nume) = maximum oamenii --facem maximul dupa prima componenta
    putStrLn nume
    print varsta


-- exercitiul 2
--Citire din fisier
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