--Exercitii test 

aux a b = if a `mod` 3 == 0 && b `mod` 3 == 0 then a - b else a * b
--Cu recursie
ex2 [a,b] = aux a b
ex2(a:b:t) = (aux a b) + (ex2 (b:t))

--Cu foldr si zip
ex2' (h:t) = 
    let l = zip (h:t) t in
    foldr (\(x,y) accum -> (aux x y) + accum) 0 l

--Cu foldr si fara zip
ex2'' (h:t) = 
    let (suma,_) = foldl (\(suma,ultim) elem -> (suma + (aux ultim elem), elem)) (0, h) t in
    suma


--Ex 3
data MyPair a b = P a b deriving (Show, Eq, Ord, Read)
data LP a = L [a] deriving Show
class MyClass m where
    myMap :: (MyPair a b -> MyPair b a) -> m (MyPair a b) -> m (MyPair b a)
    myFilter :: (MyPair a b -> Bool) -> m (MyPair a b) -> m (MyPair a b)

instance MyClass LP where
    myMap f (L lista) = L [f x | x <- lista]
    myFilter f (L lista) = L [x | x <- lista, f x]

--Quick Check

double x = 2 * x
triple x = 3 * x
penta 200 = 9
penta x = 5 * x

test x = (double x * triple x) == (penta x)


--Scriem un lookup si vedem daca da cat cel obisnuit
myLookUp :: Int -> [(Int, String)] -> Maybe String
myLookUp _ [] = Nothing
myLookUp a ((x,y):t) = if a == x then (Just y) else myLookUp a t

testLookUp a lista = (lookup a lista) == (myLookUp a lista)

--quickCheck testLookUp

-- !! Read e OPUSUL LUI Show
f (P a b) = P b a
g (P a b) = P (a - b) (a + b)

--test_fg x = (f x) == (g x)
--fara deriving Arbitrary la MyPair da eroare;


------------ TYPE CLASSES ----------------
--Show, Eq, Read -> sunt definite pe tipuri care apar la parametri


----Date
--2, 3 [1,2]
--Just 5
--f x y = x * y

--- *
--Int, Float, [Int], Maybe String, Int->String

--- *-> *
--[]
--Maybe
--MyList

---Type Classes 
--Show, Read, Num, Eq, Ord...

--FUNCTOR
--are o cutie de a
--o functie care primeste a si intoarce b
--returneaza o cutie de b
data MyList a = Nil | a ::: (MyList a) deriving Show
instance Functor MyList where
    fmap _ Nil = Nil
    fmap f (head ::: tail) = (f head) ::: (fmap f tail)

--invelisul trebuie sa fie functor
dubleazatot :: (Num a, Functor invelis) => invelis a -> invelis a
dubleazatot container = fmap (*2) container

--diferenta Show si Foldable: instance Show (MyList a) where
instance Foldable MyList where
    foldr _ accum Nil = accum
    foldr f accum (head ::: tail) = 
        let x = foldr f accum tail in
        f head x

--l = (1 ::: (2 ::: ( 3 ::: Nil)))
--acum putem face sum pe l



--facem tipul Distante
data Distante = Km Int
instance Semigroup Distante where
    (Km x) <> (Km y) = Km (x * y)

instance Monoid Distante where
    mempty = Km 1
    mappend (Km x) (Km y) = Km (x * y)

--APPLICATIVE
--primeste o cutie de a
--o cutie de functii
--intoarce o cutie de b
--fata de functii primeste o cutie de functii

--fmap folosind applicative
fmap' functie container = 
    (pure functie) <*> container
--pure baga functia in cutie
