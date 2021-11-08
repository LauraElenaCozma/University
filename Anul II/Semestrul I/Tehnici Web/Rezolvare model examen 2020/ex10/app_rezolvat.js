const express=require('express');
app=express();
app.use('/ex10.html',express.urlencoded({extended:false}));
//app.use(express.static("html"));
persoane=[
	{
		nume:"Georgescu",
		prenume:"Ion"
	},
	{
		nume:"Alexandrescu",
		prenume:"Gogu"
	},	
	{
		nume:"Andreescu",
		prenume:"Andreea"
	},
	{
		nume:"Georgescu",
		prenume:"Monica"
	},
	{
		nume:"Andreescu",
		prenume:"Costel"
	},
        {
		nume:"Georgescu",
		prenume:"Laura"
	},
	{
		nume:"Costache",
		prenume:"Costel"
	},
	{
		nume:"Alexandrescu",
		prenume:"Monica"
	},
]
app.get("/ex10.html", function(req,res){
        //res.redirect("ex10.html");
        res.sendFile(__dirname+"/ex10.html");
});

app.post("/ex10.html", function(req,res){
	var vect=[];
        for(a of persoane) { if(a[req.body.tip]==req.body.cuvant) vect.push(a);} 
	res.send(vect);
	
});

/*app.get("/cale.html",function(req,res)
{
	let url = req.query;

	var obj =[];
	for(let a of persoane)
	{
		if(url.cuvant == a[url.tip])
		 obj.push(a);
	}
	res.send(JSON.stringify(obj));
})
<form ... action="https//:localstorage:8010/cale"
*/



app.listen(8080);
console.log("Serverul a pornit");
