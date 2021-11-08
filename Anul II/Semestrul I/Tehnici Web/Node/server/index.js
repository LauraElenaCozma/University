const someObj = require('./bd.json');
const express = require('express');
const app = express();
const port = 3000;
app.use(express.json()); 

app.get('/',  (req,res) => {res.send(someObj);});
app.listen(port , () => {console.log('Running');});