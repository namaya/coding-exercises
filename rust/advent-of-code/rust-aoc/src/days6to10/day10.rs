
use std::fs;

pub fn day10_cathode_ray_tube() {
    let mut v = 1;
    let mut v_hist: Vec<i32> = vec![0];

    let input_path = "inputs/2022/day10/full.txt";

    let contents = fs::read_to_string(input_path)
        .expect("invalid input path");


    for instruction in contents.lines() {
        let instruction: Vec<&str> = instruction.split_whitespace().collect();

        match instruction[0] {
            "addx" => {
                v_hist.push(v);
                v_hist.push(v);

                v += instruction[1].parse::<i32>()
                    .expect("invalid arg to addx.");
            },
            "noop" => {
                v_hist.push(v);
            },
            _ => panic!("Unkown command"),
        }
    }

    v_hist.push(v);

    let answer = v_hist.iter()
        .enumerate()
        .filter(|(i, _)| i % 40 == 20)
        .map(|(i, v)|  (i as i32) * v)
        .sum::<i32>();

    println!("{:?}", answer);
}