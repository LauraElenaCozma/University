window.onload = function()
{
    window.onkeydown = function(event)
{
    if(event.key == "q")
    {
        var d1 = document.getElementsByClassName("d1");
        for(d of d1)
        {
            var height = window.getComputedStyle(d).getPropertyValue("height");
            var h = parseInt(height);
            h++;
            d.style.height = h +"px";
        }
    }
    else
    {
        var d1 = document.getElementsByClassName("d1");
        for(d of d1)
        {
            var height = window.getComputedStyle(d).getPropertyValue("height");
            var h = parseInt(height);
            if(h > 0) d.style.height =  parseInt(h - 1) + "px";
        }
    }


}
}

