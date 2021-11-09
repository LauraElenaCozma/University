import Data.Char
import Data.List (nub)
import Data.Maybe (fromJust)
--import Test.QuickCheck EROARE LA IMPORT??

--data Figura = Cerc Float | Patrat Float | Dreptunghi Float Float
--data Figura a b = Cerc a | Patrat b | Dreptunghi b b
--apel: [Cerc (2::Int), Patrat (3.5 :: Double)]
--aria (Cerc raza) = raza^2 * pi
--aria (Patrat latura) = latura^2
--aria (Dreptunghi lat lung) = lat * lung
---trebuie apelat cu paranteze!!! altfel ar fi aria cu 2 parametrii


---ceva cu litera mare e constructor; nu merge cu litera mica
--data Expr = Numar Int | Expr :+: Expr | Expr :*: Expr
--il transformam pentru a merge 
--Expr = Type Constructor
--Numar = data Constructor
data Expr a = Numar a | (Expr a) :+: (Expr a) | (Expr a) :*: (Expr a)

--data Expr a = Numar a | Expr :+: Expr | Expr :*: Expr
--ERROR: Expecting one more argument to `Expr' pentru ca expr nu e tip acum
--Expr nu e tip, Expr a e tip
------ Evaluare de expresii ----------
--a = (Numar 5) :+: ((Numar 6) :*: (Numar 7))

--original eval :: Expr -> Int
--acum :: Num a(de la +, *) => Expr a -> a
e = (Numar 5) :+: (Numar 10)
evall (Numar x) = x
evall (x :+: y) = (evall x) + (evall y)
evall (x :*: y) = (evall x) * (evall y)

-------Ex 2------------
--Sa punem numerele din expresie intr-o lista
numere (Numar x) = [x]
numere (x :+: y) = (numere x) ++ (numere y)
numere (x :*: y) = (numere x) ++ (numere y)



-----------------------------------------LABORATOR 6-------------------------------------------

data Fruct = Mar String Bool | Portocala String Int deriving(Show)
--String pentru soiul de mere sau portocale
--int numarul de felii ale portocalei
--bool marul are vierme sau nu

ionatanFaraVierme = Mar "Ionatan" False
goldenCuVierme = Mar "Golden Delicious" True
portocalaSicilia10 = Portocala "Sanguinello" 10

listaFructe = [Mar "Ionatan" False,
                Portocala "Sanguinello" 10,
                Portocala "Valencia" 22,
                Mar "Golden Delicious" True,
                Portocala "Sanguinello" 15,
                Portocala "Moro" 12,
                Portocala "Tarocco" 3,
                Portocala "Moro" 12,
                Portocala "Valencia" 2,
                Mar "Golden Delicious" False,
                Mar "Golden" False,
                Mar "Golden" True]

--a) Scrieti o fct care indica daca un fruct e sau nu o portocala de sicilia
--E Tarocco, Moro sau Sanguinello

ePortocalaDeSicilia :: Fruct -> Bool
ePortocalaDeSicilia (Portocala "Tarocco" _) = True
ePortocalaDeSicilia (Portocala "Moro" _) = True
ePortocalaDeSicilia (Portocala "Sanguinello" _) = True
ePortocalaDeSicilia _ = False


--b) Scrieti o functie care calculeaza nr total de felii ale
--portocalelor de Sicilia dintr-o lista de fructe
--ATENTIE!!!! mai multe variante
--varianta laborator
feliiFruct :: Fruct -> Int
feliiFruct (Portocala "Tarocco" x) = x
feliiFruct (Portocala "Moro" x) = x
feliiFruct (Portocala "Sanguinello" x) = x
feliiFruct _ = 0
nrFeliiSicilia :: [Fruct] -> Int
nrFeliiSicilia lista = sum [feliiFruct fruct | fruct <- lista]

--varianta foldr
nrFeliiSiciliaMap :: [Fruct] -> Int
nrFeliiSiciliaMap lista = foldr (\(Portocala _ x) accum -> x + accum) 0 (filter ePortocalaDeSicilia lista)

--varianta list comprehension
--DIFICIL!! FOLOSIRE elem si se pot extrage numai fructele portocale
nrFeliiSiciliaComp :: [Fruct] -> Int
nrFeliiSiciliaComp lista = sum [nr | Portocala nume nr <- lista, elem nume ["Tarocco", "Moro", "Sanguinello"]]

--DIFICIL: folosire x@
nrFeliiSiciliaComp2 lista = sum [nr | fruct@(Portocala nume nr) <- lista, ePortocalaDeSicilia fruct]

--recursie
nrFeliiSiciliaRec [] = 0
nrFeliiSiciliaRec (fruct@(Portocala nume nr):tail) =
    if ePortocalaDeSicilia fruct then nr + (nrFeliiSiciliaRec tail)
    else nrFeliiSiciliaRec tail
nrFeliiSiciliaRec (_:tail) = nrFeliiSiciliaRec tail

--TEST
test_nrFeliiSicilia = nrFeliiSicilia listaFructe == 52 --trebuie sa dea true pe apel cu orice functie de mai sus


--c) Scrieti o functie nrMereViermi care calculeaza nr de mere
--care au viermi dintr-o lista de fructe
--List comprehension
nrMereViermiComp :: [Fruct] -> Int
nrMereViermiComp lista = sum [1 | fruct@(Mar nume areVierme) <- lista, areVierme == True]
---Sau putem folosi length in loc de sum

--Recursie
nrMereViermiRec :: [Fruct] -> Int
nrMereViermiRec [] = 0
nrMereViermiRec (fruct@(Mar nume areVierme):tail)
    | areVierme == True = 1 + nrMereViermiRec tail
    | otherwise = nrMereViermiRec tail
nrMereViermiRec (_:tail) = nrMereViermiRec tail

--Foldr
--cu functie ajutatoare!!!!
--Se poate altfel? 
eMar :: Fruct -> Bool
eMar (Mar _ areVierme) = areVierme
eMar _ = False
nrMereViermiFoldr lista = foldr (+) 0 (map (\fruct -> 1) (filter eMar lista))


---Exercitiul 2
type NumeA = String --ca un alias
type Rasa = String
data Animal = Pisica NumeA | Caine NumeA Rasa deriving(Show)

--Scrieti o functie care intoarce Meow pentru pisica si Woof pentru caine
vorbeste :: Animal -> String
vorbeste (Pisica _) = "Meow!"
vorbeste (Caine _ _) = "Woof!"
luca = Pisica "Luca"
rex = Caine "Rex" "Lup"

--Rasa unui caine daca este caine, Nothing daca e pisica
--ATENTIE: Definire tip
rasa :: Animal -> Maybe String
rasa (Caine _ r) = Just r
rasa (Pisica _) = Nothing


-------------------------------LOGICA PROPOZITIONALA----------------------------------------

type Nume = String
data Prop 
    = Var Nume   --o propozitie poate avea variabile
    | F          --F/T, not, si, sau 
    | T
    | Not Prop
    | Prop :|: Prop
    | Prop :&: Prop
    deriving(Eq, Read)

infixr 2 :|:      
infixr 3 :&:


--1) (PvQ)^(P^Q)
p1 :: Prop   -- se poate fara parantezele de la var
p1 = ((Var "P") :|: (Var "Q")) :&: ((Var "P") :&: (Var "Q"))

--2) (PvQ)^(notP^notQ)
p2 :: Prop
p2 = ((Var "P") :|: (Var "Q")) :&: (Not (Var "P") :&: Not (Var "Q"))

--3) (P^(QvR))^((notPvnotQ)^(notPvnotR))
p3 :: Prop
p3 = (Var "P" :&: (Var "Q" :|: Var "R")) :&: ((Not (Var "P") :|: Not (Var "Q")) :&: (Not (Var "P") :|: Not (Var "R")))



--Exercitiul 2
--Faceti tipul Prop instanta a clasei de tipuri Show, inlocuind conectivele 
--Not, :|:, :&: cu ~, |, &
--ATENTIE!! CUM Instantiem clasa Show


instance Show Prop where   --Show e numele type class-ului
    show (Var x) = x --show x daca nu era string
    show F = "false"
    show T = "true"
    show (a :|: b) = "(" ++ show a ++ " v " ++ show b ++ ")"
    show (a :&: b) = "(" ++ show a ++ " ^ " ++ show b ++ ")"
    show (Not a) = "(~" ++ show a ++ ")"

test_ShowProp :: Bool
test_ShowProp = 
    show (Not (Var "P") :&: Var "Q") == "(~P & Q)"

--Cum folosim instance pe Figura
class Figura a where
    aria :: a -> Float  --restrictii ce trebuie implementat
    perimetru :: a -> Float

data Cerc = Cerc Float --acum cerc este propriul lui tip; nu mai e constructor

instance Figura Cerc where
    aria (Cerc r) = r^2 * pi
    perimetru (Cerc r) = 2 * r * pi
--aria (Cerc 5)
--perimetru (Cerc 5)

---Unde nu merge Ord
data Tuplu a = Element a | Pereche (a,a) deriving(Show, Eq)
--Element 5 == Element 4 F

--data Nested = Nimic | TT (Tuplu Int) deriving (Show, Eq, Ord)
--EROARE: CA NU EXISTA ORD PENTRU TUPLU
data TipulMeuMagic = Magic 
--de ce nu merge a = Element Magic? Pentru Magic nu exista Show

--Functie care face show pw ala care e mai mare
maxshow :: (Ord a, Show a) => a -> a -> String
maxshow a b = if a > b then show a else show b --trebuie sa implementeze si show si ord

-------EVALUAREA UNEI EXPRESII--------


--Exercitiul 3
--Definiti o functie eval care data o expresie logica si
--un mediu de evaluare, calculeaza valoarea de adevar a expresiei

--Trebuie sa stim ce valori au variabilele
--o lista de perechi care tine valorile variabilelor
type Env = [(Nume, Bool)]

impureLookup :: Eq a => a -> [(a,b)] -> b
impureLookup a = fromJust . lookup a
--fromJust (Just 5) => 5

eval :: Prop -> Env -> Bool
eval F _ = False
eval T _ = True
eval (Var x) env = impureLookup x env
eval (Not x) env = not (eval x env)
eval (x :|: y) env = (eval x env) || (eval y env)
eval (x :&: y) env = (eval x env) && (eval y env)

--scoate variabilele din expresie
variabile' F = []
variabile' T = []
variabile' (Var x) = [x]
variabile' (Not x) = variabile' x
variabile' (x :|: y) = variabile' x ++ variabile' y
variabile' (x :&: y) = variabile' x ++ variabile' y
--scoate duplicatele din variabile'
variabile :: Prop -> [Nume]
variabile prop = nub (variabile' prop)

test_variabile = variabile (Not (Var "P") :&: Var "Q") == ["P", "Q"]
--trebuie sa dea true

--Functie care da toate valorile posibile ale variabilelor
envs :: [Nume] -> [Env]
envs [] = []
envs [nume] = [[(nume, False)], [(nume, True)]]
envs (nume:t) =
    let restul = envs t in  --restul e o lista de envs
    let cu_true = [(nume, True) : env | env <- restul] in 
    let cu_false = [(nume, False) : env | env <- restul] in
    cu_false ++ cu_true

test_envs =
      envs ["P", "Q"]
      ==
      [ [ ("P",False)
        , ("Q",False)
        ]
      , [ ("P",False)
        , ("Q",True)
        ]
      , [ ("P",True)
        , ("Q",False)
        ]
      , [ ("P",True)
        , ("Q",True)
        ]
      ]


--Exercitiul 7
--Verificam daca e satisfiabila
--construim toate envs si verificam daca cel putin una da true
satisfiabila :: Prop -> Bool
satisfiabila prop =
    let v = variabile prop in
    let e = envs v in
    or [eval prop x | x <- e]

test_satisfiabila1 = satisfiabila (Not (Var "P") :|: Var "Q") == True
test_satisfiabila2 = satisfiabila (Not (Var "P") :&: Var "P") == False

--toate sa dea true
valida :: Prop -> Bool
valida prop =
    let v = variabile prop in
    let e = envs v in
    and [eval prop x | x <- e]
test_valida1 = valida (Not (Var "P") :&: Var "Q") == False
test_valida2 = valida (Not (Var "P") :|: Var "P") == True

-- a -> b <=> ~a v b
-- a <-> b <=> (~a v b) ^ (~b v a)
--putem defini orice operator
a ++++++ b = a + 7 * a + b

--data TipulMeu = Constructor [Int]
--f (Constructor lista) = 