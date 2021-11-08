window.addEventListener("load", function(){
	var rng=document.getElementById("rng");
	rng.max=Math.floor(20+Math.random()*20);
	rng.parentNode.insertBefore(document.createTextNode(rng.min),rng);
	rng.parentNode.appendChild(document.createTextNode(rng.max));
	rng.value=rng.min;

	function myFunc()
	{
		console.log(1);
		var inp = document.getElementsByTagName("input")[0];
		var val = inp.value;
		document.body.style.fontSize = val + "px";

		var min = parseInt(inp.min);
		var max = parseInt(inp.max);

		console.log(min + ". " + max + " " + val);
		if(val > (min + max)/2)
		{
			console.log(2);
			document.body.style.color = "red";
		}
		else
		{
			document.body.style.color = "black";
		}
	}

	var inp = document.getElementsByTagName("input")[0];
	inp.addEventListener("change" , myFunc);

	


	 var radio = document.querySelectorAll("input[type=radio]");
	 for(let i = 0 ; i <radio.length ; i++)
	 	radio[i].name = "grup";
	 
	var btn = document.getElementById("btn");

	btn.addEventListener("click" , changeText);

	function changeText(){
		var radio = document.querySelectorAll("input[type=radio]");
		for(let i = 0 ; i < radio.length ; i++)
			if(radio[i].checked)
			{
				this.innerHTML = radio[i].parentNode.textContent;
				break;
			}
		
	}
	
});
