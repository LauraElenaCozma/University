const express=require('express');
app=express();
app.use('/ex10.html',express.urlencoded({extended:false}));

persoane=[
	{
		nume:"Ion",
		sex:"m",
		varsta:3,
	},
	{
		nume:"Oana",
		sex:"f",
		varsta:23,
	},
	{
		nume:"Daria",
		sex:"f",
		varsta:10,
	},
	{
		nume:"Mihai",
		sex:"m",
		varsta:19,
	},
	{
		nume:"Gabriel",
		sex:"m",
		varsta:22,
	},
	{
		nume:"Simona",
		sex:"f",
		varsta:11,
	},
	{
		nume:"Bogdan",
		sex:"m",
		varsta:28,
	}

]
app.get("/ex10.html", function(req,res){

	res.sendFile(__dirname+"/ex10.html");
});

//Completati 


app.listen(8010);
console.log("Serverul a pornit");