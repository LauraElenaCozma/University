window.addEventListener("load",function(){

	var sir = localStorage.getItem("numere");

	if(sir == undefined)
			sir = "";
	document.body.appendChild(document.createTextNode(sir));
	setInterval(
		function(){
			document.body.appendChild(document.createTextNode(Math.floor(Math.random()*1000)+" "));
			document.body.normalize();
		},500
	);

	var btn = document.getElementById("salveaza");
	btn.onclick = function(){
		var sir = document.body.lastChild.textContent;
     	localStorage.setItem("numere" , sir);
	}

	var s = document.getElementById("sterge");
	s.onclick = function() {
		localStorage.setItem("numere" , "");
		document.body.lastChild.textContent = "";
	}


});