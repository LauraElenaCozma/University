# Problema 1 lab 5

# F'(x) = f(x) densitatea pe care vrem sa o suprapunem peste histograma pentru comparatie
densitate <- function(x, alfa, beta) {
  alfa * beta * x ^ (beta - 1) * exp(-alfa * x ^ beta)
}

n <- 10 ^ 6
lambda <- 1
alfa <- 0.1#2 0.5 0.5 ca o normala
beta <- 0.25#4 1

genereaza_1 <- function(n, alfa, beta) {
  u <- runif(n)
  x <- -1/alfa * log(u)
  x <- x ^ (1/beta)
}

x <- genereaza_1(n, alfa, beta)

hist(x, freq=FALSE, col='blue')

t <- seq(0, 4, 0.001)

lines(t, densitate(t, alfa, beta), col='red')

# vrem sa eliminam valorile care sunt in plus (cele care sunt foarte putine pe anumite intervale)
x_filtrat <- x[x<10^6]
hist(x_filtrat, freq=FALSE, col='blue')
# inainte range-ul de valori este foarte mare si se ingramadesc intr-un interval foarte mic
# de aceea era doar o bara
x_filtrat_2 <- x_filtrat[x_filtrat<4 * 10^5]
hist(x_filtrat_2, freq=FALSE, col='blue')

t <- seq(0, 3 * 10^5, 1)
lines(t, densitate(t, alfa, beta), col='red')
# acum forma functiei era satisfacuta de densitatea cu rosu



# Simularea uniformei pe multimea 1, 2,....m 
# n = cate valori sa simulam

n <- 10^6
m <- 10
# generam n valori de pe interv 0 1
U <- runif(n)
# m = nr de valori
X <- floor(m * U) + 1

length(X[X<1]) # 0 valori => corect

hist(X, col='blue')
# frecventele de aparitie sunt egale => e ok

