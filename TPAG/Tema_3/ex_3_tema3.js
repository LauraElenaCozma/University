const fs = require('fs');

const a = 5;
const N = 30;
const pas = 0.15;
const fileExport = "object.obj";
let points = [];
let string = "# Blender v2.92.0 OBJ File: ''\n" + 
"# www.blender.org\n" + 
"mtllib " + fileExport + "\n";

for (let u = 0; u < Math.PI; u += pas) {
    for (let v = -1; v < 1; v += pas) {
        const x = a * (Math.cos(v) + u * Math.cos(v / 2) * Math.cos(v));
        const y = a * (Math.sin(v) + u * Math.cos(v / 2) * Math.sin(v));
        const z = a * u * Math.sin(v / 2);

        const point = {
            x,
            y,
            z
        };

        points.push(point);
        string = string + "v " + x + " " + y + " " + z + "\n";
    }
}
string += "usemtl None\n" + 
    "s off \n";

let facesString = "";
console.log(points.length);
for(let i = 0 ; i < points.length - 3; ++i) {
    let nr1 = i + 1;
    let nr2 = i + 2;
    let nr3 = i + 3;
    let nr4 = i + 4;
    facesString = facesString + "f " + nr1 + "// " +   nr2 + "// " + nr3 + "// " + nr4 + "//\n";
}

console.log(facesString);
string = string + facesString;

fs.writeFileSync(fileExport, string, (err) => {
    if(err) 
        throw err;
});