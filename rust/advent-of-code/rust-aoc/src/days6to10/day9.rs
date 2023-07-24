
use std::{fs, collections::HashSet};

enum Motion {
    Right(u32),
    Left(u32),
    Up(u32),
    Down(u32)
}

pub fn day9_rope_bridge() {
    let path = "inputs/2022/day9/full.txt";

    let mut head_pos = (0, 0);
    let mut tail_pos = (0, 0);
    let mut visited = HashSet::new();

    visited.insert((0,0));


    fs::read_to_string(path)
        .unwrap()
        .split("\n")
        .map(|motion| match &motion.split_whitespace().collect::<Vec<&str>>()[..] {
                &[first, second, ..] => match first {
                    "U" => Motion::Up(second.parse::<u32>().expect("nsteps not uint32")),
                    "R" => Motion::Right(second.parse::<u32>().expect("nsteps not uint32")),
                    "D" => Motion::Down(second.parse::<u32>().expect("nsteps not uint32")),
                    "L" => Motion::Left(second.parse::<u32>().expect("nsteps not uint32")),
                    _ => unreachable!()
                },
                _ => unreachable!()
        })
        .for_each(|motion| {
            match motion {
                Motion::Up(nsteps) => {
                    for i in 0..nsteps {
                        head_pos.1 += 1;

                        if head_pos.1 - tail_pos.1 >= 2 {
                            tail_pos.1 += 1;
                            tail_pos.0 += head_pos.0 - tail_pos.0;

                            if !visited.contains(&tail_pos) {
                                visited.insert(tail_pos);
                            }
                        }
                    }
                }
                Motion::Right(nsteps) => {
                    for i in 0..nsteps {
                        head_pos.0 += 1;

                        if head_pos.0 - tail_pos.0 >= 2 {
                            tail_pos.0 += 1;
                            tail_pos.1 += head_pos.1 - tail_pos.1;
                            if !visited.contains(&tail_pos) {
                                visited.insert(tail_pos);
                            }
                        }
                    }
                },
                Motion::Down(nsteps) => {
                    for i in 0..nsteps {
                        head_pos.1 -= 1;

                        if head_pos.1 - tail_pos.1 <= -2 {
                            tail_pos.1 -= 1;
                            tail_pos.0 += head_pos.0 - tail_pos.0;
                            if !visited.contains(&tail_pos) {
                                visited.insert(tail_pos);
                            }
                        }
                    }
                },
                Motion::Left(nsteps) => {
                    for i in 0..nsteps {
                        head_pos.0 -= 1;

                        if head_pos.0 - tail_pos.0 <= -2 {
                            tail_pos.0 -= 1;
                            tail_pos.1 += head_pos.1 - tail_pos.1;
                            if !visited.contains(&tail_pos) {
                                visited.insert(tail_pos);
                            }
                        }
                    }
                }
            }

        });
    
    println!("{}", visited.len());
}