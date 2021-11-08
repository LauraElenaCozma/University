window.onmousemove = function(event)
{
    if(event.target && event.target.nodeName != "DIV")
    {
       // var nod = event.eventTarget.previousElementSibling;
       var y = event.clientY;
       var x = event.clientX;
       console.log("y "+y);
        var d = new Date();
        var n = d.getHours();
        var m = d.getMinutes();
        var s = d.getSeconds();
        max = 0;
        index = 0;
        
        var div = document.getElementsByTagName("div");
        for(let i = 0 ; i < div.length ; i++)
        {
           // console.log(window.getComputedStyle(div[i]).top);
            
            if(parseInt(window.getComputedStyle(div[i]).top) < y && parseInt(window.getComputedStyle(div[i]).left) <=x && parseInt(window.getComputedStyle(div[i]).top) > max)
            {
               // console.log(i);
                max = parseInt(window.getComputedStyle(div[i]).top);
                index = i;
            }
        }

        div[index].innerHTML = n + " " + m + " " + s;
    }
}