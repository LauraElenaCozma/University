window.onload = function()
{
    var btn = document.getElementsByTagName("button");
    console.log(btn.length);
    for(let i = 0 ; i < btn.length ; i++)
    {
        btn[i].onclick = clickBtn;
    }

    function clickBtn()
    {
        var clase = this.classList;
        if(clase.contains("a") &&  clase.contains("b") && !clase.contains("c") && !clase.contains("d"))
                    this.className += " zzz";
    }
    var cls = document.getElementById("clase_multe");
    cls.addEventListener("click" , myFct);

    function myFct()
    {
        var clase = this.classList;
        for(let i = 0 ; i < clase.length ; i++)
            if(clase.item(i)[clase.item(i).length - 1] % 2 == 0 )
            {
                clase.remove(clase.item(i));
                i --;
            }
    }
}