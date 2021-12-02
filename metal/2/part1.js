let fs = require("fs");

const main = async () => {
    
    let file = await fs.readFileSync('./input.txt', 'utf8');
    let array = file.split("\n");
    let horizontal = 0;
    let depth = 0;
    for(let i = 0; i < array.length; i++) {
        let instruction = array[i].split(" ");
        switch(instruction[0]) {
            case "forward":
                horizontal += parseInt(instruction[1]);
                break;
            case "up":
                depth -= parseInt(instruction[1]);
                break;
            case "down":
                depth += parseInt(instruction[1]);
                break;
        }
    }
    console.log(horizontal + " " + depth);
    console.log(horizontal*depth);
    console.log("done");
}

main(); 