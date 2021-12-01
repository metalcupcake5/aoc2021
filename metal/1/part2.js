let fs = require("fs");

const main = async () => {
    
    let file = await fs.readFileSync('./numbers.txt', 'utf8');
    let array = file.split("\n");
    let windows = [];
    for(let i = 0; i < array.length - 2; i++){
        windows.push(parseInt(array[i]) + parseInt(array[i+1]) + parseInt(array[i+2]));
    }
    let count = 0;
    let previous = windows[0];
    for(let i = 1; i < windows.length; i++) {
        if(parseInt(windows[i]) > parseInt(previous)){
            count++;
        }
        previous = windows[i];
    }
    console.log(count);
    console.log("done");
}

main(); 