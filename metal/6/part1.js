let fs = require("fs");

function simulate(array){
    let newArray = [];
    for(let i = 0; i < array.length; i++){
        if(array[i] - 1 < 0){
            newArray.push(6, 8);
        } else {
            newArray.push(array[i] - 1);
        }
    }
    return newArray;
}

const main = async () => {
    
    let file = await fs.readFileSync('./numbers.txt', 'utf8');
    let array = file.split(",");
    
    for(let i = 0; i < array.length; i++) {
        array[i] = parseInt(array[i]);
    }

    let days = 80;
    let simulation = array;
    for(let i = 0; i < days; i++){
        simulation = simulate(simulation);
    }
    console.log(simulation);
    console.log(simulation.length);
    console.log("done");
}

main(); 