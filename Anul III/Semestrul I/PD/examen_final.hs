{-
care defineste expresii aritmetice cu trei variabile. Definiti interpretarea acestor expresii in monada Reader Int:

   eval :: Expr -> Reader Int

Unde memoria folosita pentru a da valori variabilelor X, Y si Z este reprezentata de parametrii Int din Reader. 

Programul trebuie sa  contina si definitia completa a monadei Reader Int.-}


data Expr =  X  | Y  | Z        -- variabile  
            | Plus   Expr Expr     -- adunare
            | Ori    Expr Expr   -- inmultire

newtype Reader a = Reader {runReader:: Int -> Int -> Int -> a}

instance Monad Reader where
    return a = Reader (\_ _ _ -> a)
    ma >>= k = Reader f 
                where f envX envY envZ =
                        let va = runReader ma envX envY envZ in
                        runReader (k va) envX envY envZ


instance  Applicative Reader where
  pure = return
  mf <*> ma = do
    f <- mf
    a <- ma
    return (f a)       

instance  Functor Reader where              
  fmap f ma = pure f <*> ma 


-- obtinem memoria
askX :: Reader Int
askX = Reader (\envX envY envZ -> envX) --intoarce env-ul lui X

askY :: Reader Int 
askY = Reader (\envX envY envZ -> envY) --intoarce env-ul lui Y

askZ :: Reader Int 
askZ = Reader (\envX envY envZ -> envZ) --intoarce env-ul lui Z


eval :: Expr -> Reader Int
eval X = do
    x <- askX
    return x
eval Y = do
    y <- askY
    return y 
eval Z = do
    z <- askZ
    return z
eval (Plus exp1 exp2) = do
    ev1 <- eval exp1
    ev2 <- eval exp2
    return (ev1 + ev2)
eval (Ori exp1 exp2) = do
    ev1 <- eval exp1
    ev2 <- eval exp2
    return (ev1 * ev2)

--testare
expresie1 = Ori (Plus X Y) (Plus X (Plus Y Z))

test1 = runReader (eval expresie1) 1 2 3
test2 = runReader (eval expresie1) (-1) 1 10

expresie2 = Ori X Y