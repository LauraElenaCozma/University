window.onload = function()
{
    var elem = document.querySelectorAll("div.xyz p");
    for(let i = 0 ; i < elem.length ; i++)
    {
        var c = elem[i].children;
        if(c.length > 5)
        {
            var color = "rgb(" + Math.floor(Math.random() *
            256)
                    + "," + Math.floor(Math.random() * 256)
                    + "," + Math.floor(Math.random() * 256)
                    + ")";
            elem[i].style.border = "2px solid " + color;
            
        }
    }

}