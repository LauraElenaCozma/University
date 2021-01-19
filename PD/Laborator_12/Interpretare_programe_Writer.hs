type Name = String
type M a = StringWriter a
-- vom adauga termenul Out care va afisa valorile termenilor
------- Termeni --------
data Term = Var Name
            | Con Integer    --constanta
            | Term :+: Term  --adunarea a doi termeni
            | Lam Name Term  --param si corpul functiei
            | App Term Term
            | Out Term       --EXTINDEM LIMBAJUL CU OPERATIA DE AFISARE
        deriving (Show)

-- EVALUAREA LUI Out u AFISEAZA VALOAREA LUI u URMATA DE ; SI INTOARCE ACEA VALOARE

pgm1:: Term
pgm1 = App
          (Lam "x" ((Var "x") :+: (Var "x")))
          (Out ((Con 10) :+:  (Con 11))) 
-- "Output: 21;  Value: 42"


pgm2 :: Term
pgm2 = Out (Con 41) :+: Out (Con 1)
-- "Output: 41; 1;  Value: 42"

------- Valori ---------
data Value = Num Integer
            | Fun (Value -> M Value) -- o functie
            | Wrong

instance Show Value where
    show (Num x) = show x
    show (Fun _) = "<function>"
    show Wrong = "<wrong>"

--- Monada Writer

newtype StringWriter a = StringWriter { runStringWriter :: (a, String)}


showM :: Show a => M a -> String
showM (StringWriter (a, logs)) = "Output: " ++ logs ++ " Value: " ++ (show a)

-------- Writer instanta a clasei Monad ----------
instance Monad StringWriter where
    return a = StringWriter (a, "")
    ma >>= k = StringWriter (vb, loga ++ logb)
                where
                    (va, loga) = runStringWriter ma
                    (vb, logb) = runStringWriter (k va) 

instance Applicative StringWriter where
    pure = return
    mf <*> ma = do { f <- mf; a <- ma; return (f a) }

instance Functor StringWriter where
    fmap f ma = do { a <- ma; return (f a) }

------ Functie tell care afiseaza valoarea data ca argument
tell :: String -> StringWriter ()
tell str = StringWriter ((), str)

------ Definiti un interpretator --------

type Environment = [(Name, Value)]

interp :: Term -> Environment -> M Value
interp (Var x) env = lookupM x env
interp (Con int) _ = return (Num int)
interp (Lam x term) env = return (Fun $ \v -> interp term ((x, v):env)) --adaug variabila impreuna cu valoarea in env
interp (t1 :+: t2) env = do
    v1 <- interp t1 env
    v2 <- interp t2 env
    add v1 v2
interp (App t1 t2) env = do
    f <- interp t1 env
    v <- interp t2 env
    apply f v
interp (Out t1) env = do
    v <- interp t1 env
    tell (show v ++ "; ") --acest string e adaugat intr-un writer ca mesaj
    return v              --return v se face un writer cu valoarea v dar fara mesaj
--prin inlantuirea expresiilor cu >> logurile se concateneaza si ramane ultima valoare

add :: Value -> Value -> M Value
add (Num i) (Num j) = return (Num (i + j))
add _ _             = return Wrong

apply :: Value -> Value -> M Value
apply (Fun k) v = k v           --k = Value -> M Value este o functie
apply _ _       = return Wrong

lookupM :: Name -> Environment -> M Value
lookupM x env = case lookup x env of
    Just v -> return v
    Nothing -> return Wrong


----------- Testare -------------

test :: Term -> String
test t = showM $ interp t []
-- test pgm1
-- test pgm2

