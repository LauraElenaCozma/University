gama <- function(n)
{
  if(isNatural(n))
    return(factorial(n-1))
  else if(n>1)
  {
    return (n-1)*gama(n-1)
  }
       else if(n<1)
       {
         func <- function(x)
         {
           x^(n-1)*exp(-x)
         }
         return(integrate(func,0,Inf))
       }
           
}

gama(3.532)
gamma(3.532)


