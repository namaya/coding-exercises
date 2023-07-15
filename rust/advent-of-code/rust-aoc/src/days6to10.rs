

use std::collections::HashSet;
use std::fs;

pub fn day6_tuning_trouble() {
    let path = "inputs/2022/day6/full.txt";
    let lookback_window = 14;

    let stream = fs::read_to_string(path).unwrap();

    let mut i = lookback_window;

    while i < stream.len() {
        let characters = &stream[i-lookback_window..i];

        let mut character_set = HashSet::new();

        for character in characters.chars() {
            character_set.insert(character);
        }

        if character_set.len() == lookback_window {
            break;
        }

        i += 1;
    }

    println!("{i}");
    
}