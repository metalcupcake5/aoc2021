use std::fs;
use std::cmp::Ordering;

fn main() {
    let input = fs::read_to_string("../../inputs/2021/3/input.txt")
        .expect("Couldn't read input file, has it not been downloaded yet?");

    let mut digits: Vec<Vec<bool>> = Vec::new();
    
    for (i, line) in input.lines().enumerate() {
        let chars: Vec<char> = line.chars().collect();

        if i == 0 {
            while digits.len() < chars.len() {
                digits.push(Vec::<bool>::new());
            }
        }

        for (i, c) in chars.iter().enumerate() {
            digits[i].push(*c == '1');
        }
    }

    let mut gamma: u32 = 0;
    let mut epsilon: u32 = 0;

    for (i, d) in digits.iter().enumerate() {
        let mut sum: u32 = 0;

        for x in d.iter() {
            if *x {
                sum += 1;
            }
        }

        let mut len: u32 = d.len() as u32;

        let exp = (digits.len() as u32 - 1) - i as u32;

        len /= 2;

        match sum.cmp(&len) {
            Ordering::Greater => gamma += 2u32.pow(exp),
            _ => epsilon += 2u32.pow(exp)
        }
    }

    println!("Result (part 1): {}", gamma * epsilon);
}
