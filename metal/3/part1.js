let fs = require("fs");

const main = async () => {
    
    let file = await fs.readFileSync('./input.txt', 'utf8');
    let array = file.split("\n");
    let gamma = "";
    let epsilon = "";
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

    for(let i = 0; i < on.length; i++){
        if(parseInt(on[i]) > parseInt(off[i])){
            gamma += "1";
            epsilon += "0";
        } else {
            gamma += "0";
            epsilon += "1";
        }
    }
    gamma = parseInt(gamma, 2);
    epsilon = parseInt(epsilon, 2)
    console.log(gamma);
    console.log(epsilon);
    console.log(gamma * epsilon);
    console.log("done");
}

main(); 