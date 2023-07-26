
use std::fs;

pub fn day10_cathode_ray_tube() {
    let mut signal_history: [i32; 250] = [0; 250];
    signal_history[0] = 1;

    let mut cycle_num: usize = 0;

    let input_path = "inputs/2022/day10/example.txt";

    fs::read_to_string(input_path)
        .expect("invalid input path")
        .split("\n")
        .map_while(|instruction| {
            let instruction = instruction.split_whitespace()
                .collect::<Vec<&str>>();

            match instruction[0] {
                "addx" => {
                    if cycle_num + 1 < signal_history.len() {
                        signal_history[cycle_num+1] = signal_history[cycle_num];
                    }

                    if cycle_num + 2 < signal_history.len() {
                        signal_history[cycle_num+2] = signal_history[cycle_num] + instruction[1].parse::<i32>().expect("invalid addx argument.");
                    }

                    cycle_num += 2;
                },
                "noop" => {
                    signal_history[cycle_num+1] = signal_history[cycle_num];
                    cycle_num += 1;
                },
                _ => panic!("Unknown command."),
            }

            if cycle_num >= signal_history.len() {
                None
            } else {
                Some(())
            }
        })
        .for_each(|_| {});
    
    signal_history.iter().enumerate().map(|(i, sig)| format!("{}: {}", i, sig))
        .for_each(|s| println!("{}", s));

    let sigs: Vec<i32> = signal_history.iter()
        .enumerate()
        .filter(|(i, _)| (i) % 40 == 20 )
        .map(|(i, signal)| (i as i32) * signal )
        .collect();

    println!("{:?}", sigs);
}