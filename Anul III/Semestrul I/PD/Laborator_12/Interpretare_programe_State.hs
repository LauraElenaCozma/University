type Name = String
type M a = IntState a

------ Memoria se va modifica
------ Avem o stare curenta. Se executa ceva, rezulta a si o noua stare

------- Termeni --------
data Term = Var Name
            | Con Integer    --constanta
            | Term :+: Term  --adunarea a doi termeni
            | Lam Name Term  --param si corpul functiei
            | App Term Term
            | Count          --valoarea resprezinta starea
        deriving (Show)

pgm1:: Term
pgm1 = App
          (Lam "x" ((Var "x") :+: (Var "x")))
          ((Con 10) :+:  (Con 11)) --val = 4

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

--- Monada State
--- Vom face state-ul un integer
newtype IntState a = IntState {runIntState :: Integer -> (a, Integer)}

showM :: Show a => M a -> String
showM ma = "Value: " ++ (show va) ++ " Count: " ++ (show s1)
        where 
            (va, s1) = runIntState ma 0

-------- State instanta a clasei Monad ----------
instance Monad IntState where
    return a = IntState (\s -> (a, s))
    ma >>= k = IntState f
                where f s1 = 
                        let  (v2, s2) = (runIntState ma) s1 in
                        let  (v3, s3) = runIntState (k v2) s2 in
                        (v3, s3)

instance Applicative IntState where
    pure = return
    mf <*> ma = do { f <- mf; a <- ma; return (f a) }

instance Functor IntState where
    fmap f ma = do { a <- ma; return (f a) }


--modifica starea intera a monadei conform functiei date ca argument
modify :: (Integer -> Integer) -> IntState ()
modify f = IntState (\s -> ((), f s))
-- Computatie care creste contorul
tickS :: IntState ()
tickS = IntState (\s -> ((), s+1))

-- Intoarce starea curenta
get :: IntState Integer
get = IntState (\s -> (s, s))  
        
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
interp Count _ = do         -- intoarcem starea curenta
    s <- get
    return (Num s)          -- o intorc sub forma de value; interpretarea are un elem de tip value

add :: Value -> Value -> M Value
add (Num i) (Num j) = do
    tickS                   -- SAU TICKS >> RETURN (NUM $ I + J)
    return (Num (i + j))
add _ _             = return Wrong

apply :: Value -> Value -> M Value
apply (Fun k) v = do
    tickS         -- trecem la o noua stare
    k v           --k = Value -> M Value este o functie
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

