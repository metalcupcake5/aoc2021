use std::fs;

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

    let mut gamma = String::from("");
    let mut epsilon = String::from("");

    for d in digits {
        let mut sum: u32 = 0;

        for x in d.iter() {
            if *x {
                sum += 1;
            }
        }

        let mut len: u32 = d.len() as u32;
        len /= 2;

        if sum > len {
            gamma.push_str("1");
            epsilon.push_str("0");
        } else {
            gamma.push_str("0");
            epsilon.push_str("1");
        }
    }

    let gamma = u32::from_str_radix(&gamma, 2).unwrap();
    let epsilon = u32::from_str_radix(&epsilon, 2).unwrap();

    println!("Result (part 1): {}", gamma * epsilon);
}
