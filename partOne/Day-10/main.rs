use std::fs;

fn parse_machine(line: &str) -> (Vec<bool>, Vec<Vec<usize>>) {
    // Extract pattern between [...]
    let start = line.find('[').unwrap();
    let end = line.find(']').unwrap();
    let pattern_str = &line[start + 1..end];

    // Convert pattern to bool vector (. = false, # = true)
    let target: Vec<bool> = pattern_str.chars().map(|c| c == '#').collect();

    // Extract button specifications between (...)
    let buttons_start = line.find('(').unwrap();
    let buttons_end = line.find('{').unwrap();
    let buttons_str = &line[buttons_start..buttons_end];

    let mut buttons = Vec::new();

    // Parse each button specification
    let mut in_button = false;
    let mut current_button = String::new();

    for ch in buttons_str.chars() {
        if ch == '(' {
            in_button = true;
            current_button.clear();
        } else if ch == ')' {
            in_button = false;
            // Parse comma-separated indices
            let indices: Vec<usize> = current_button
                .split(',')
                .filter(|s| !s.is_empty())
                .map(|s| s.trim().parse().unwrap())
                .collect();
            buttons.push(indices);
        } else if in_button {
            current_button.push(ch);
        }
    }

    (target, buttons)
}

fn solve_machine(target: &[bool], buttons: &[Vec<usize>]) -> usize {
    let n = target.len();
    let m = buttons.len();
    let mut min_presses = usize::MAX;

    // Convert target to u64 bitmask for faster comparison
    let target_mask: u64 = target.iter()
        .enumerate()
        .map(|(i, &b)| if b { 1u64 << i } else { 0 })
        .fold(0, |acc, x| acc | x);

    // Precompute button masks
    let button_masks: Vec<u64> = buttons.iter()
        .map(|btn| {
            btn.iter()
                .map(|&idx| 1u64 << idx)
                .fold(0, |acc, x| acc | x)
        })
        .collect();

    // Brute force all subsets (m up to ~20 is manageable)
    for subset in 0u64..(1 << m) {
        let press_count = subset.count_ones() as usize;

        // Early pruning: if we already found a better solution
        if press_count >= min_presses {
            continue;
        }

        // Compute XOR of selected buttons
        let mut result = 0u64;
        for i in 0..m {
            if subset & (1u64 << i) != 0 {
                result ^= button_masks[i];
            }
        }

        if result == target_mask {
            min_presses = press_count;
        }
    }

    min_presses
}

fn main() {
    let input = fs::read_to_string("input.txt")
        .expect("Failed to read input.txt");

    let mut total_presses = 0;

    for line in input.lines() {
        let trimmed = line.trim();
        if trimmed.is_empty() {
            continue;
        }

        let (target, buttons) = parse_machine(trimmed);
        let presses = solve_machine(&target, &buttons);
        total_presses += presses;
    }

    println!("{}", total_presses);
}