window.onload = function()
{
    var elem = document.querySelectorAll(".abc");
    for(let i = 0 ; i < elem.length ; i++)
    {
        var clasa = elem[i].classList;
        
        if(clasa.length == 2)
        {
            
            var cls;
            for(let i = 0 ; i < clasa.length ; i++)
                    if(clasa.item(i) != "abc")
                        cls = clasa.item(i);
            elem[i].classList.remove(cls);
        }
    }

    document.body.onclick = function()
    {
        var elem = document.querySelectorAll("[class]");
        for(el of elem)
        {
            var cls = el.classList;
            for(let i = 0 ; i < cls.length ; i++)
            {console.log(cls.item(i));

                if(cls.item(i).search("0")!= -1 || cls.item(i).search("1")!=-1 || cls.item(i).search("2")!=-1 ||cls.item(i).search("3")!=-1 || cls.item(i).search("4")!=-1 || cls.item(i).search("5")!=-1 || cls.item(i).search("6")!=-1 || cls.item(i).search("7")!=-1 || cls.item(i).search("8")!=-1 || cls.item(i).search("9")!=-1)
                   {
                    el.className += " number";
                    break;
                   }     
            }
        }
    }
}

