
# Calculam valoarea exacta a integralei
f1 <- function(x)
{
  x^3*exp(-3*x^2/16)
}
real_val <- integrate(f1, -Inf, Inf)$value # = 0
# Functia e impara, deci integrala este 0

# Monte Carlo pentru integrala -inf inf x^3 * exp(-3x^2/16)

# 1. Pornind de la o normala de medie 0 si dispersie sqrt(8/3)
# f(x) = (sqrt(3)/(4*pi)) * exp(-3*x^2/16)
# integrala de  calculat este: integrala de la -inf la + inf din
# x^3 * 4*pi/sqrt(3) * sqrt(3)/(4*pi) * exp(-3x^2/16)
# Deci, h(x) = x^3
# f(x) = sqrt(3)/(4*pi) * exp(-3x^2/16)
# g(x) = x^3 * exp(-3x^2/16)

h1 <- function(x) 
{
  x^3
}

n <- 10^6
x <- rnorm(n, 0, sqrt(8/3))
hu <- h1(x)
medie_empirica_norm <- 4*pi/sqrt(3) * sum(hu)/n  # 0.0168



# Aproximati integrala de la -inf la +inf din exp(-x^2) cu ajutorul exponentialei
# Calculam folosind Monte Carlo integrala din -inf la +inf din exp(-x^2); functia e para, deci calculam 2*integrala(0, inf)
# Facem schimbarea de var x^2 = y <=> x = sqrt(y)
# x -> 0 => y -> 0
# x -> inf => y -> inf
# 2xdx = dy => dx = 1/(2*sqrt(y))dy
# I = integrala 0 inf din exp(-y) * 1/sqrt(y)dy
# Alegem exponentiala cu lambda = 1
# f(x) = exp(-x)
# h(x) = 1/sqrt(x)
h2 <- function(x) 
{
  1/sqrt(x)
}

x2_exp <- rexp(n, 1)
hu <- h2(x2_exp)
medie_empirica_2_exp <- sum(hu)/n          # 1.76