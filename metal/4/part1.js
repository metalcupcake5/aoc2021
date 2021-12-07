let fs = require("fs");

// parses called numbers and returns a card with 1s if it has been called and 0s if it hasn't
function parseCard(card, numbers){
    let result = [];
    
    for(const row of card){
        let rowResults = [];
        for(const item of row){
            rowResults.push(numbers.includes(item) ? 1 : 0);
        }
        result.push(rowResults);
    }
    return result;
}

// check if a card has either a full row or a full column
function checkWin(card){
    let columns = [];
    for(const row of card){
        if(row.filter(entry => entry != 1).length < 1){
            return true;
        }
        for(let i = 0; i < row.length; i++){
            if(columns[i]){
                columns[i].push(row[i]);
            } else {
                columns[i] = [row[i]];
            }
        }
    }
    for(const column of columns){
        if(column.filter(entry => entry != 1).length < 1){
            return true;
        }
    }
    return false;
}

// calculate the sum of unmarked numbers
function calculateUnmarked(card, parsed){
    let sum = 0;
    for(let i = 0; i < parsed.length; i++){ // rows
        const row = parsed[i];
        for(let j = 0; j < row.length; j++){
            sum += row[j] == 0 ? parseInt(card[i][j]) : 0;
        }
    }
    return sum;
}

function draw(draws, cards){
    for(let i = 0; i < draws.length; i++){
        for(const card of cards){
            const parsed = parseCard(card, draws.slice(0, i + 1));
            if(checkWin(parsed)){
                return parseInt(draws[i]) * calculateUnmarked(card, parsed);
            }
        }
    }
}

const main = async () => {
    
    let file = await fs.readFileSync('./input.txt', 'utf8');
    let array = file.split("\n");
    let draws = array[0];
    draws = draws.split(",");
    let cards = [];
    array = array.slice(2);
    let card = [];
    
    // separate into array of bingo cards
    for(let i = 0; i < array.length; i++){
        if(array[i] == ""){
            cards.push(card);
            card = [];
        } else {
            card.push(array[i]);
        }
    }
    cards.push(card);

    // separate card rows into arrays of numbers
    for(const card of cards){
        for(let i = 0; i < card.length; i++){
            card[i] = card[i].replace(/^\s+|\s+$|\s+(?=\s)/g, ""); // removes whitespace
            card[i] = card[i].split(" ");
        }
    }

    
    console.log(draw(draws, cards));
    /*const card3 = parseCard(cards[2], draws.slice(0, 12))
    console.log(card3);
    console.log(checkWin(card3));
    console.log(calculateUnmarked(cards[2], card3))*/
    console.log("done");
}

main(); 