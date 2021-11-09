
# Tema

#ex1

f1 <- function(x)
{
  (1-x)^3*x^5
}

real_val_f1 <- integrate(f1, 0, 1)$value               #0.00198412
f1u <- f1(u)
med_val_f1 <- sum(f1u)/n                              #0.00197447


#ex2

f2 <- function(x)
{
  exp(exp(x))
}

real_val_f2 <- integrate(f2, 0, 1)$value               #6.3165638
f2u <- f2(u)
med_val_f2 <- sum(f2u)/n                               #6.3158491


#ex3

f3 <- function(x) 
{
  exp(x + x^2)
}

real_val_f3 <- integrate(f3, -2, 2)$value               #93.162753
u <- runif(n, -2, 2)
f3u <- f3(u)
med_val_f3 <- 4 * (sum(f3u)/n)                          #93.749209


#ex4
# Aplicam schimbarea de variabila y = 1/(1+e^x)
# x -> inf => y -> 0
# x -> -inf => y -> 1

f4 <- function(x)
{
  (1/(x*(1-x))) * exp(-(log(1/x-1)^2)) 
}

real_val_f4 <- integrate(f4, 0, 1)$value                #1.77245
u <- runif(n)
f4u <- f4(u)
med_val_f4 <- sum(f4u)/n                                #1.77193