
use std::{fs, collections::HashSet};

enum Motion {
    Right(u32),
    Left(u32),
    Up(u32),
    Down(u32)
}

pub fn day9_rope_bridge() {
    let path = "inputs/2022/day9/large-example.txt";
    const N: u32 = 10;

    let mut knots_pos: Vec<(i32, i32)> = Vec::from_iter((0..N).map(|_| (0,0)));
    let mut visited = HashSet::from([(0,0)]);
    println!("Pos: {:?}", (0,0));


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
                    println!("U {}", nsteps);
                    for i in 0..nsteps {
                        let len = knots_pos.len();
                        knots_pos[len-1].1 += 1;

                        for i in (0..knots_pos.len()-1).rev() {
                            if knots_pos[i+1].1 - knots_pos[i].1 >= 2 {
                                knots_pos[i].1 += 1;
                                knots_pos[i].0 += knots_pos[i+1].0 - knots_pos[i].0;
                            }
                        }

                        if !visited.contains(&knots_pos[0]) {
                            visited.insert(knots_pos[0]);
                            println!("Pos: {:?}", knots_pos[0]);
                        }
                    }
                }
                Motion::Right(nsteps) => {
                    println!("R {}", nsteps);
                    for i in 0..nsteps {
                        let len = knots_pos.len();
                        knots_pos[len-1].0 += 1;

                        for i in (0..knots_pos.len()-1).rev() {
                            if knots_pos[i+1].0 - knots_pos[i].0 >= 2 {
                                knots_pos[i].0 += 1;
                                knots_pos[i].1 += knots_pos[i+1].1 - knots_pos[i].1;
                            }
                        }

                        if !visited.contains(&knots_pos[0]) {
                            visited.insert(knots_pos[0]);
                            println!("Pos: {:?}", knots_pos[0]);
                        }
                    }
                },
                Motion::Down(nsteps) => {
                    println!("D {}", nsteps);
                    for i in 0..nsteps {
                        let len = knots_pos.len();
                        knots_pos[len-1].1 -= 1;

                        for i in (0..knots_pos.len()-1).rev() {
                            if knots_pos[i+1].1 - knots_pos[i].1 <= -2 {
                                knots_pos[i].1 -= 1;
                                knots_pos[i].0 += knots_pos[i+1].0 - knots_pos[i].0;
                            }
                        }

                        if !visited.contains(&knots_pos[0]) {
                            visited.insert(knots_pos[0]);
                            println!("Pos: {:?}", knots_pos[0]);
                        }
                    }
                },
                Motion::Left(nsteps) => {
                    println!("L {}", nsteps);
                    for i in 0..nsteps {
                        let len = knots_pos.len();
                        knots_pos[len-1].0 -= 1;

                        for i in (0..knots_pos.len()-1).rev() {
                            if knots_pos[i+1].0 - knots_pos[i].0 <= -2 {
                                knots_pos[i].0 -= 1;
                                knots_pos[i].1 += knots_pos[i+1].1 - knots_pos[i].1;
                            }
                        }

                        if !visited.contains(&knots_pos[0]) {
                            visited.insert(knots_pos[0]);
                            println!("Pos: {:?}", knots_pos[0]);
                        }
                    }
                }
            }

        });
    
    println!("{}", visited.len());
}