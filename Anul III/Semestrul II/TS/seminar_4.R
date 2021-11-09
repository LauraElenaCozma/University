# Metoda inversa
# Generarea a n valori intr-o variabila aleatoare x, repartizata exponential
# cu parametru lambda

n <- 10^6
lambda <- 1

# nu vrem sa folosim rexp din sistem, vrem sa plecam de la o uniforma
# generam o singura valoare u

# cum verificam daca sunt bune sau nu? generam n valori

genereaza_exp <- function(n, lambda) {
  u <- runif(n)
  x <- (-1)/lambda * log(u)
  x
}

x <- genereaza_exp(n, lambda)

x1 <- rexp(n, lambda)

# facem histogramele
# par = functie care gestioneaza parametrii grafici
# facem o linie si 2 coloane
# de fiecare data cand rulam bucata de cod ramane valabila pana rulam iar par
par(mfrow = c(1, 2))
t <- seq(0, 10, 0.001)


hist(x, freq = F)
lines(t, dexp(t, lambda))

hist(x1, freq = F)
lines(t, dexp(t, lambda))

# avem x un vector cu valori foarte apropiate
# valorile intre 0 si 0.5 de pe x au frecventa de pe y
# pe noi ne intereseaza forma in ansamblu

# generam toate valorile pornind de la o valoare minima la una maxima

# vrem sa desenam peste grafic
# punem pe grafic densitatea de la exponentiala
lines(t, dexp(t, lambda))
# aria de sub graficul densitatii imi da probabilitatea
#plot(t, dexp(t, lambda))

par(mfrow = c(1, 1))
# Punem histogramele suprapuse

x <- genereaza_exp(n, lambda)
x1 <- rexp(n, lambda)
hist(x, freq = F, col="blue")
lines(t, dexp(t, lambda), col="green") # lines deseneaza mereu peste

hist(x1, freq = F, col="red", add=TRUE)


############################################
# Repartitia gamma
# Generam n valori dintr-o variabila aleatoare X ~ Gamma(k, lambda)
gamma_one <- function(k, lambda) {
  # generam k valori fiecare provenind dintr-o exponentiala de param lambda
  x <- genereaza_exp(k, lambda)
  sum(x)
  }  

# ne ajutam de functia gamma one ca sa generam cele n valori
gamma_n <- function(n, k, lambda) {
  x <- c()
  for(i in 1:n) {
    x <- c(x, gamma_one(k, lambda))
  }
  x
}

n <- 10^6
lambda <-2
k <- 3

t <- seq(0, 10, 0.001)

x <- gamma_n(n, k, lambda)
x1 <- rgamma(n, k, lambda)
hist(x, freq = F, col="blue")
hist(x1, freq = F, col="red", add=TRUE)
lines(t, dgamma(t, k, lambda), col="green") # lines deseneaza mereu peste

# la 10^6 merge greu
# Eficientizare fara folosirea lui for

gamma_n_turbo <- function(n, k, lambda) {
  # sapply(vector, functie)
  x <- 1:n
  # vrem sa apelam functia gamma_one de n ori
  f_aux <- function(ceva=1) {
    gamma_one(k, lambda)
  }
  sapply(x, f_aux)
}

x <- gamma_n_turbo(n, k, lambda)
x1 <- rgamma(n, k, lambda)
hist(x, freq = F, col="blue")
hist(x1, freq = F, col="red", add=TRUE)
lines(t, dgamma(t, k, lambda), col="green") # lines deseneaza mereu peste


# Eficientizarea suprema cu matematica

gamma_n_super_turbo <- function(n, k, lambda) {

  f_aux <- function(ceva=1) {
    u <- runif(k)
    -1/lambda * sum(log(u))
  }
  sapply(1:n, f_aux)
}

x <- gamma_n_turbo(n, k, lambda)
x1 <- rgamma(n, k, lambda)
hist(x, freq = F, col="blue")
hist(x1, freq = F, col="red", add=TRUE)
lines(t, dgamma(t, k, lambda), col="green") # lines deseneaza mereu peste
