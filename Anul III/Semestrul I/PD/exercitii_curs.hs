import Data.Char
--ATENTIE: pentru ord avem nevoie de Data.Char

----------------- Curs 3 --------------------
--Aflati lungimea celui mai lung cuvânt care începe cu litera ’c’ dintr-o lista ̆data. 
maxLen lista = foldr max 0 (map (length) (filter (\s -> (head s) == 'c') lista))

----------------- Curs 4 --------------------

f x lista = elem x lista
---- FUNCTIA ELEM

--Rescrierea functiei elem cu ajutor list comprehension
elemComp x lista = foldr (||) False [x == y | y <- lista]
elemCompOr x lista = or [x == y | y <- lista]

--Folosind recursivitate
elemRec x [] = False
elemRec x (h:tail) = (x == h) || (elemRec x tail)

--Folosind HOF
elemHof x lista = foldr (||) False (map (== x) lista)


---- Clasa Eq
--redefinire clasa EqNew
class EqNew a where
    (===) :: a -> a -> Bool
    (/==) :: a -> a -> Bool
    x === y = not (x /== y)

--definim tipul Bool care apartine clasei EqNew
instance EqNew Bool where
    True === True = True
    True === False = False
    False === True = False
    False === False = True
    True /== True = False
    True /== False = True
    False /== True = True
    False /== False = False

--definim tipul Char care apartine clasei EqNew
instance EqNew Char where
    a === b = ord a == ord b
    a /== b = ord a /= ord b

--definim EqNew pentru perechi
--trebuie sa fie definit EqNew pentru tipurile din pereche
instance (EqNew a, EqNew b) => EqNew (a,b) where
    (a,b) === (c,d) = a === c && b === d
    (a,b) /== (c,d) = a /== c || b /== d

--definim EqNew pentru liste
instance EqNew a => EqNew [a] where
    [] === [] = True
    xs === [] = False
    [] === ys = False
    (x:xs) === (y:ys) = (x === y) && (xs === ys)
    [] /== [] = False
    xs /== [] = True
    [] /== ys = True
    (x:xs) /== (y:ys) = (x /== y) || (xs /== ys)
--Apel: ['1','2','3'] === ['1','2','3']

---Extinderea claselor
class (EqNew a) => (OrdNew a) where
    (<<) :: a -> a -> Bool

--implementam ordNew pentru Char pentru teste
instance OrdNew Char where
    a << b = (ord a) < (ord b) 

--OrdNew pentru perechi
instance (OrdNew a, OrdNew b) => OrdNew (a,b) where
    (a,b) << (c,d) = a << c || (a === c && b << d) 
--Apel: ('b','c') << ('c', 'd')


----Construire clase proprii
--O clasa de tipuri pentru date care pot fi afisate
--Similara clasei show
class Visible a where
    toString :: a -> String

--instante ale clasei
instance Visible Char where
    toString a = [a]

instance Visible Bool where
    toString True = "True"
    toString False = "False"

--ATENTIE: cum transformam int in string fara show?
--ATENTIE: cu int nu functioneaza, DAR CU INTEGER DA
instance Visible Integer where
    toString a = show a
--Apel: toString 321

--pentru perechi
instance (Visible a, Visible b) => Visible (a,b) where
    toString (a,b) = "(" ++ (toString a) ++ "," ++ (toString b) ++ ")"

instance (Visible a) => Visible [a] where
    toString [] = "[]"
    toString (x:xs) = "[" ++ showSep x xs ++ "]"
        where
            showSep x [] = toString x  --pentru a afisa valorile din interior fara [ ]
            showSep x (y:xs) = (toString x) ++ "," ++ (showSep y xs) 


------------ Tipuri de date algebrice ----------------

------- Tipuri suma ---------
--definite prin enumerarea alternativelor
data Season = Spring | Summer | Autumn | Winter deriving Show
--Season constructor de tip
--Spring.. constructori de date

succesor Spring = Summer
succesor Summer = Autumn
succesor Autumn = Winter 
succesor Winter = Spring

-------- Tipuri produs ---------

--Tipul punct
data Point a b = Pt a b deriving(Show)
--Point constructor de tip
--Pt constructor de date


----- Accesarea componentelor
--Definim proiectii
pr1 :: Point a b -> a
pr1 (Pt x _) = x
pr2 :: Point a b -> b 
pr2 (Pt _ y) = y

pointFlip (Pt x y) = Pt y x

--Tipul lista
data List a = Nil | Cons a (List a) deriving Show
append :: List a -> List a -> List a 

