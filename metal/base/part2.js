let fs = require("fs");

const main = async () => {
    
    let file = await fs.readFileSync('./numbers.txt', 'utf8');
    let array = file.split("\n");
    
    for(let i = 0; i < array.length; i++) {
        
    }
    
    console.log("done");
}

main(); 