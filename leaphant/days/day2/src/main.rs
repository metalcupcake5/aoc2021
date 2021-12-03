use std::fs;

fn main() {
    let input = fs::read_to_string("../../inputs/2021/2/input.txt")
        .expect("Couldn't read input file, has it not been downloaded yet?");

    let mut d: u32 = 0;
    let mut h: u32 = 0;
    let mut a: u32 = 0;
    let mut result: u32 = 0;

    let mut part: u8 = 1;

    loop {
        if part == 2 {
            d = 0;
            h = 0;
        }

        for line in input.lines() {
            let x: Vec<&str> = line.split_whitespace().collect();

            let movement = x[0];
            let amount: u32 = match x[1].parse() {
                Ok(x) => x,
                Err(_) => {
                    println!("Failed to parse {} as u32", line);
                    continue;
                }
            };

            if part == 1 {
                match movement {
                    "forward" => h += amount,
                    "down" => d += amount,
                    "up" => d -= amount,
                    _ => ()
                }
            } else if part == 2 {
                match movement {
                    "forward" => {
                        h += amount;
                        d += a * amount;
                    },
                    "down" => a += amount,
                    "up" => a -= amount,
                    _ => ()
                }
            }

            result = d * h;
        }

        println!("Result (part {}): {}", part, result);

        if part > 1 {
            break;
        }

        part += 1;
    }
}
