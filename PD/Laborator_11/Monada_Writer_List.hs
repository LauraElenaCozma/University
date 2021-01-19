-------- Writer cu List
newtype WriterLS a = Writer {runWriter :: (a, [String])}

instance Monad WriterLS where
    return va = Writer(va, [])
    ma >>= k = let 
                (va, log1) = runWriter ma
                (vb, log2) = runWriter (k va)
                in
                Writer (vb, log1 ++ log2)

instance Applicative WriterLS where
    pure = return
    mf <*> ma = do
        f <- mf
        a <- ma
        return (f a)

instance Functor WriterLS where
    fmap f ma = pure f <*> ma

tell :: String -> WriterLS ()
tell log = Writer ((), [log])

logIncrement :: Int -> WriterLS Int
logIncrement x = do
    tell ("increment:" ++ (show x))
    return (x + 1)
-- Apel: runWriter $ logIncrement 10

logIncrementN :: Int -> Int -> WriterLS Int
logIncrementN x 1 = logIncrement x
logIncrementN x n = do
    y <- logIncrement x
    logIncrementN y (n - 1)
-- runWriter $ logIncrementN 1 10

isPos :: Int -> WriterLS Bool
isPos x = if (x > 0)
                then (Writer (True, ["pos"]))
                else (Writer (False, ["neg"]))
-- map runWriter $ map isPos [1,-2,3]
-- [(True,["poz"]),(False,["neg"]),(True,["poz"])]

-- 4. Definiti o functie care se comportă similar cu map, dar efectul final este
-- înlăntuirea efectelor. Signatura acestei functii este:

-- Apel: runWriter $ mapWriterLS isPos [1, -2, 3]
mapWriterLS :: (a -> WriterLS b) -> [a] -> WriterLS [b]
mapWriterLS f xs = Writer (list2, list3)
    where
        list1 = map runWriter $ map f xs
        list2 = map fst list1        --iei numai valoarea din pereche, fara log-uri
        list3 = concat $ map snd list1 --in list 3 iei numai log-ul din pereche