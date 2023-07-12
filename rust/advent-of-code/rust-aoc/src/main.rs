
use std::collections::HashMap;
use std::fs;


fn day1_max_calories() {
    let contents = fs::read_to_string("inputs/day1/full.txt")
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
    let mut max_values: [u32; 3] = [0, 0, 0];

    for num_calories in elf_calories {
        for value in max_values {
            if num_calories > value {
                // replace smallest value
                let mut min_value = u32::MAX;
                let mut min_i = 0;

                for (i, value) in max_values.iter().enumerate() {
                    if *value < min_value {
                        min_value = *value;
                        min_i = i;
                    }
                }

                max_values[min_i] = num_calories;
                break;
            }

        }
    }

    let top3: u32 = max_values.iter().sum();

    println!("Max of top 3 elves: {top3}");

}

fn day2_rock_paper_scissors() {

    let file_path = "inputs/day2/full.txt";

    let strategy_guide = fs::read_to_string(file_path)
        .expect("Error reading input file.");

    let opponent_action_encodings = HashMap::from([
        ("A", 1),
        ("B", 2),
        ("C", 3)
    ]);

    // from part 1
    // let player_action_encodings = HashMap::from([
    //     ("X", 1),
    //     ("Y", 2),
    //     ("Z", 3)
    // ]);

    let player_action_encodings = HashMap::from([
        ("X", [0, 3, 1, 2]),
        ("Y", [0, 1, 2, 3]),
        ("Z", [0, 2, 3, 1])
    ]);


    let action_rules = [
        [0, 0, 0, 0],
        [0, 3, 0, 6],
        [0, 6, 3, 0],
        [0, 0, 6, 3],
    ];

    let mut overall_score = 0;

    for line in strategy_guide.split("\n") {
        let inputs: Vec<&str> = line.split(" ").collect();

        let desired_round_outcome = inputs[1];
        let opp_action_score = opponent_action_encodings[inputs[0]];

        let player_action_score = player_action_encodings[desired_round_outcome][opp_action_score];

        let round_outcome = action_rules[player_action_score][opp_action_score];
        let player_score = player_action_score + round_outcome;

        overall_score += player_score;
    }

    println!("Overall score: {overall_score}");
}

fn main() {
    day2_rock_paper_scissors()
}
