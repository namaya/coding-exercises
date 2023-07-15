

use std::collections::HashSet;
use std::fs;

pub fn day6_tuning_trouble() {
    let path = "inputs/2022/day6/full.txt";

    let stream = fs::read_to_string(path).unwrap();

    let mut i = 4;

    while i < stream.len() {
        let characters = &stream[i-4..i];

        let mut character_set = HashSet::new();

        for character in characters.chars() {
            character_set.insert(character);
        }

        if character_set.len() == 4 {
            break;
        }

        i += 1;
    }

    println!("{i}");
    
}