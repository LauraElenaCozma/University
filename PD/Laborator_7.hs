import Data.List
import Data.Maybe

---------------MODEL TEST--------------------

--Exercitiul 1
--Scrieti o functie care numara cate propozitii sunt intr-un text dat
--Functie auxiliara sfChr care verifica daca un caracter e sfarsit de propozitie
--sfarsitul propozitiei e marcat prin ., ?, ! si :.

--RECURSIE
sfChr :: Char -> Bool
sfChr c = c == '.' || c == '!' || c == '?' || c == ':'

numProp :: String -> Int
numProp [] = 0
numProp (h:tail) =
    if sfChr h then 1 + (numProp tail)
    else numProp tail

--LIST COMPREHENSION
numPropComp lista = sum [1 | x <- lista, sfChr x]


--Exercitiul 2
--Scrieti o functie liniiN care are ca parametru o matrice de numere ıntregi
--([[Int]]) si un numar intreg n, si verifica daca toate liniile de lungime n din matrice au doar
--elemente strict pozitive.
liniiN :: [[Int]] -> Int -> Bool
liniiN lista n = foldr (\x accum -> accum && (x > 0)) True 
    (map (\row -> minimum row)
    (map (\(len:row) -> row) 
    (filter (\row -> (length row) == (n + 1)) 
    (map (\row -> (length row) : row) lista))))


---V2
liniiN' liste n = 
  let alea = filter (\c -> length c == n) liste in
  filter (\c -> (foldr min 1 c) > 0) alea == alea
--Exercitiul 3
--puncte cu numar variabil de coordonate intregi
--Sa se scrie o instanta a clasei ToFromArb pentru tipul de date Punct astfel ıncat lista
--coordonatelor punctului sa coincida cu frontiera arborelui.
data Punct = Pt [Int] deriving Show

data Arb = Vid | F Int | N Arb Arb deriving Show
class ToFromArb a where
    toArb :: a -> Arb
    fromArb :: Arb -> a


instance ToFromArb Punct where
  toArb (Pt []) = Vid
  toArb (Pt (h:tail)) = 
    let subarb = toArb (Pt tail) in
    (N (F h) subarb)
  fromArb Vid = (Pt [])
  fromArb (F val) = (Pt [val])
  fromArb (N arb1 arb2) = 
    let (Pt st) = fromArb arb1 in
    let (Pt dr) = fromArb arb2 in
    Pt (st ++ dr)

--toArb (Pt [1,2,3])
--fromArb $ N (F 1 ) (N (F 2 ) (N (F 3 ) Vid ) ) :: Punct


---------------------MICRO HASKELL---------------------------------
type Name = String

data  Value  =  VBool Bool
        |VInt Int
        |VFun (Value -> Value)
        |VError
        
data  Hask  = HTrue | HFalse 
        |HIf Hask Hask Hask
        |HLit Int
        |Hask :==: Hask
        |Hask :+:  Hask
    |HVar Name
    |HLam Name Hask  --expresie lambda cu un singur parametru si expresia din
	|Hask :$: Hask
        deriving (Read, Show)
        
infix 4 :==:
infixl 6 :+:
infixl 9 :$:

type  HEnv  =  [(Name, Value)]

showV :: Value -> String
showV (VBool b)   =  show b
showV (VInt i)    =  show i
showV (VFun _)    =  "<function>"
showV (VError)    =  "<error>"

eqV :: Value -> Value -> Bool
eqV (VBool b) (VBool c)    =  b == c
eqV (VInt i) (VInt j)      =  i == j
eqV (VFun _) (VFun _)      =  error "Unknown"
eqV (VError ) (VError)      =  error "Unknown"
eqV _ _               = False

hEval :: Hask -> HEnv -> Value
hEval HTrue r         =  VBool True
hEval HFalse r        =  VBool False

hEval (HIf c d e) r   =
  hif (hEval c r) (hEval d r) (hEval e r)
  where  hif (VBool b) v w  =  if b then v else w
         hif _ _ _ = VError
  
hEval (HLit i) r      =  VInt i

hEval (d :==: e) r     =  heq (hEval d r) (hEval e r)
  where  heq (VInt i) (VInt j) = VBool (i == j)
         heq  _ _ = VError    
  
hEval (d :+: e) r    =  hadd (hEval d r) (hEval e r)
  where  hadd (VInt i) (VInt j) = VInt (i + j)
         hadd _ _  = VError   
  
hEval (HVar x) r      =  fromMaybe VError (lookup  x r)
--facem lookup in env si se uita daca este x in env

hEval (HLam x e) r    =  VFun (\v -> hEval e ((x,v):r))


hEval (d :$: e) r    =  happ (hEval d r) (hEval e r)
  where  happ (VFun f) v  =  f v
         happ _ _ = VError

run :: Hask -> String
run pg = showV (hEval pg [])

h0 =  (HLam "x" (HLam "y" ((HVar "x") :+: (HVar "y")))) 
      :$: (HLit 3)
      :$: (HLit 4)
      


test_h0 = eqV (hEval h0 []) (VInt 7)