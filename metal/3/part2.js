let fs = require("fs");

function countBits(array){
    let on = [];
    let off = [];
    for(let i = 0; i < array.length; i++) {
        let split = array[i].split("");
        for(let j = 0; j < split.length; j++){
            switch(split[j]){
                case "0":
                    if(!off[j]){
                        off[j] = 0;
                    }
                    off[j] = off[j] + 1;
                    break;
                case "1":
                    if(!on[j]){
                        on[j] = 0;
                    }
                    on[j] = on[j] + 1;
                    break;
            }
        }
    }
    return {
        on: on,
        off: off,
    }
}

const main = async () => {
    
    let file = await fs.readFileSync('./input.txt', 'utf8');
    let originalArray = file.split("\n");
    let array = originalArray;
    let oxygen = "";
    let scrubber = "";
    let result = countBits(array);
    let on = result.on;
    let off = result.off;

    for(let i = 0; i < on.length; i++){
        if(parseInt(on[i]) >= parseInt(off[i])){
            array = array.filter(entry => entry.split("")[i] == "1");
            console.log(array);
        } else {
            array = array.filter(entry => entry.split("")[i] == "0");
            console.log(array);
        }
        if(array.length == 1)
            break;
        let recount = countBits(array);
        on = recount.on;
        off = recount.off;
    }
    oxygen = array[0];

    array = originalArray;
    on = result.on;
    off = result.off;

    for(let i = 0; i < on.length; i++){
        if(parseInt(on[i]) >= parseInt(off[i])){
            array = array.filter(entry => entry.split("")[i] == "0");
        } else {
            array = array.filter(entry => entry.split("")[i] == "1");
        }
        if(array.length == 1)
            break;
        let recount = countBits(array);
        on = recount.on;
        off = recount.off;
    }
    scrubber = array[0];

    console.log(on);
    console.log(off);
    console.log(`Oxygen\nbinary: ${oxygen}\ndecimal: ${parseInt(oxygen, 2)}`);
    console.log(`Scrubber\nbinary: ${scrubber}\ndecimal: ${parseInt(scrubber, 2)}`);
    console.log(parseInt(oxygen, 2) * parseInt(scrubber, 2));
    console.log("done");
}

main(); 