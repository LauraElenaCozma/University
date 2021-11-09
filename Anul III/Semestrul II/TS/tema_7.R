# Simulare metoda inversa pentru v.a. discrete - Repartitia Poisson

# Demonstratie relatie de recurenta
# pj+1 = lambda/(j+1) * pj
# stim ca pj = lambda^j * exp(-lambda) / j!
# pj+1/pj = (lambda^(j+1) * exp(-lambda) * j!) / ((j+1)! * lambda^j * exp(-lambda))=lambda/(j+1)
# deci pj+1 = lambda/(j+1) * pj

# Simulam X ~ Pois(lambda)
simulare_pois <- function(lambda) {
  i <- 0
  p <- exp(-lambda)
  F <- p
  U <- runif(1)
  while (U >= F) {
    p = (lambda * p)/(i + 1)
    F = F + p
    i = i + 1
  }
  i # i da valoarea lui X
}


lambda <- 1.5
X <- simulare_pois(lambda)


# Simulam n valori din aceasta repartitie poisson
simulare_pois_n <- function(n, lambda) {
  x <- 1:n
  # vrem sa apelam functia simulare_pois de n ori
  f_aux <- function(ceva=1) {
    simulare_pois(lambda)
  }
  sapply(x, f_aux)
}

n <-  10^3
X <- simulare_pois_n(n, lambda)

hist(X, col="green")
X1 <- rpois(n, lambda)
hist(X1, add=T, col="red")



#########################################################################

# Simulare metoda inversa pentru v.a. discrete - Repartitia Binomiala

# Demonstratie relatie de recurenta
# pj+1 = (n-j)/(j+1) * p/(1-p) * pj
# stim ca pj = n!/(j! * (n-j)!) * p^j * (1-p)^(n-j)
# pj+1/pj = (n! * p^(j+1) * (1-p)^(n-j-1) * j! * (n-j)!) / (n! * p^j * (1-p)^(n-j) * (j+1)! * (n-j-1)!)
# deci pj+1 = (n-j)/(j+1) * p/(1-p) * pj

# Simulam X ~ Binom(n, p)
simulare_binom <- function(n, p) {
  c <- p / (1 - p)
  i <- 0
  prob <- (1 - p) ^ n
  U <- runif(1)
  
  while (U >= F) {
    prob = c * (n - i) / (i + 1) * prob
    F = F + prob
    i = i + 1
  }
  i # i da valoarea lui X
}


p <- 0.7
n <- 20
X <- simulare_binom(n, p)

# Simulam m valori din aceasta repartitie binomiala
simulare_binom_m <- function(m, n, p) {
  x <- 1:m
  # vrem sa apelam functia simulare_binom de m ori
  f_aux <- function(ceva=1) {
    simulare_binom(n, p)
  }
  sapply(x, f_aux)
}

m <-  10^4
X <- simulare_binom_m(m, n, p)

hist(X, col="green")
X1 <- rbinom(m, n, p)
hist(X1, add=T,col="red")

