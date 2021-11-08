window.onload = function()
{
    window.onclick = function(event)
    {
        if(event.target.nodeName != "DIV")
        {
            var div = document.createElement("div");
            div.className += " animat";    
            document.body.appendChild(div);
            var rand = Math.floor(Math.random() * 2);
            if(rand == 1)div.style.animationName = "miscare1";
            else div.style.animationName = "miscare2";
            div.style.position = "absolute";
            var x = event.clientX;
            var y = event.clientY;
            var w = parseInt(window.getComputedStyle(div).getPropertyValue("width"));
            var h = parseInt(window.getComputedStyle(div).getPropertyValue("height"));
            div.style.top = y - h/2 + "px";
            div.style.left = x - w/2 + "px";
        }

    }
}