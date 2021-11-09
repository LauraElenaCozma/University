import Data.Char
------------Recursie-----------------

-- Ex 1 Fibonacci
--Stil ecuational
fibo :: Integer -> Integer
fibo 0 = 0
fibo 1 = 1
fibo n = fibo (n - 1) + fibo (n - 2)

--Recursiv
fibo' :: Integer -> Integer
fibo' n 
    | n < 2 = n
    | otherwise = fibo' (n - 1) + fibo' (n - 2)

---TODO: Fibonacci liniar


-------------RECURSIE PESTE LISTE----------------
--Functie care elimina nr impare si le injumatateste pe cele pare
semipare :: [Int] -> [Int]
semipare [] = []
semipare (h:tail)
    | even h = (h `div` 2) : semipare tail  ----- !! ATENTIE VERIFICARE NR PAR
    | otherwise = semipare tail

--varianta 2 cu where
semipare' lista
    | null lista = lista ----- !! ATENTIE CAZ PT LISTA VIDA
    | even h = (h `div` 2) : semipare' t
    | otherwise = semipare' t
    where
        h = head lista
        t = tail lista

--varianta 3 list comprehension
semipare'' l = [x `div` 2 | x <- l, even x]

--Functie care primeste limita inferioara si cea superioada a unui interval inchis si o lista de numere
--calculeaza lista numerelor care apartin intervalului
--LIST COMPREHENSION
inIntervalComp :: Integer -> Integer -> [Integer] -> [Integer]
inIntervalComp inf sup l = [x | x <- l, x >= inf && x <= sup]
--Apel: inIntervalComp 5 10 [1..15]
--Apel: inIntervalComp 5 10 [2,4,1,2,5,7,4,11,24]

--RECURSIE
inIntervalRec _ _ [] = []
inIntervalRec inf sup (h:l)
    | h >= inf && h <= sup = h : (inIntervalRec inf sup l)
    | otherwise = inIntervalRec inf sup l

--Ex: Functie care numara cate numere strict pozitive sunt intr-o lista data ca argument
--Recursie
pozitiveRec :: [Integer] -> Integer
pozitiveRec [] = 0
pozitiveRec (h:l) = if (h > 0) then 1 + (pozitiveRec l) else pozitiveRec l
--Apel: pozitiveRec [1,4,-2,9,0,-4]

--List comprehension
pozitiveComp l = sum [1 | x <- l, x > 0]  --- !!Atentie: sum ca sa numaram

--Ex: Functie care determina lista pozitiilor numerelor impare din lista
--Recursie --- DIFICIL
pozitiiImpareAux _ [] = []
pozitiiImpareAux p (h:l) = if odd h then p : (pozitiiImpareAux (p + 1) l) else (pozitiiImpareAux (p + 1) l)

pozitiiImpareRec lista = pozitiiImpareAux 0 lista
--List Comprehension  !!!!!!!!!!!!!!!!
pozitiiImpareComp l = [b | (a,b) <- zip l [0..], odd a]

--Ex: produsul cifrelor care apar in sirul de caractere dat ca intrare
multDigitsRec :: [Char] -> Int  -- !!!!!! ATENTIE digitToInt returneaza Int nu Integer
-- !!!!! folosire digitToInt si isDigit 
multDigitsRec [] = 1
multDigitsRec (h:l) = if isDigit h 
    then (digitToInt h) * (multDigitsRec l) 
    else multDigitsRec l

--List comprehension
-- !!!!! functia product
multDigitsComp l = product [(digitToInt x) | x <- l, isDigit x]

--Ex: Pentru o lista de preturi aplica un discount de 25% si pastreaza in lista valorile reduse care sunt mai mari decat 200
--Recursie
discountRec [] = []
discountRec (h:l) = 
    let
        val = 0.75 * h 
    in
    if val < 200 then val : (discountRec l) else discountRec l
--Apel: discountRec [150, 300, 250, 200, 450, 100]

--List comprehension
-- !!! folosire let in list comprehension
discountComp l = [y | x <- l, let y = x * 0.75, y < 200]

--map filter
discountMap l = filter (< 200) (map (* 0.75) l)