append Nil ys = ys
append (Cons x xs) ys = Cons x (append xs ys)
--Apel:append (Cons 1 (Cons 2 Nil)) (Cons 3 Nil)

----Tipuri de date algebrice
--ATENTIE: Trebuie neaparat sa contina CONSTRUCTORI
data StrInt = VI Int | VS String deriving(Show)
--Apel: [VI 1, VS "Laura", VI 4] :: [StrInt]


--------------------- Curs 5 ------------------------
-------- Tipul MAYBE --------

--Maybe ca parametru
power :: Maybe Int -> Int -> Int
power Nothing n = 2 ^ n
power (Just m) n = m ^ n
--Apel: power (Just 7) 2 => 49
--Apel: power Nothing 2 => 4

--Maybe ca tip rezultat
divide n 0 = Nothing
divide n m = Just(n `div` m)


--ATENTIE: INSTRUCTIUNEA CASE
right n m = case divide n m of
                Nothing -> 3
                Just r -> r + 3



---Tipul either
--aduna intregii dintr-o lista de int si string
addInts :: [Either Int String] -> Int
addInts [] = 0
addInts (Left x : xs) = x + (addInts xs)
addInts (Right x : xs) = addInts xs
--Apel: addInts [Left 3, Left 1, Right "sa", Left 22, Right "asaf"]

addIntsComp lista = sum [x | Left x <- lista]

addIntsHof lista = foldr (+) 0 (map (\(Left x) -> x) (filter isLeft lista))
            where
                isLeft (Left x) = True
                isLeft _ = False

--concateneaza stringurile dintr-o lista de int si string
addStrs [] = []
addStrs (Left x : xs) = addStrs xs
addStrs (Right x : xs) = x ++ (addStrs xs)
--Apel: addStrs [Left 3, Left 1, Right "sa", Left 22, Right "asaf"]

addStrsComp lista = concat [s | Right s <- lista]

addStrsHof lista = foldr (++) [] (map (\(Right s) -> s) (filter isRight lista))
            where
                isRight (Right x) = True
                isRight _ = False


--------------- Logica Propozitionala --------------------

--------------- Arbori binari de cautare --------------------
data BinaryTree a = Empty | Node (BinaryTree a) a (BinaryTree a)

----Scrieti o functie care determina inaltimea unui arbore
height :: BinaryTree a -> Int
height Empty = 0
height (Node left val right) = 1 + (max (height left) (height right))
--Apel: height (Node (Node Empty 2 Empty) 4 Empty)

----Scrieti o functie care determina parcurgerea in inordine
inord :: BinaryTree a -> [a]
inord Empty = []
inord (Node left val right) = (inord left) ++ [val] ++ (inord right)


-------------- Arbori binari ------------------
data BTree a = Leaf a | NodeB (BTree a) (BTree a)

showBT (Leaf a) = show a
showBT (NodeB l r) = "(" ++ (showBT l) ++ ") , (" ++ (showBT r) ++ ")"

instance (Show a) => Show (BTree a) where
    show = showBT

exTree = NodeB ( NodeB ( Leaf '1' ) ( Leaf 's' ) ) ( Leaf 'q')


-------- Foldr pentru alte tipuri de date ------------

--Pentru BTree

foldTree :: (a -> b -> b) -> b -> BTree a -> b
foldTree f accum (Leaf a) = f a accum
foldTree f accum (NodeB left right) = foldTree f (foldTree f accum right) left

instance Foldable BTree where
    foldr = foldTree

--foldr (\ x accum -> x:accum) [] exTree


----- Pe expresii
data Exp = Lit Int | Add Exp Exp | Mul Exp Exp

evalExp (Lit a) = a
evalExp (Add e1 e2) = (evalExp e1) + (evalExp e2)
evalExp (Mul e1 e2) = (evalExp e1) * (evalExp e2)

expresie1 = Add (Lit 1) (Mul (Lit 3) (Lit 2))

--ATENTIE: in curs e n, nu Lit n, trebuie modificat?
foldExp fLit fAdd fMul (Lit n) = fLit (Lit n)
foldExp fLit fAdd fMul (Add e1 e2) = fAdd v1 v2
                    where
                        v1 = foldExp fLit fAdd fMul e1
                        v2 = foldExp fLit fAdd fMul e2
foldExp fLit fAdd fMul (Mul e1 e2) = fMul v1 v2
                    where
                        v1 = foldExp fLit fAdd fMul e1
                        v2 = foldExp fLit fAdd fMul e2

