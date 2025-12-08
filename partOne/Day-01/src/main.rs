use std::fs;

fn main() {
    let input = fs::read_to_string("input.txt").expect("Failed to read input.txt");
    let instructions = input.lines().collect::<Vec<&str>>();

    let mut position: i32 = 50;
    let mut zero_count = 0;

    for instr in instructions {
        let (direction, steps_str) = instr.split_at(1);
        let steps: i32 = steps_str.parse().expect("Invalid step number");

        match direction {
            "L" => position = (position - steps).rem_euclid(100),
            "R" => position = (position + steps).rem_euclid(100),
            _ => panic!("Invalid direction"),
        }

        if position == 0 {
            zero_count += 1;
        }
    }

    println!("Password: {}", zero_count);
}