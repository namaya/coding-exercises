
use std::fs;

pub fn day10_cathode_ray_tube() {
    let mut v: i32 = 1;
    let mut v_hist: Vec<i32> = vec![];

    let input_path = "inputs/2022/day10/full.txt";

    let contents = fs::read_to_string(input_path)
        .expect("invalid input path");


    for instruction in contents.lines() {
        let instruction: Vec<&str> = instruction.split_whitespace().collect();

        match instruction[0] {
            "addx" => {
                let h = (v_hist.len() as i32) % 40;

                if h == 0 {
                    println!();
                }

                if h >= v-1 && h <= v+1 {
                    print!("#");
                } else {
                    print!(".");
                }

                v_hist.push(v);

                let h = (v_hist.len() as i32) % 40;

                if h == 0 {
                    println!();
                }

                if h >= v-1 && h <= v+1 {
                    print!("#");
                } else {
                    print!(".");
                }

                v_hist.push(v);

                v += instruction[1].parse::<i32>()
                    .expect("invalid arg to addx.");
            },
            "noop" => {
                let h = (v_hist.len() as i32) % 40;

                if h == 0 {
                    println!();
                }

                if h >= v-1 && h <= v+1 {
                    print!("#");
                } else {
                    print!(".");
                }

                v_hist.push(v);
    
            },
            _ => panic!("Unkown command"),
        }
    }

    v_hist.push(v);

    let answer = v_hist.iter()
        .enumerate()
        .filter(|(i, _)| i % 40 == 19)
        .map(|(i, v)|  ((i + 1) as i32) * v)
        .sum::<i32>();

    println!();
    println!("{:?}", answer);
}