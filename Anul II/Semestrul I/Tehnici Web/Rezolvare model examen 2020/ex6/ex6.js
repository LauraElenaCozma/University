window.onload = function()
{
    var p = document.querySelectorAll("div + p");
    for(let i = 0 ; i < p.length; i++)
    {
        p[i].addEventListener("click" , myFunc);
    }

    function myFunc()
    {
        var div = this.previousElementSibling;
        var lista = div.getElementsByTagName("li");
        this.innerHTML = lista.length;  
    }
}