window.onload = function()
{
   var ult = localStorage.getItem("U");
    if(ult != null)
    {
        var p = document.getElementsByTagName("p");
        p[parseInt(ult)].style.color = "red";
    }
    console.log(ult);
    var p = document.getElementsByTagName("p");
    for(let i = 0 ; i < p.length ; i++)
    {
        p[i].index = i;
        p[i].addEventListener("click", function(){this.style.color = "red"; localStorage.setItem("U" , this.index)});
    }
        
    var btn = document.getElementById("res");
    btn.addEventListener("click" , stopSave);

    function stopSave()
    {
        var p = document.getElementsByTagName("p");
        for(let i = 0 ; i < p.length ; i++)
            p[i].style.color = "black";
        localStorage.clear();
    }
} 