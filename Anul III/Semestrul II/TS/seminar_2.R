
n <- 10^4
x <- runif(n, -1, 1) # Genereaza n valori in intervalul (-1,1)
y <- runif(n, -1, 1)

# Versiunea 1
k <- 0
for(i in 1:n) 
{
  if(x[i]^2 + y[i]^2 <=1)
    k <- k + 1
}

# Versiunea eficientizata
k <- sum(x^2 + y^2 <= 1)
pi <- k/n * 4

# Reprezentarea grafica v1
plot(0, 0, col="black")
for (i in 1:n) {
  if(x[i]^2 + y[i]^2 <=1) {
    points(x[i], y[i], col="red")
  }
  else {
    points(x[i], y[i], col="blue")
  }
}


# Ex 1
n <- 10^5     # n mai mare, precizie mai buna
u <- runif(n) # Genereaza n valori in intervalul (0,1)

f1 <- function(x) 
{
  exp(x + x^2)
}

real_val_f1 <- integrate(f1, -2, 2)$value               #93.162753
u <- runif(n, -2, 2)
f1u <- f1(u)
med_val_f1 <- 4 * (sum(f1u)/n)                          #93.749209

# Ex 2

# y = exp(-x) => x = -lny; x-> inf => y -> 0;  x -> 0 => y -> 1
# dx = - (1/y)dy
f2 <- function(x)
{
  -log(x) * (1 + log(x)^2)^(-2) * (1/x)
}

real_val_f2 <- integrate(f2, 0, 1)$value               
u <- runif(n, 0, 1)
f2u <- f2(u)
med_val_f2 <- (sum(f2u)/n)         


# e^(-x^2) -inf, +inf
f3 <- function(x)
{
  exp(-x^2)
}
real_val_f3 <- integrate(f3, -Inf, Inf)$value

# f3 este para, deci vom calcula 2 * integrala(f3, 0, inf)
# x = t/(1-t)
# dx = ((1-t) + t)/(1-t)^2 = 1/(1-t)^2
f3_1 <- function(t) 
{
  2 * exp(-t^2/(1-t)^2) * 1/(1-t)^2
}

# x - tx = t => x = t(1+x) => t = x/(1+x)
# x-> inf => t = 1
# x = 0 => t = 0

u <- runif(n, 0, 1)
f3u <- f3_1(u)
med_val_f3 <- sum(f3u)/n

simulare_pi <- med_val_f3^2


# Ex 4
#integrala 0 1 integrala 0 1 din exp((x+y)^2) dy dx

g <- function(x, y)
{
  exp((x+y)^2)
}

real_val_g <- integral2(g, 0, 1, 0, 1)$Q

# De calculat integrala dubla cu functie imbricata
