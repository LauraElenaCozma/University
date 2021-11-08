window.onkeydown  = function(event)
{
    if(event.key >= 0 && event.key <=9)
    {
        var p = document.getElementsByTagName("p");
        for(let i = 0 ; i < p.length ; i++)
        {
            var sir = p[i].innerHTML.split(" ");
            if(sir.length > event.key)
                {this.document.body.removeChild(p[i]);
                i--;}
        }
    }
    

}