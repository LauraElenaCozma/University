/*Scriet ̧i un predicat fib/2 pentru a calcula al n-ulea num ̆ar Fibonacci.
Secventa de numere Fibonacci este definit ̆a prin:
F0 = 1
F1 = 1
Fn = Fn−1 + Fn−2 for n ≥ 2*/

fib(0, 1).
fib(1, 1).
fib(N, X) :- N >= 2, N1 is N - 1, N2 is N - 2, fib(N1, F1), fib(N2, F2), X is F1 + F2.

%Varianta 2
fibo(1, 1, 0). %p1-pozitia n, p2-al n lea nr fibo, p3-al n-1 lea nr fib
fibo(N, Fn, Fn_1) :- N > 1, N1 is N - 1, fibo(N1, Fn_1, B), Fn is Fn_1 + B.

fibonacci(N, X) :- fibo(N, X, Y).