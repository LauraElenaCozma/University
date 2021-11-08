fgam <- function(a)
{
  if(a == 1)
    return (1)
  
  else if(a == 1/2)
    return (sqrt(pi))
  
  else if (is.integer(a) && a > 0) # daca este natural 
    return (factorial(a-1))
  
  else if (a > 1)
    return (fgam(a - 1) * (a - 1))
  
  else 
  {
    # pentru a < 1
    f <- function(x)
    {
      x^(a-1)*exp(-x)
    }
    
    return(integrate(f,0,Inf)$value)
  }
}

fbet <- function(a,b)
{
  if(a + b == 1 && a > 0 && b > 0)
    return (pi / (sin(a * pi)))
  else return ( ( fgam(a) * fgam(b) ) / (fgam(a+b)) )
}

# Functie care integreaza dupa densGamma, pe intervalul (min,max), avand ca parametri a si b
integreazaGamma <- function(min , max , a , b)
{
  
  densGamma <- function(x)
  {
    numitor <- b^a * fgam(a)
    numarator <- x ^ (a - 1) * exp(-x / b)
    return (numarator / numitor)
  }
  
  return(integrate(densGamma , min , max)$value)
}

# Functie care integreaza dupa densBeta, pe intervalul (min,max), avand ca parametri a si b 
integreazaBeta <- function(min , max , a , b)
{
  if(max< 0)
    return (0)
  if(min > 1)
    return (0)
  
  densBeta <- function(x)
  {
    
    y <- ((1 - x) ^ (b - 1)) * (x ^ (a - 1))
    return 󰀀
  }
  
  rez <- integrate(densBeta, min , max)
  rez <- rez$value
  numitor <- fgam(a) * fgam(b) / fgam(a+b)
  
  return(rez / numitor)
}

fprobgamma1 <- function(a , b)
{
  x <- integreazaGamma(0 , 3 , a , b)
  return (x)
}

fprobgamma2 <- function(a , b)
{
  x <- integreazaGamma(0 , 5 , a , b) - integreazaGamma(0 , 2 , a , b)
  return (x)
}

fprobgamma3 <- function(a , b)
{
  x <- integreazaGamma(3 , 4 , a , b)
  y <- integreazaGamma(2 , Inf , a , b)
  
  return ( x / y)
}

fprobbeta4 <- function(a , b)
{
  x <- integreazaBeta(2 , Inf , a , b)
  
  return (x)
}

fprobgamma5 <- function(a , b)
{
  x <- integreazaGamma(4 , 6 , a , b)
  return (x)
}

fprobgamma6 <- function(a , b)
{
  x <- integreazaGamma(0 , 1 , a , b)
  y <- integreazaGamma(0 , 7 , a , b)
  return (x/y)
}

fprob7 <- function(a , b)
{
  f <- function(x , y)
  {
    densGamma <- function(x)
    {
      numitor <- b ^ a * fgam(a)
      numarator <- x ^ (a - 1) * exp(-x / b)
      return (numarator / numitor)
    }
    
    densBeta <- function(x)
    {
      numitor <- fbet(a , b)
      numarator <- (1 - x) ^ (b - 1) * x ^ (a - 1)
      return (numarator/numitor)
    }
    
    return (densGamma(x) * densBeta(y)) # densitatea comuna
  }
  
  ymax <- function(x) # limita superioara pentru cea de-a doua integrala
  {
    min <- min(1 , 5 - x) # definirea lui Y este pe (0,1)
  }
  
  I <- integral2(f, 0 , 5 , 0 , ymax)
  return(I$Q)
}


fprob8 <- function(a , b)
{
  
  densGamma <- function(x)
  {
    numitor <- b ^ a * fgam(a)
    numarator <- x ^ (a - 1) * exp(-x / b)
    return (numarator / numitor)
  }
  
  densBeta <- function(x)
  {
    numitor <- fbet(a , b)
    numarator <- (1 - x) ^ (b - 1) * x ^ (a - 1)
    return (numarator/numitor)
  }
  
  # functia care calculeaza densitatea comuna, inversand x si y
  densInvers <- function(x , y) 
  {
    return (densGamma(y) * densBeta(x))
  }
  
  # Integram initial dupa y, ca sa nu am probleme cu domeniul la infinit, si scadem din 1
  
  #limita inferioara
  ymin <- function(x)
  {
    return (x)
  }
  
  #limita superioara
  ymax<-function(x)
  {
    return( x + 0.5)
  }
  
  I<-integral2(densInvers , 0 , 1 , ymin , ymax);
  
  return (1 - I$Q)
}


