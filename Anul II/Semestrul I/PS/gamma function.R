
F <- function(n)
{
       if(isNatural(n))
    
            factorial(n-1)
  
       else if(n>1)
       {
     
           rez <- 1
        
           while(n>1)
           {
              rez <- rez*(n-1)
              n <- n-1
           }
         
           G <- function(x)
           {
           
               exp(-x) * x^(n-1)
           
           }
           
           
           rez * integrate(G,0,Inf)
         
         
         
        }
             else if(n<0)
                 ( "Date de intrare invalide" )

}

F(4.9)
gamma(4.9)

