import Data.Maybe
{-Se definesc tipurile de date Exp si Env in modul urmator: 



Definiti interpretarea expresiilor Exp folosind monada Reader Env Integer unde

newtype Reader env a = Reader { runReader :: env -> Maybe a }

eval :: Exp -> Reader Env Integer

astfel incat:

Evaluarea unei expresii foloseste Maybe pentru a trata cazurile de eroare (impatire la 0).

datele de  forma Con Integer sunt interpretate ca numere intregi

interpretarea datelor de forma Var Name (variabilelor) este data de Env,

operatia :/: este interpretata ca impartire, 

Programul trebuie sa contina definitia completa a monadei  Reader env a

Rezolvarea exercitiului se va scrie in caseta text. 

 -}

type Name = String

data Exp = Var Name | Con Integer

            | Exp :/: Exp

            deriving (Show)

type Env = [ (Name, Integer) ]

newtype Reader env a = Reader { runReader :: env -> Maybe a }

instance Monad ( Reader env ) where
  return x = Reader (\_ -> Just x)
  ma >>= k = Reader f
              where
              f env = let va = runReader ma env
                      in runReader ( k (fromJust va) ) env


instance  Applicative ( Reader env ) where
  pure = return
  mf <*> ma = do
    f <- mf
    a <- ma
    return (f a)       

instance  Functor ( Reader env ) where              
  fmap f ma = pure f <*> ma 

ask = Reader (\env -> Just env)

eval :: Exp -> Reader Env Integer
eval (Var name) = do
    env <- ask
    let x = fromJust (lookup name env)
    return x
eval (Con x) = return x
eval (ex1 :/: ex2) = do
    eval1 <- eval ex1
    eval2 <- eval ex2
    return (divide eval1 eval2)

divide eval1 eval2 = if eval2 == 0  then return Nothing else return (eval1 `div` eval2)            