use std::collections::HashMap;
use std::fs;

pub fn days1to5() {
    day1_max_calories();
    day2_rock_paper_scissors();
    day3_rucksack_reorganization();
    day4_camp_cleanup();
}

pub fn day1_max_calories() {
    let contents = fs::read_to_string("inputs/2022/day1/full.txt")
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

pub fn day2_rock_paper_scissors() {

    let file_path = "inputs/2022/day2/full.txt";

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

pub fn day3_rucksack_reorganization() {
    let file_path = "inputs/2022/day3/full.txt";

    let rucksacks = fs::read_to_string(file_path)
                                    .unwrap();

    let mut total_priority: u32 = 0;

    let mut groups = ["", "", ""];
    let mut i = 0;

    for rucksack in rucksacks.split("\n") {
        groups[i] = rucksack;
        i = (i + 1) % 3;

        if i != 0 || groups[0].len() == 0 {
            continue;
        };

        let mut special_item = 0u8;

        for item in groups[0].as_bytes() {
            if groups[1].as_bytes().contains(item) && groups[2].as_bytes().contains(item) {
                special_item = *item;
                break;
            }
        }

        let priority = if special_item >= b'a' {
            special_item - b'a' + 1
        } else {
            special_item - b'A' + 27
        };

        total_priority += u32::from(priority);
    }

    println!("{total_priority}");
}

pub fn day4_camp_cleanup() {
    let input_path = "inputs/2022/day4/full.txt";
    let section_assignments = fs::read_to_string(input_path).unwrap();

    let mut count = 0;

    for pair in section_assignments.split("\n") {
        let assigments: Vec<&str> = pair.split(",").collect();

        let section_range1: Vec<u16> = assigments[0].split("-").map(|x| x.parse::<u16>().unwrap()).collect();
        let section_range2: Vec<u16> = assigments[1].split("-").map(|x| x.parse::<u16>().unwrap()).collect();

        if section_range1[0] < section_range2[0] && section_range1[1] >= section_range2[0] {
            count += 1;
        } else if section_range2[0] < section_range1[0] && section_range2[1] >= section_range1[0] {
            count += 1;
        } else if section_range1[0] == section_range2[0] {
            count += 1;
        }

        // part 1
        // if section_range1[0] < section_range2[0] && section_range1[1] >= section_range2[1] {
        //     count += 1;
        // } else if section_range2[0] < section_range1[0] && section_range2[1] >= section_range1[1] {
        //     count += 1;
        // } else if section_range1[0] == section_range2[0] {
        //     count += 1;
        // }
    }

    println!("{count}");
}