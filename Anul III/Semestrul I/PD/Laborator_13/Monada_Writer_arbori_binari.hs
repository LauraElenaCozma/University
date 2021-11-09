data Binar a = Leaf a | Node (Binar a) (Binar a)
type Elem = [(Int, [Bool])] 
newtype Writer a = Writer {runWriter :: (a, ())}  deriving(Show)

instance Monad Writer where
  return va = Writer (va, ())
  ma >>= k = let (va, ()) = runWriter ma
                 (vb, ()) = runWriter (k va)
             in  Writer (vb, ())


instance  Applicative Writer where
  pure = return
  mf <*> ma = do
    f <- mf
    a <- ma
    return (f a)       

instance  Functor Writer where              
  fmap f ma = pure f <*> ma 

encode (Leaf a) drum = return [(a, drum)]
encode (Node st dr) drum = do
    drumSt <- encode st (drum ++ [True])
    drumDr <- encode dr (drum ++ [False])
    return (drumSt ++ drumDr)

tree = (Node (Node (Leaf 3) (Leaf 4)) (Node (Node (Leaf 1) (Leaf 2)) (Leaf 5)))
-- Apel: runWriter (encode tree [])
-- Apel: encode tree []