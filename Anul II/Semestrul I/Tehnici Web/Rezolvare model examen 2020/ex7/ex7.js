window.onload = function()
{
    setTimeout(creare , 1500);

    function creare()
    {
        for(let i = 0 ; i < 10 ; i++)
        {
            var b = document.createElement("button");
            b.activ = 0 ; 
            b.innerHTML = "0";
            b.addEventListener("click" , changeState);
            b.style.display = "block";
            document.body.appendChild(b);
        }
    }

    function changeState()
    {
        if(this.activ == 0)
        {
            this.activ = setInterval(increment , 1000 , this);
        }
        else
        {
            clearInterval(this.activ);
        }
    }

    function increment(p)
    {
        var x = parseInt(p.innerHTML);
        x++;
        p.innerHTML = x;

    }
}