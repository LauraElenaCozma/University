
n <- 10 ^ 5

x <- runif(n, -1, 1)
y <- runif(n, -1, 1)

in_circle <- sum(x ^ 2 + y ^ 2 < 1)

pi_approx = 4 * (in_circle / n)

#Sa se reprezinte grafic punctele care pica in cerc, respectiv in afara cercului dar in patrat

arch <- function(x) {
  sqrt(1 - x ^ 2)
}

plot(0, 0)

xy = data.frame(x, y)
points(xy[which(xy$x ^ 2 + xy$y ^ 2 < 1),], col = 'magenta')
points(xy[which(xy$x ^ 2 + xy$y ^ 2 > 1),], col = 'blue')

#Sa se reprezinte un cerc centrat in origine si raza 1

x_circle = seq(-1, 1, length.out = n)
lines(x_circle, arch(x_circle), col = 'green')
lines(x_circle,-arch(x_circle), col = 'green')


# Solutie cu data frame
plot(0, 0, asp=1)

# Construim un data frame continand punctele selectate
df <- data.frame(x, y)
names(df) <- c("val_x", "val_y")

# Filtram valorile din data frame in 2 data frame-uri noi, continand
# punctele din cerc si din afara lui
library(dplyr)
df_in_cerc <- filter(df, val_x ^ 2 + val_y ^ 2 < 1)
df_in_afara <- filter(df, val_x ^ 2 + val_y ^ 2 > 1)

# Afisam pe acelasi grafic fiecare set de date cu o culoare distincta
points(df_in_cerc, col='magenta')
points(df_in_afara, col='blue')

# Adaugam cercul de raza 1
symbols(0, 0, circles=c(1), inches=FALSE, add=TRUE)


# Puteam lucra cu cbind in loc de data.frame
punct <- cbind(x, y)

# Accesare x
punct[,1]


# Alta solutie

plot(x, y, col=ifelse(x ^ 2 + y ^ 2 < 1, "magenta", "blue"), asp=1)

# folosim biblioteca plotrix
library(plotrix)
draw.circle(0, 0, 1)


# g(x,y) = e^(-y) * x^2  -> De integrat dublu de la 0 la 1

n <- 10^6
g <- function(x,y){
  exp(-y) * x^2
}

u1 <- runif(n,0,1)
u2 <- runif(n,0,1)

gu <- g(u1,u2)

medieemp <- sum(gu)/n

integrala <-integral2(g,0,1,0,1)$Q
  
  


