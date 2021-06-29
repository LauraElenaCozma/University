# Metoda Monte Carlo

# Construieste o functie care se comporta ca g(x)

g <- function(x)
{
  x^5*(1-x)^0.5
}

# O integrez folosind functia integrate
# Luam valoarea din lista

teta <- integrate(g, 0, 1)$value

# Aproximez valoarea lui teta prin metoda Monte Carlo

n <- 10^5     # n mai mare, precizie mai buna
u <- runif(n) # Genereaza n valori in intervalul (0,1)
gu <- g(u) 
medie_empirica <- sum(gu)/n # Aici se afla aproximarea
