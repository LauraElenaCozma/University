type Name = String
type M a = Identity a
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

--- Monada Identity

newtype Identity a = Identity { runIdentity :: a }


showM :: Show a => M a -> String
showM = show . runIdentity

-------- Identity instanta a clasei Monad ----------
instance Monad Identity where
    return a = Identity a
    ma >>= k = k (runIdentity ma)

instance Applicative Identity where
    pure = return
    mf <*> ma = do { f <- mf; a <- ma; return (f a) }

instance Functor Identity where
    fmap f ma = do { a <- ma; return (f a) }


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

