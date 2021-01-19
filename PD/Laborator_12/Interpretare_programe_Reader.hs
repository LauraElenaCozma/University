type Name = String
type M a = EnvReader a
-- putem gandi mediul de evaluare Environment ca o stare care este citita
-- atunci cand avem nevoie de valorile variabilelor
-- dar nu este modificata

------- Termeni --------
data Term = Var Name
            | Con Integer    --constanta
            | Term :+: Term  --adunarea a doi termeni
            | Lam Name Term  --param si corpul functiei
            | App Term Term
        deriving (Show)

pgm1:: Term
pgm1 = App
          (Lam "x" ((Var "x") :+: (Var "x")))
          ((Con 10) :+:  (Con 11)) --val = 42

pgm2 :: Term
pgm2 = App
  (Lam "y"
    (App
      (App
        (Lam "f"
          (Lam "y"
            (App (Var "f") (Var "y"))
          )
        )
        (Lam "x"
          (Var "x" :+: Var "y")
        )
      )
      (Con 3)
    )
  )
  (Con 4)


------- Valori ---------
data Value = Num Integer
            | Fun (Value -> M Value) -- o functie
            | Wrong

instance Show Value where
    show (Num x) = show x
    show (Fun _) = "<function>"
    show Wrong = "<wrong>"

--- Monada Reader

newtype EnvReader a = Reader { runEnvReader :: Environment -> a }

-- initial avem [] ca environment
showM :: Show a => M a -> String
showM ma = show (runEnvReader ma [])

-------- EnvReader instanta a clasei Monad ----------
instance Monad EnvReader where
    return a = Reader (\_ -> a)
    ma >>= k = Reader f 
                where f env =
                        let va = runEnvReader ma env in
                        runEnvReader (k va) env

instance Applicative EnvReader where
    pure = return
    mf <*> ma = do { f <- mf; a <- ma; return (f a) }

instance Functor EnvReader where
    fmap f ma = do { a <- ma; return (f a) }

-- obtinem memoria
ask :: EnvReader Environment
ask = Reader id --intoarce env-ul 

-- modifica local memoria
local :: (Environment -> Environment) -> EnvReader a -> EnvReader a -- o functie dupa care se modifica memoria
local f ma = Reader (\r -> (runEnvReader ma) (f r)) --readerul initial
--readerul obtinut dupa modif lui r

------ Definiti un interpretator --------
-- DIN INTERPRETOR DISPARE CAMPUL ENVIRONMENT
type Environment = [(Name, Value)]

interp :: Term -> M Value
interp (Var x) = lookupM x
interp (Con int) = return (Num int)
interp (Lam x term) = do
    env <- ask  --extragem env-ul curent 
    --adaug variabila impreuna cu valoarea in env
    return (Fun $ \v -> local (const ((x, v) : env)) (interp term)) --const intoarce param 1: transmite mai departe env modificat
    -- modificam enviromnentul cu local dupa care il transmitem noului interpretor
interp (t1 :+: t2) = do
    v1 <- interp t1
    v2 <- interp t2
    add v1 v2
interp (App t1 t2) = do
    f <- interp t1
    v <- interp t2
    apply f v

add :: Value -> Value -> M Value
add (Num i) (Num j) = return (Num (i + j))
add _ _             = return Wrong

apply :: Value -> Value -> M Value
apply (Fun k) v = k v           --k = Value -> M Value este o functie
apply _ _       = return Wrong

lookupM :: Name -> M Value
lookupM x = do
    env <- ask -- accesam env cu functia ask; cu sageata extragem componenta de tip a
    case lookup x env of  
        Just v -> return v
        Nothing -> return Wrong


----------- Testare -------------
-- ATENTIE: TESTUL SE MODIFICA
test :: Term -> String
test t = showM $ interp t
-- test pgm1
-- test pgm2

