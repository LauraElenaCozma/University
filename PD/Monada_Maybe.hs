----------- MONADE -------------

-- FUNCTOR: e generalizarea de la map care merge pe orice fel de tip
-- primeste o cutie de a si o functie de la a la b si returneaza o cutie de b
-- avem fmap

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

-- MONADA
{-m e monada <=> e si applicative
m e constructor de tipuri
return: baga a in cutie ca la applicative

>>= (bind)
primeste o cutie de a
f : a-> o cutie de b        returneaza o cutie de b
-}

data Lista a = Gol | a ::: (Lista a)
infixr :::
instance Show a => Show (Lista a) where
    show Gol = "[]"
    show (head ::: tail) = (show head) ++ ":" ++ (show tail)

instance Functor Lista where
    fmap _ Gol = Gol
    fmap f (head ::: tail) = (f head) ::: (fmap f tail)

--fmap (+2) (1:::2:::3:::4:::Gol)
instance Applicative Lista where
    pure x = x ::: (pure x) --ca sa faca lista infinata si sa le concatenam pe taote
    Gol <*> _ = Gol
    _ <*> Gol = Gol
    (headf ::: tailf) <*> (heade ::: taile) = 
        (headf heade) ::: (tailf <*> taile)

--- a = (+2):::(1-):::(*2):::Gol
--- *Main> b =  (1:::2:::3:::4:::Gol)                          
--- *Main> a <*> b
--- 3:-1:6:[]

instance Monad Lista where
    Gol >>= _ = Gol
    (head ::: tail) >>= op =
        let alta_cutie = op head in
        case alta_cutie of Gol       -> tail >>= op
                           (h ::: _) -> h ::: (tail >>= op)



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


{- Monada Maybe este definita in GHC.Base 

instance Monad Maybe where
  return = Just
  Just va  >>= k   = k va
  Nothing >>= _   = Nothing


instance Applicative Maybe where
  pure = return
  mf <*> ma = do
    f <- mf
    va <- ma
    return (f va)       

instance Functor Maybe where              
  fmap f ma = pure f <*> ma   
-}

--Scoti din cutie maxim un element sau 0
{--*Main> Nothing >> Nothing
Nothing
*Main> Nothing >> Just 3
Nothing
*Main> Just 3 >> Nothing
Nothing
*Main> Just 3 >> Just 6
Just 6
*Main> [1,2,3] >> [4,5,6]
[4,5,6,4,5,6,4,5,6]--}

--1. Definiti operatorul de compunere a functiilor îmbogătite
(<=<) :: (a -> Maybe b) -> (c -> Maybe a) -> c -> Maybe b
--f <=< g = (\ x -> g x >>= f)
-- Cu scriere do
(f <=< g) x = do
    a <- g x
    f a

-- 1.1 Creat, i singuri exemple prin care să înt,eleget, i funct, ionarea acestui operator.
f x = if (x > 0) then Just (x * 2) else Nothing
g x = if (x > 0) then Just (x + 2) else Nothing
h = f <=< g
--Apel: h 10

f1 :: String -> Maybe Int
f1 x = if (length x) > 10 then Just (length x) else Nothing

g1 :: Int -> Maybe String
g1 x = if x > 0 then Just $ concat $replicate x "ab" else Nothing
-- Apel: (g1 <=< f1) "anamarianegura": mai intai aplicam f1 pe string si dupa g1 pe lungimea lui
-- Just "abababababababababababababab"

f2, f3, f4 :: Int -> Maybe Int
f2 x = if x > 10 then Just $ x * x else Nothing
f3 x = if x > 15 then Just $ x + x else Nothing
f4 x = if x > 20 then Just $ x * x * x else Nothing

-- 1.2 Definiti proprietatea
asoc :: (Int -> Maybe Int) -> (Int -> Maybe Int) -> (Int -> Maybe Int) -> Int -> Bool
asoc f g h x = (h <=< (g <=< f) $ x) == ((h <=< g) <=< f $ x)
-- Apel: asoc f2 f3 f4 4
-- True

-- Exercitiul 2
-- Functie care verifica daca un numar este pozitiv
pos :: Int -> Bool
pos  x = if (x>=0) then True else False

-- Ia numarul din monada si returneaza Just (true daca e pozitiv sau false altfel)
foo :: Maybe Int ->  Maybe Bool 
foo  mx =  mx  >>= (\x -> Just (pos x))  
  
-- foo folosind notatia do
fooDo :: Maybe Int ->  Maybe Bool 
fooDo mx = do
    x <- mx
    return (pos x)


-- 3. Vrem să definim o functie care adună două valori de tip Maybe Int
addM :: Maybe Int -> Maybe Int -> Maybe Int  
addM Nothing _ = Nothing
addM _ Nothing = Nothing
addM (Just x) (Just y) = Just (x + y)

-- 3.2 Definiti addM folosind operatii monadice si notatia do.
addMonad :: Maybe Int -> Maybe Int -> Maybe Int 
addMonad mx my = mx >>= (\x -> my >>= (\y -> return (x + y)))

addDo :: Maybe Int -> Maybe Int -> Maybe Int 
addDo mx my = do
    x <- mx
    y <- my
    return (x + y)
--addM (Just 4) (Just 3)


-------- Notatia DO
-- 4. Să se treacă în notatia do urmatoarele functii:
cartesian_product xs ys = xs >>= (\x -> (ys >>= (\y -> return (x, y))))
-- Apel: cartesian_product (Just 4) (Just 2)
-- Just (4,2)

-- Apel: cartesian_product [1,2,4,5] [4,1]    
-- [(1,4),(1,1),(2,4),(2,1),(4,4),(4,1),(5,4),(5,1)]

cartesian_product_do xs ys = do
    x <- xs
    y <- ys
    return (x, y)

-- functia 2
prod f xs ys = [f x y | x <- xs, y<-ys]
-- Apel: prod (\x y -> (show x) ++ " " ++ (show y)) [1, 2, 3] [6, 7]
-- ["1 6","1 7","2 6","2 7","3 6","3 7"]

prodMonad f xs ys = xs >>= (\x -> ys >>= (\y -> return (f x y)))
prodDo f xs ys = do
    x <- xs
    y <- ys
    return (f x y)

-- functia 3
myGetLine :: IO String
myGetLine = getChar >>= \x ->
    if x == '\n' then
        return []
    else
        myGetLine >>= \xs -> return (x:xs)

--ATENTIE!!
myGetLineDo = do
    x <- getChar
    if x == '\n' then
        return []
    else
        let rest = myGetLineDo in
        do
        xs <- rest
        return (x:xs)

-- Sa se treaca in notatia de secventiere
prelNo noin = sqrt noin
ioNumber = do
    noin <- readLn :: IO Float
    putStrLn $ "Intrare\n" ++ (show noin)
    let noout = prelNo noin
    putStrLn $ "Iesire"
    print noout