fprob9 <- function(a1 , b1)
{
  
  densGamma <- function(x)
  {
    numitor <- b ^ a * fgam(a)
    numarator <- x ^ (a - 1) * exp(-x / b)
    return (numarator / numitor)
  }
  
  densBeta <- function(x)
  {
    numitor <- fbet(a , b)
    numarator <- (1 - x) ^ (b - 1) * x ^ (a - 1)
    return (numarator/numitor)
  }
  
  #densitatea comuna este produsul densitatilor (datorita independentei)
  dens <- function(x , y )
  {
    return (densGamma(x) * densBeta(y)) 
  } 
  
  
  ymax <- function(x) # limita superioara pentru cea de-a doua integrala
  {
    return (min(3 - x , 1))
  }
  
  
  numarator <- 1 - integral2(dens , 0 , 3 , 0 , ymax)
  numitor <- fprob8(a , b);
  return ((numarator$Q) / numitor)
}

#d. Calculaţi aceleaşi probabilităţi ca la punctul c) folosind funcţiile de sistem din R
tabel <- function(val1  , val2)
{
  options(digits=20)
  rezultateC <- vector()
  rezultateD <- vector()
  #1) P(X < 3)
  rezultateC <- c(rezultateC , fprobgamma1(val1, val2))
  rezultateD <- c( rezultateD , pgamma(3 , shape = val1 , scale = val2))
  
  
  #2) P(2 < X < 5)
  rezultateC <- c(rezultateC , fprobgamma2(val1 , val2))
  rezultateD <- c( rezultateD , pgamma(5 , shape = val1 , scale = val2) - pgamma(2 , shape = val1 , scale = val2))
  
  #3)  P(3 < X < 4 | X > 2)
  rezultateC <- c(rezultateC , fprobgamma3(val1 ,val2))
  numarator <- pgamma(4 , shape = val1 , scale = val2) - pgamma(3 , shape = val1, scale = val2)
  numitor <- pgamma(Inf, shape = val1 , scale = val2) - pgamma(2 , shape = val1 , scale = val2)
  rezultateD <- c( rezultateD , numarator / numitor)
  
  #4) P(Y > 2)
  rezultateC <- c(rezultateC , fprobbeta4(val1, val2))
  rezultateD <- c(rezultateD , pbeta(Inf , shape1 = val1 , shape2 = val2) - pbeta(2, shape1 = val1 , shape2 = val2))
  
  #5) P(4 < X < 6)
  rezultateC <- c(rezultateC , fprobgamma5(val1, val2))
  rezultateD <- c( rezultateD , pgamma(6 , shape = val1 , scale = val2) - pgamma(4 , shape = val1 , scale = val2))
  
  #6) P(0 < X < 1 | X < 7)
  rezultateC <- c(rezultateC , fprobgamma6(val1, val2))
  numarator <- pgamma(1 ,shape = val1 , scale = val2)
  numitor <- pgamma(7 , shape = val1 , scale = val2)
  rezultateD <- c( rezultateD , numarator / numitor)
  
  #7) P(X + Y < 5)
  rezultateC <- c(rezultateC , fprob7(val1 , val2))
  
  #determina densitatea comuna
  f7 <- function(x , y)
  {
    
    return (dgamma(x , shape = val1 , scale = val2) * dbeta(y , shape1 = val1 , shape2 = val2)) 
  }
  
  ymax7 <- function(x) # limita superioara pentru cea de-a doua integrala
  {
    min <- min(1 , 5 - x) # definirea lui Y este pe (0,1)
  }
  
  I7 <- integral2(f7, 0 , 5 , 0 , ymax7)
  rezultateD <- c(rezultateD , I7$Q)
  
  #8) P(X − Y > 0.5)
  rezultateC <- c(rezultateC , fprob8(val1 , val2))
  
  
  rezultateD <- c(rezultateD , I81$Q + I82$integral)
  
  
  
  df <- data.frame("C" = rezultateC , "D" = rezultateD)
  return(df)
}

tabel(3 , 1) # arata ok
tabel(2 , 4.5) # arata ok
tabel(0.2 , 0.5)