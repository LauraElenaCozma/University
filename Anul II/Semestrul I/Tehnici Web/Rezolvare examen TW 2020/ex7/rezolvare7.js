window.onload = function()
{
    nrCreate = 0;
    var inp = document.getElementById("nrp");
    inp.addEventListener("focusout" , fct);

    generare = 0;
    function fct( )
    {
        console.log(1);
        var inp = document.getElementById("nrp");
        var val = inp.value;
        if(parseInt(val) != NaN)
        {
            var v = parseInt(val);
            console.log(v);
            for(let i = 0 ; i < v ; i++)
            {
                
                generare = setTimeout(function(){p = document.createElement("p");
                p.innerHTML = i;
                p.addEventListener("click" , stopFct);
                document.body.appendChild(p);} , 500 * (i + 1));
            }
        }
    }

    function stopFct()
    {
        console.log(342);
        clearTimeout(generare);

        setTimeout(function(b){alert(b.innerHTML);} , 2000,this);
    }

}