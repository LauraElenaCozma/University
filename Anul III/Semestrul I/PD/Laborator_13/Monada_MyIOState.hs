type Input = String
type Output = String
type InOutWorld = (Input, Output)
type MyIOState a = State InOutWorld a
-- Are forma State (\(input, output) -> (a, (input, output)))
newtype State state a = State {runState :: state -> (a, state)}
{- SAU
newtype MyIOState a = MyIOS {runMyIOS :: InOutWorld -> (a, InOutWorld)}
-}

instance Monad (State s) where
    return va = State (\s -> (va, s))
    ma >>= k = State f
                where f s1 = let 
                                (va, s2) = runState ma s1
                                (vb, s3) = runState (k va) s2
                             in
                                 (vb, s3)


instance Applicative (State s) where
    pure = return
    mf <*> ma = do { f <- mf; a <- ma; return (f a) }

instance Functor (State s) where
    fmap f ma = do { a <- ma; return (f a) }

--definiti operatiile de bază myGetChar , myPutChar si runIO
myGetChar :: MyIOState Char
myGetChar = State (\(c:input, output) -> (c, (input, output)))
test1 = runState myGetChar ("aban", "def")

myPutChar :: Char -> MyIOState ()
myPutChar c = State (\(inp, out) -> ((), (inp, out ++ [c])))
test2 = runState (myPutChar '1') ("abc", "def")

--given a command and an input produce the output
runIO :: MyIOState a -> InOutWorld -> Output
runIO command (i, o) = out
                        where 
                            (va, (inp, out)) = runState command (i, o)
test3 = runIO myGetChar ("abc", "def")
-- "def" pentru ca returnam output; daca returnam si va va afisa 'a'
test4 = runIO (myPutChar '1') ("abc", "def")
-- "def1"


-- definiti operatii derivate utile (myPutStr, myGetLine)
myPutStr :: String -> MyIOState ()
myPutStr str = State (\(i, o) -> ((), (i, o ++ str)))

test5 = runState (myPutStr "laura") ("123", "abd")
-- ((),("123","abdlaura"))

myPutStrRec :: String -> MyIOState ()
myPutStrRec "" = myPutChar '\n'
myPutStrRec (c:s) = do 
    myPutChar c
    myPutStrRec s

test6 = runState (myPutStrRec "laura") ("123", "abd")
-- ((),("123","abdlaura\n"))


myGetLine :: MyIOState String
myGetLine = State (\(i, o) -> (i, ("", o)))
test7 = runState myGetLine ("abv", "sef")
-- ("abv",("","sef"))

myGetLineRec :: MyIOState String
myGetLineRec = do
    c <- myGetChar
    if c == '\n' then return ""
    else do
        rest <- myGetLineRec
        return (c:rest)

test8 = runState myGetLineRec ("abv\n", "sef")
-- ("abv",("","sef"))