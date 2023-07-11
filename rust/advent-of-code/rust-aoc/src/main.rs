
use std::fs;


fn day1_max_calories() {
    let contents = fs::read_to_string("inputs/day1/input.txt")
        .expect("Error reading file...");

    let mut elf_calories : Vec<u32> = vec![0];

    for line in contents.split("\n") {
        if let Ok(num_calories) = line.parse::<u32>() {
            let cur_calories = elf_calories.last_mut()
                .expect("something went wrong..");

            *cur_calories += num_calories;
        } else {
            elf_calories.push(0);
        }
    }

    // get max value
    let mut max_value: u32 = 0;

    for num_calories in elf_calories {
        if num_calories > max_value {
            max_value = num_calories;
        }
    }

    println!("Max calories: {max_value}");

}

fn main() {
    day1_max_calories()
}
