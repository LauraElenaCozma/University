import Data.Monoid
-- Writer: un tip de date care e o pereche - un state si un log de mesaje
-- putem schimba state-ul curent, afisam ceva si modificam state-ul

--ex: state e un numar pe care il crestem si logam pe baza acestui nr

--runWriter (inceput >>= logIncrement >>= logIncrement)

{-creste_state_ul writer = do
    state_vechi <- writer
    Writer (show state_vechi + 1, "Am crescut state-ul cu unu\n")
-}


-- the Writer monad is for values that have another value attached that acts as a sort of log value.

-- fct that takes the number of bandits in a gang and tells if that's a big gang or not
isBigGang :: Int -> (Bool, String)
isBigGang x = (x > 9, "Compared gang size to 9")

applyLog :: (a, String) -> (a -> (b, String)) -> (b, String)
applyLog (x, log) f = 
    let (y, newLog) = f x in
    (y, log ++ newLog)

-- Apel: (3, "Smallish gang. ") `applyLog` isBigGang
-- (False,"Smallish gang. Compared gang size to 9")

-- (30, "A freakinh platoon. ") `applyLog` isBigGang
-- (True,"A freakinh platoon. Compared gang size to 9")

-- Exemple de alte functii
-- ("Tobin","Got outlaw name.") `applyLog` (\x -> (length x, "Applied length."))  
-- (5,"Got outlaw name.Applied length.")

----- The writer type --------

{-newtype Writer w a = Writer {runWriter :: (a, w)}
instance (Monoid w) => Monad (Writer w) where  
    --mempty is used to present identity monoid values, such as "" and Sum 0
    return x = Writer (x, mempty)  
    (Writer (x,v)) >>= f = 
        let (Writer (y, v')) = f x in 
        Writer (y, v `mappend` v')-}

--- Monada Writer

newtype WriterS a = Writer { runWriter :: (a, String) } 


instance  Monad WriterS where
  return va = Writer (va, "")
  ma >>= k = let (va, log1) = runWriter ma
                 (vb, log2) = runWriter (k va)
             in  Writer (vb, log1 ++ log2)


instance  Applicative WriterS where
  pure = return
  mf <*> ma = do
    f <- mf
    a <- ma
    return (f a)       

instance  Functor WriterS where              
  fmap f ma = pure f <*> ma     

tell :: String -> WriterS () 
tell log = Writer ((), log)

-- 1.1 Definiti functiile logIncrement si logIncrement2 din cursul 9 si testati
-- functionarea lor

logIncrement :: Int  -> WriterS Int
logIncrement x = do
    tell (" increment: " ++ (show x) ++ "\n")
    return (x + 1)
-- runWriter $ logIncrement 10 => (11," increment: 10\n")

logIncrement2 :: Int -> WriterS Int
logIncrement2 x = do
    y <- logIncrement x
    logIncrement y
    --return (y + 1) nu mai adauga increment: 11 in log; doar se mareste primul nr

logIncrementN :: Int -> Int -> WriterS Int
logIncrementN x 1 = logIncrement x
logIncrementN x n = do
    y <- logIncrement x
    logIncrementN y (n - 1)

-- Apel: runWriter $ logIncrementN 10 4
-- (14," increment: 10\n increment: 11\n increment: 12\n increment: 13\n")





