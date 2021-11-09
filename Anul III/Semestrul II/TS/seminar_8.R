# Simularea unei variabile normale standard

generare_normala <- function(a=5) {
  Y <- rexp(1)
  U1 <- runif(1)
  k <- 0
  while( U1 > exp(-(Y - 1)^2 / 2)) {
    U1 <- runif(1)
    k <- k + 1
    Y <- rexp(1)
  }
  mod_X <- -U1
  U2 <- runif(1)
  if(U2 <= 1/2) {
    X <- -mod_X
  } else {
    X <- mod_X
  }
  return(c(X, k))
  
}

generare_normala()

# Generam n valori
generare_norm_n <- function(n) {
  res <- sapply(1:n, generare_normala)
  return(res)
}


n <- 10^6
mat <- generare_norm_n(n)
X <- mat[1,]
k <- mat[2,]

medie <- mean(k)
c <- sqrt(2 * exp(1) / pi)

hist(x, freq=F, col="pink")
t <- seq(-4, 4, 0.01)

lines(t, dnorm(t), col='blue')