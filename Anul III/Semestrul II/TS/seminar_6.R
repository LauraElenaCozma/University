# Simulam X ~ Geom(p)
# Incepem prin a simula o singura valoare

simulare_geom <- function(p) {
  q <- 1 - p
  U <- runif(1) # pentru ca vrem sa generam doar o valoare
  X <- floor(log(1 - U)/log(q)) + 1
  X
}


p <- 1/2
 
X <- simulare_geom(p)

# Simulam n valori din aceasta geometrica
simulare_geom_n <- function(n, p) {
  # pentru fiecare x pe care vrem sa il generam avem nevoie de alt U
  q <- 1 - p
  U <- runif(n) # pentru ca vrem sa generam doar o valoare
  X <- floor(log(1 - U)/log(q)) + 1
  X
}

n <-  10^6
p <- 1/5
X <- simulare_geom_n(n, p)

length(X[X==0])  # X nu are valori de 0
hist(X, col="green")
X1 <- rgeom(n, p)
X1 <- X1 + 1
length(X1[X1==0]) # functia din sistem are valori de 0
hist(X1, add=T, col="red")
