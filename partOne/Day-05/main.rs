use std::fs;
use std::ops::RangeInclusive;
use std::path::Path;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let input = fs::read_to_string(Path::new("input.txt"))?;

    let mut lines = input.lines();

    // Parse fresh ranges
    let mut fresh_ranges: Vec<RangeInclusive<u64>> = Vec::new();
    let mut blank_seen = false;

    for line in lines.by_ref() {
        let line = line.trim();
        if line.is_empty() {
            blank_seen = true;
            break;
        }
        if line.contains('-') {
            let parts: Vec<&str> = line.split('-').collect();
            let start: u64 = parts[0].trim().parse()?;
            let end: u64 = parts[1].trim().parse()?;
            fresh_ranges.push(start..=end);
        }
    }

    // Parse available ingredient IDs
    let mut available_ids: Vec<u64> = Vec::new();
    for line in lines {
        let line = line.trim();
        if !line.is_empty() {
            let id: u64 = line.parse()?;
            available_ids.push(id);
        }
    }

    // Count how many available IDs are fresh
    let mut fresh_count = 0;
    for &id in &available_ids {
        let is_fresh = fresh_ranges.iter().any(|range| range.contains(&id));
        if is_fresh {
            fresh_count += 1;
        }
    }

    println!("Number of fresh ingredient IDs: {}", fresh_count);

    Ok(())
}