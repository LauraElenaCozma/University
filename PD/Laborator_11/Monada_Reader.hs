---Monada Reader

--cutie r->a
--f : a -> cutie de r -> b
--da o cutie r -> b
newtype Reader env a = Reader { runReader :: env -> a }


instance Monad (Reader env) where
  return x = Reader (\_ -> x)
  ma >>= k = Reader f
    where f env = let a = runReader ma env
                  in  runReader (k a) env



instance Applicative (Reader env) where
  pure = return
  mf <*> ma = do
    f <- mf
    a <- ma
    return (f a)

instance Functor (Reader env) where
  fmap f ma = pure f <*> ma


ask :: Reader env env
ask = Reader id

local :: (r -> r) -> Reader r a -> Reader r a
local f ma = Reader $ (\r -> (runReader ma)(f r))

-- Reader Person String

data Person = Person { name :: String, age :: Int }

showPersonN :: Person -> String
showPersonN Person {name = name, age = age} = "NAME: " ++ name


showPersonA :: Person -> String
showPersonA persoana = "AGE: " ++ show (age persoana)


showPerson :: Person -> String
showPerson persoana = "(" ++ (showPersonN persoana) ++ "," ++ (showPersonA persoana) ++ ")"
--showPerson $ Person "Ana" 32

mshowPersonN ::  Reader Person String
mshowPersonN = Reader showPersonN

mshowPersonA ::  Reader Person String
mshowPersonA = Reader showPersonA

mshowPerson :: Reader Person String
mshowPerson = Reader showPerson

--runReader show_mai_multe $ Person "ada" 20
show_mai_multe = do
    name <- mshowPersonN
    age <- mshowPersonA
    total <- mshowPerson
    return (name ++ " " ++ age ++ " " ++ total)

{-
---- VARIANTA 2 de rezolvare
ask :: Reader env env
ask = Reader id

mshowPersonN :: Reader Person String
mshowPersonN = do
    p <- ask
    return ("NAME:" ++ (name p))

p = Person {name="ana", age=21}
--runReader mshowPersonN p

mshowPersonA :: Reader Person String
mshowPersonA = do
    p <- ask
    return ("AGE:" ++ (show (age p)))

mshowPerson :: Reader Person String
mshowPerson = do
    p <- ask
    return ("NAME:" ++ (name p) ++ " AGE:" ++ (show (age p)))


-}