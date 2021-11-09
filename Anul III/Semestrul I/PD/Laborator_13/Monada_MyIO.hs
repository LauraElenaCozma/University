type Input = String
type Output = String
newtype MyIO a = MyIO { runMyIO :: Input -> (a, Input, Output)}

instance Monad MyIO where
    return a = MyIO (\i -> (a, i, ""))
    ma >>= k = MyIO f
                where f input = 
                        let (a, inputa, outputa) = runMyIO ma input in
                        let (b, inputb, outputb) = runMyIO (k a) inputa in
                        (b, inputb, outputa ++ outputb)

instance Applicative MyIO where
    pure = return
    mf <*> ma = do 
        f <- mf
        a <- ma
        return (f a) 


instance Functor MyIO where
    fmap f ma = do 
        a <- ma
        return (f a) 


myPutChar :: Char -> MyIO ()
myPutChar c = MyIO (\i -> ((), i, [c]))
-- Apel: runMyIO (myPutChar 'c') "input"

myGetChar :: MyIO Char
myGetChar = MyIO (\(c:input) -> (c, input, ""))
-- Apel: runMyIO myGetChar "input"

--given a command and an input produce the output
runIO :: MyIO () -> String -> String
runIO comanda input = o
                        where (a, i, o) = runMyIO comanda input
-- Apel: runIO (myPutChar 'c') "input"

myPutStrRec "" = MyIO (\i -> ((), i, ""))
myPutStrRec (h:tail) = do
    myPutChar h
    myPutStrRec tail
--runMyIO myGetLineRec "ana ar\ne mere\n"
--("ana ar","e mere\n","")


myGetLineRec = do
    c <- myGetChar
    if c == '\n' then return []
    else do
        rest <- myGetLineRec
        return (c:rest)