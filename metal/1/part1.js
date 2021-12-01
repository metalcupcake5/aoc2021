let fs = require("fs");

const main = async () => {
    
    let file = await fs.readFileSync('./numbers.txt', 'utf8');
    let array = file.split("\n");
    let count = 0;
    let previous = array[0];
    for(let i = 1; i < array.length; i++) {
        if(parseInt(array[i]) > parseInt(previous)){
            count++;
        }
        previous = array[i];
    }
    console.log(count);
    console.log("done");
}

main(); 