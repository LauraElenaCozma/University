window.onload = function()
{
    var c = document.getElementById("intregi");
    c.onchange = function()
    {

        if(c.checked)
        {
            console.log(3);
            var s = document.getElementById("numere");
            var opt = s.options;
            console.log(opt.length);
            for(let i = 0 ; i < opt.length ; i++)
            {
            
                if(parseInt(opt[i].value) != opt[i].value)
                {
                    opt[i].style.display = "none";
                }
            }
        }
        else
        {
            var s = document.getElementById("numere");
            var opt = s.options;
            console.log(opt.length);
            for(let i = 0 ; i < opt.length ; i++)
            {
                console.log(opt[i].value);
                if(parseInt(opt[i].value) != opt[i].value)
                {
                    opt[i].style.display = "";
                }
            }
        }
    }
    
}