type Name = String
type M a = Maybe a ----- Aduce in plus cazul de eroare
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

instance Show Value where
    show (Num x) = show x
    show (Fun _) = "<function>"

--- Monada Maybe
-- Se poate renunta la valoarea wrong

showM :: Show a => M a -> String
showM (Just a) = show a
showM Nothing = "<wrong>"


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
add _ _             = Nothing

apply :: Value -> Value -> M Value
apply (Fun k) v = k v           --k = Value -> M Value este o functie
apply _ _       = Nothing

lookupM :: Name -> Environment -> M Value
lookupM x env = case lookup x env of
    Just v -> return v
    Nothing -> Nothing


----------- Testare -------------

test :: Term -> String
test t = showM $ interp t []
-- test pgm1
-- test pgm2

