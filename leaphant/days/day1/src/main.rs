use std::fs;

fn main() {
    let input = fs::read_to_string("../../inputs/2021/1/input.txt")
        .expect("Couldn't read input file, has it not been downloaded yet?");

    let mut prev_measurement: u32 = 0;
    let mut increases = 0;
    let lines = input.lines();

    let mut measurements = Vec::new();

    for line in lines {
        let measurement: u32 = match line.parse() {
            Ok(x) => x,
            Err(_) => {
                println!("Failed to parse {} as i32", line);
                continue;
            }
        };

        measurements.push(measurement);
    }

    for m in measurements.iter() {
        if prev_measurement > 0 && m > &prev_measurement {
            increases += 1;
        }

        prev_measurement = *m;
    }

    println!("Result (part 1): {}", increases);

    prev_measurement = 0;
    increases = 0;

    let mut measurement = Vec::new();

    for (index, m) in measurements.iter().enumerate() {
        measurement.push(m);

        if index < 2 {
            continue;
        }

        let sum: u32 = measurement.iter().copied().sum();

        if prev_measurement > 0 && sum > prev_measurement {
            increases += 1;
        }

        prev_measurement = sum;

        measurement.remove(0);
    }

    println!("Result (part 2): {}", increases);
}
